#include "midimap/midimap.hh"
#include "midimap/SetupWindow.hh"

#include "FL/Fl.H"
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include "FL/fl_ask.H"

#include <sstream>
#include <fstream>
#include <type_traits>

#include <cstdio>

namespace midimap {

namespace {
    int disable_shortcuts(int e) {
        return e == FL_SHORTCUT;
    }

    std::string output(Key down, Key up, NoteKeyMap const &map)
    {
        std::stringstream ss;
        ss << "Octave Down: " << key2str(down) << "\t"
           << "Octave Up: " << key2str(up) << "\n\n"
           << noteKeyMap2str(map);
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
        layout_.deactivate();
    } else {
        for (auto const &name : controller_.getPortNames()) {
            layout_.choice->add(name.c_str());
        }
        controller_.openPort(0);
    }
    layout_.choice->value(0);

    bundle_.controller = &controller_;
    bundle_.widget = layout_.setup->button_note;
    bundle_.noteKeyMap = &noteKeyMap_;
    bundle_.octaveDown = Key::NONE;
    bundle_.octaveUp = Key::NONE;

    layout_.setup->bundle = &bundle_;
    layout_.setup->button_down->copy_label(key2str(bundle_.octaveDown).c_str());
    layout_.setup->button_up->copy_label(key2str(bundle_.octaveUp).c_str());

    register_callbacks();

    layout_.show();

    Fl::add_handler(&disable_shortcuts);
    return Fl::run();
}

void
MidiMap::
importMap(std::string const &fname)
{
    std::ifstream ifs(fname);
    if (ifs.is_open()) {
        noteKeyMap_.clear();
        std::underlying_type<Key>::type octKey;
        NoteKeyMap::key_type key;
        std::underlying_type<NoteKeyMap::mapped_type>::type val;
        decltype(bundle_.minOctave) oct;

        ifs >> octKey; bundle_.octaveDown = Key(octKey);
        ifs >> octKey; bundle_.octaveUp = Key(octKey);

        ifs >> oct; bundle_.minOctave = oct;
        ifs >> oct; bundle_.maxOctave = oct;

        while (ifs >> key >> val) {
            noteKeyMap_.insert({key, Key(val)});
        }

        layout_.output->value(output(bundle_.octaveDown, bundle_.octaveUp, noteKeyMap_).c_str());
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
        ofs << static_cast<std::underlying_type<Key>::type>(bundle_.octaveDown) << " "
            << static_cast<std::underlying_type<Key>::type>(bundle_.octaveUp) << "\n";
        ofs << bundle_.minOctave << " "
            << bundle_.maxOctave << "\n";
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

struct RegisterCallbacks {

    static void cb_window(Fl_Widget *w, void *data)
    {
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);
        auto &ctrl    = Attorney::controller(*midiMap);

        layout.setup->hide();
        layout.window->hide();
    }

    static void cb_choice(Fl_Widget *w, void *data)
    {
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);
        auto &ctrl    = Attorney::controller(*midiMap);

        ctrl.closePort();
        ctrl.openPort(layout.choice->value());
    }

    static void cb_setup(Fl_Widget *w, void *data)
    {
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);
        auto &ctrl    = Attorney::controller(*midiMap);
        auto &bundle  = Attorney::bundle(*midiMap);

        layout.setup->show();
        ctrl.read(bundle);
    }

    static void cb_start(Fl_Widget *w, void *data)
    {
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
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);

        Attorney::importMap(*midiMap, layout.input_import->value());
    }

    static void cb_export(Fl_Widget *w, void *data)
    {
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);

        Attorney::exportMap(*midiMap, layout.input_export->value());
    }

    static void cb_setup_window(Fl_Widget *w, void *data)
    {
        auto *midiMap    = (MidiMap*) data;
        auto &layout     = Attorney::layout(*midiMap);
        auto &ctrl       = Attorney::controller(*midiMap);
        auto &noteKeyMap = Attorney::noteKeyMap(*midiMap);
        auto &bundle     = Attorney::bundle(*midiMap);

        auto it = noteKeyMap.begin();
        while (it != noteKeyMap.end()) {
            if (it->second == Key::NONE) {
                it = noteKeyMap.erase(it);
            } else {
                it++;
            }
        }

        layout.output->value(output(bundle.octaveDown, bundle.octaveUp, noteKeyMap).c_str());

        layout.setup->hide();
        layout.setup->note();
        ctrl.stop();
    }

    static void cb_note(Fl_Widget *w, void *data)
    {
        auto *midiMap    = (MidiMap*) data;
        auto &layout     = Attorney::layout(*midiMap);
        auto &ctrl       = Attorney::controller(*midiMap);
        auto &bundle     = Attorney::bundle(*midiMap);
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

                auto octave = Converter::octave(it->first);
                if (noteKeyMap.size() == 1) {
                    bundle.minOctave = octave;
                    bundle.maxOctave = octave;
                } else {
                    if (bundle.minOctave > octave) { 
                        bundle.minOctave = octave;
                    } else if (bundle.maxOctave < octave) { 
                        bundle.maxOctave = octave;
                    }
                }
            }

        layout.output->value(output(bundle.octaveDown, bundle.octaveUp, noteKeyMap).c_str());

            layout.setup->note();
            ctrl.read(bundle);
        }
    }

    static void cb_down(Fl_Widget *w, void *data)
    {
        auto *midiMap    = (MidiMap*) data;
        auto &layout     = Attorney::layout(*midiMap);

        layout.setup->down();
    }

    static void cb_up(Fl_Widget *w, void *data)
    {
        auto *midiMap    = (MidiMap*) data;
        auto &layout     = Attorney::layout(*midiMap);

        layout.setup->up();
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
    layout_.setup->button_note->callback(&RegisterCallbacks::cb_note, this);
    layout_.setup->button_down->callback(&RegisterCallbacks::cb_down, this);
    layout_.setup->button_up->callback(&RegisterCallbacks::cb_up, this);
}

} // namespace midimap
