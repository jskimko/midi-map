#include "midimap/midimap.hh"

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

    auto const &names = controller.getPortNames();
    if (names.size() == 0) {
        layout_.choice->add("could not detect a MIDI input device");
        layout_.deactivate();
    } else {
        for (auto const &name : controller.getPortNames()) {
            layout_.choice->add(name.c_str());
        }
    }
    layout_.choice->value(0);

    register_callbacks();

    layout_.show();
    return Fl::run();
}

struct RegisterCallbacks {

    static void cb_setup(Fl_Widget *w, void *data)
    {
        printf("@@ setup\n");
        auto *midiMap = (MidiMap*) data;
        Attorney::layout(*midiMap).setup->show();
    }

    static void cb_start(Fl_Widget *w, void *data)
    {
        printf("@@ start\n");
        auto *midiMap = (MidiMap*) data;
    }

    static void cb_import(Fl_Widget *w, void *data)
    {
        printf("@@ import\n");
    }

    static void cb_export(Fl_Widget *w, void *data)
    {
        printf("@@ export\n");
    }

};

void
MidiMap::
register_callbacks()
{
    layout_.button_setup->callback(&RegisterCallbacks::cb_setup, this);
    layout_.button_start->callback(&RegisterCallbacks::cb_start, this);
    layout_.button_import->callback(&RegisterCallbacks::cb_import, this);
    layout_.button_export->callback(&RegisterCallbacks::cb_export, this);
}

} // namespace midimap
