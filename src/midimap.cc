#include "midimap/midimap.hh"
#include "midimap/SetupWindow.hh"

#include "FL/Fl.H"
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include "FL/fl_ask.H"

#include <fstream>
#include <type_traits>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>

#include <cstdio>

namespace midimap {

namespace {
    int disable_shortcuts(int e) {
        return e == FL_SHORTCUT;
    }

    std::string
    noteKeyMap2str(NoteKeyMap const &map) {
        if (map.size() == 0) { return {}; }

        auto minOctave = Converter::octave(map.begin()->first);
        auto maxOctave = minOctave;

        for (auto it=map.begin(); it != map.end(); it++) {
            auto octave = Converter::octave(it->first);
            if      (octave < minOctave) { minOctave = octave; }
            else if (octave > maxOctave) { maxOctave = octave; }
        }

        std::vector<std::vector<std::pair<unsigned char, Key>>> octaves(maxOctave - minOctave + 1);
        for (auto it=map.begin(); it != map.end(); it++) {
            auto o = Converter::octave(it->first) - minOctave;
            octaves[o].push_back(*it);
        }

        std::vector<std::string::size_type> maxSymLens(octaves.size());
        std::vector<std::string::size_type> maxKeyLens(octaves.size());
        for (decltype(octaves.size()) i=0; i<octaves.size(); i++) {
            std::sort(octaves[i].begin(), octaves[i].end(), std::greater<>()); 

            for (auto const &p : octaves[i]) {
                auto len = Converter::symbol(p.first).size();
                if (len > maxSymLens[i]) { maxSymLens[i] = len; }
                len = key2str(p.second).size();
                if (len > maxKeyLens[i]) { maxKeyLens[i] = len; }
            }
        }

        auto format_entry = [&maxSymLens, &maxKeyLens](std::stringstream &ss, 
                                                       std::pair<unsigned char, Key> const &p,
                                                       int col) {
            ss << std::left << std::setfill(' ') << std::setw(maxSymLens[col])
               << Converter::symbol(p.first) << " -> " 
               << std::setw(maxKeyLens[col]) << key2str(p.second);
        };

        auto format_row = [](std::stringstream &ss, 
                             std::string const &s, 
                             std::string::size_type w, 
                             bool last) {
            ss << std::setw(w) << s;
            if (!last) { ss << " | "; }
        };

        std::stringstream ss;
        decltype(octaves[0].size()) r=0;
        std::vector<std::string::size_type> maxEntryLens(octaves.size());
        while (1) {
            bool any = false;
            for (decltype(octaves.size()) c=0; c<octaves.size(); c++) {
                if (r < octaves[c].size()) {
                    any = true;
                    break;
                }
            }
            if (!any) { break; }

            for (decltype(octaves.size()) c=0; c<octaves.size(); c++) {
                std::stringstream entry;
                if (r < octaves[c].size()) {
                    format_entry(entry, octaves[c][r], c);
                }
                if (entry.str().size() > maxEntryLens[c]) { 
                    maxEntryLens[c] = entry.str().size(); 
                }
                format_row(ss, entry.str(), maxEntryLens[c], c == octaves.size() - 1);
            }
            ss << "\n";

            r++;
        }

        return ss.str();
    }
}

bool 
MidiMap::
run()
{
    layout_.draw();

    auto const &names = controller_.getPortNames();
    if (names.size() == 0) {
        layout_.choice->add("could not detect a MIDI input device");
        //layout_.deactivate();
    } else {
        for (auto const &name : controller_.getPortNames()) {
            layout_.choice->add(name.c_str());
        }
        controller_.openPort(0);
    }
    layout_.choice->value(0);

    layout_.setup->bundle = &bundle_;
    bundle_.controller = &controller_;
    bundle_.widget = layout_.setup->button;
    bundle_.noteKeyMap = &noteKeyMap_;
    register_callbacks();

    layout_.show();

    Fl::add_handler(&disable_shortcuts);
    return Fl::run();
}

struct RegisterCallbacks {

    static void cb_window(Fl_Widget *w, void *data)
    {
        printf("@@ window\n");
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);
        auto &ctrl    = Attorney::controller(*midiMap);

        layout.setup->hide();
        layout.window->hide();
    }

    static void cb_choice(Fl_Widget *w, void *data)
    {
        printf("@@ choice\n");
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);
        auto &ctrl    = Attorney::controller(*midiMap);

        ctrl.closePort();
        ctrl.openPort(layout.choice->value());
    }

    static void cb_setup(Fl_Widget *w, void *data)
    {
        printf("@@ setup\n");
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);
        auto &ctrl    = Attorney::controller(*midiMap);
        auto &bundle  = Attorney::bundle(*midiMap);

        layout.setup->show();
        ctrl.read(bundle);
    }

    static void cb_start(Fl_Widget *w, void *data)
    {
        printf("@@ start\n");
        auto *midiMap = (MidiMap*) data;
        auto &ctrl    = Attorney::controller(*midiMap);
        auto &bundle  = Attorney::bundle(*midiMap);
        auto *button  = (Fl_Button*) w;

        if (button->value()) {
            ctrl.convert(bundle);
        } else {
            ctrl.stop();
        }
    }

    static void cb_import(Fl_Widget *w, void *data)
    {
        printf("@@ import\n");
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);

        Attorney::importMap(*midiMap, layout.input_import->value());
    }

    static void cb_export(Fl_Widget *w, void *data)
    {
        printf("@@ export\n");
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);

        Attorney::exportMap(*midiMap, layout.input_export->value());
    }

    static void cb_setup_window(Fl_Widget *w, void *data)
    {
        printf("@@ setup_window\n");
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);
        auto &ctrl    = Attorney::controller(*midiMap);

        layout.setup->hide();
        layout.setup->note();
        ctrl.stop();
    }

    static void cb_note(Fl_Widget *w, void *data)
    {
        printf("@@ note\n");
        auto *midiMap    = (MidiMap*) data;
        auto &layout     = Attorney::layout(*midiMap);
        auto &ctrl       = Attorney::controller(*midiMap);
        auto &bundle = Attorney::bundle(*midiMap);
        auto &noteKeyMap = Attorney::noteKeyMap(*midiMap);

        if (layout.setup->isEmpty()) { 
            return; 
        } else if (layout.setup->isNote()) {
            ctrl.stop();
            noteKeyMap[bundle.note] = Key::NONE;

            layout.setup->key();
        } else if (layout.setup->isKey()) {
            auto it = std::find_if(
                noteKeyMap.begin(), noteKeyMap.end(),
                [](const auto &kv) { return kv.second == Key::NONE; }
            );

            if (it != noteKeyMap.end()) {
                auto exists = std::find_if(
                    noteKeyMap.begin(), noteKeyMap.end(),
                    [&bundle](const auto &kv) { return kv.second == bundle.key; }
                );
                if (exists != noteKeyMap.end()) { return; }

                it->second = bundle.key;
            }

            layout.output->value(noteKeyMap2str(noteKeyMap).c_str());

            layout.setup->note();
            ctrl.read(bundle);
        }
    }

};

void
MidiMap::
register_callbacks()
{
    layout_.window->callback(&RegisterCallbacks::cb_window, this);
    layout_.choice->callback(&RegisterCallbacks::cb_choice, this);
    layout_.button_setup->callback(&RegisterCallbacks::cb_setup, this);
    layout_.button_start->callback(&RegisterCallbacks::cb_start, this);
    layout_.button_import->callback(&RegisterCallbacks::cb_import, this);
    layout_.button_export->callback(&RegisterCallbacks::cb_export, this);

    layout_.setup->callback(&RegisterCallbacks::cb_setup_window, this);
    layout_.setup->button->callback(&RegisterCallbacks::cb_note, this);
}

void
MidiMap::
importMap(std::string const &fname)
{
    std::ifstream ifs(fname);
    if (ifs.is_open()) {
        noteKeyMap_.clear();
        NoteKeyMap::key_type key;
        std::underlying_type<NoteKeyMap::mapped_type>::type val;
        while (ifs >> key >> val) {
            noteKeyMap_.insert({key, Key(val)});
        }

        layout_.output->value(noteKeyMap2str(noteKeyMap_).c_str());
        Fl::flush();

        fl_alert("Imported from file '%s'", fname.c_str());
    } else {
        fl_alert("Could not import from file '%s'", fname.c_str());
    }
}

void
MidiMap::
exportMap(std::string const &fname) const
{
    std::ofstream ofs(fname);
    if (ofs.is_open()) {
        for (auto const &kv : noteKeyMap_) {
            ofs << kv.first << " " 
                << static_cast<std::underlying_type<NoteKeyMap::mapped_type>::type>(kv.second)
                << "\n";
        }
        fl_alert("Exported to file '%s'", fname.c_str());
    } else {
        fl_alert("Could not export to file '%s'", fname.c_str());
    }
}

} // namespace midimap
