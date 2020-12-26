#include "midimap/midimap.hh"
#include "midimap/SetupWindow.hh"

#include "FL/Fl.H"
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>

#include <cstdio>

namespace midimap {

namespace {
    static int disable_shortcuts(int e) {
        return e == FL_SHORTCUT;
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
    }

    static void cb_import(Fl_Widget *w, void *data)
    {
        printf("@@ import\n");
    }

    static void cb_export(Fl_Widget *w, void *data)
    {
        printf("@@ export\n");
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
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);
        auto &ctrl    = Attorney::controller(*midiMap);

        if (layout.setup->isEmpty()) { 
            return; 
        } else if (layout.setup->isNote()) {
            ctrl.stop();
            layout.setup->key();
        } else if (layout.setup->isKey()) {
            auto &bundle = Attorney::bundle(*midiMap);

            auto it = std::find_if(
                bundle.note2key.begin(), bundle.note2key.end(),
                [](const auto &kv) { return kv.second == Key::NONE; }
            );

            if (it != bundle.note2key.end()) {
                it->second = bundle.key;
            }

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

} // namespace midimap
