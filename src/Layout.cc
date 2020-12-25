#include "midimap/Layout.hh"
#include "midimap/SetupWindow.hh"

#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>

namespace midimap {

void
Layout::
draw()
{
    FL_NORMAL_SIZE = 12;
    int const pad = FL_NORMAL_SIZE / 2;
    int pad4 = pad * 4;
    int pad8 = pad * 8;
    static constexpr int N_MAIN = 64;
    int remaining_pads = N_MAIN;

    auto vert_split = [pad](Fl_Widget *w1, Fl_Widget *w2, double pct) {
        auto space = pad * (N_MAIN - 3);
        w1->resize(pad, w1->y(), space * pct, w1->h());
        w2->resize(w1->x() + w1->w() + pad, w2->y(), space * (1 - pct), w2->h());
    };

    window = new Fl_Window(pad * N_MAIN, pad * N_MAIN, TITLE_TEXT);

    int y = pad;
    remaining_pads -= 2; // top and bottom pads.

    box_choice = new Fl_Box(0, y, 0, pad4, "Controller");
    choice = new Fl_Choice(0, y, 0, pad4);
    vert_split(box_choice, choice, 0.3);
    box_choice->align(FL_ALIGN_CENTER);
    y += box_choice->h() + pad;
    remaining_pads -= 5;

    button_setup = new Fl_Button(0, y, 0, pad8, "Setup");
    button_start = new Fl_Light_Button(0, y, 0, pad8, "Start");
    vert_split(button_setup, button_start, 0.5);
    button_start->align(FL_ALIGN_CENTER);
    y += button_setup->h() + pad;
    remaining_pads -= 9;

    button_import = new Fl_Button(0, y, 0, pad4, "Import");
    input_import = new Fl_Input(0, y, 0, pad4);
    vert_split(button_import, input_import, 0.2);
    y += button_import->h() + pad;
    remaining_pads -= 5;

    button_export = new Fl_Button(0, y, 0, pad4, "Export");
    input_export = new Fl_Input(0, y, 0, pad4);
    vert_split(button_export, input_export, 0.2);
    y += button_export->h() + pad;
    remaining_pads -= 5;

    // output fills to the end.
    output = new Fl_Multiline_Output(pad, y, pad * (N_MAIN - 2), pad * remaining_pads);
    output->value("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n");
    output->cursor_color(FL_BACKGROUND_COLOR);
    output->color(FL_BACKGROUND_COLOR);

    // insert output between choice and setup.
    // position(int, int) is not working.
    auto shift = output->h() + pad;
    output->resize(output->x(), button_setup->y(), output->w(), output->h());
    button_setup->resize(button_setup->x(), button_setup->y() + shift, button_setup->w(), button_setup->h());
    button_start->resize(button_start->x(), button_start->y() + shift, button_start->w(), button_start->h());
    button_import->resize(button_import->x(), button_import->y() + shift, button_import->w(), button_import->h());
    input_import->resize(input_import->x(), input_import->y() + shift, input_import->w(), input_import->h());
    button_export->resize(button_export->x(), button_export->y() + shift, button_export->w(), button_export->h());
    input_export->resize(input_export->x(), input_export->y() + shift, input_export->w(), input_export->h());

    window->end();

    static constexpr int N_SETUP_X = 40;
    static constexpr int N_SETUP_Y = 20;
    setup = new SetupWindow(pad * N_SETUP_X, pad * N_SETUP_Y);
    setup->note();
    setup->end();

}

void
Layout::
show()
{
    window->show();
}

void
Layout::
deactivate()
{
    button_setup->deactivate();
    button_start->deactivate();
}

} // namespace midimap
