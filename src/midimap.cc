#include "midimap/midimap.hh"
#include "midimap/SetupWindow.hh"

#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>

#include <cstdio>

namespace midimap {

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

    register_callbacks();

    layout_.show();
    return Fl::run();
}

struct RegisterCallbacks {

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

        layout.setup->show();
        ctrl.read(layout.setup->button);
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

    static void cb_play(Fl_Widget *w, void *data)
    {
        printf("@@ play\n");
        auto *midiMap = (MidiMap*) data;
        auto &layout  = Attorney::layout(*midiMap);
        auto &ctrl    = Attorney::controller(*midiMap);

        if (layout.setup->isEmpty()) { 
            return; 
        } else if (layout.setup->isNote()) {
            layout.setup->key();
            ctrl.stop();
        } else if (layout.setup->isKey()) {
            layout.setup->note();
            ctrl.read(layout.setup->button);
        }
    }

};

void
MidiMap::
register_callbacks()
{
    layout_.choice->callback(&RegisterCallbacks::cb_choice, this);
    layout_.button_setup->callback(&RegisterCallbacks::cb_setup, this);
    layout_.button_start->callback(&RegisterCallbacks::cb_start, this);
    layout_.button_import->callback(&RegisterCallbacks::cb_import, this);
    layout_.button_export->callback(&RegisterCallbacks::cb_export, this);

    layout_.setup->callback(&RegisterCallbacks::cb_setup_window, this);
    layout_.setup->button->callback(&RegisterCallbacks::cb_play, this);
}

} // namespace midimap
