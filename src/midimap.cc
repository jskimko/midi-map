#include "midimap/midimap.hh"

#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>

#include <cstdio>

namespace midimap {

namespace {

void callback_setup(Fl_Widget *w, void *data)
{
    ((Fl_Window*) data)->show();
}

void callback_import(Fl_Widget *w, void *data)
{
    auto *input = (Fl_Input*) w;
}

void callback_export(Fl_Widget *w, void *data)
{
}

} // anonymous namespace

bool 
MidiMap::
run()
{
    draw();
    return Fl::run();
}

void
MidiMap::
draw()
{
    FL_NORMAL_SIZE = 12;
    int const pad = FL_NORMAL_SIZE / 2;
    int pad4 = pad * 4;
    int pad8 = pad * 8;
    static constexpr int N = 64;
    int remaining_pads = N;

    auto center_on = [](Fl_Widget *w, int x, int y) {
        w->position(x - w->w() / 2, y - w->h() / 2);
    };

    auto vert_split = [pad](Fl_Widget *w1, Fl_Widget *w2, double pct) {
        auto space = pad * (N - 3);
        w1->resize(pad, w1->y(), space * pct, w1->h());
        w2->resize(w1->x() + w1->w() + pad, w2->y(), space * (1 - pct), w2->h());
    };

    window = new Fl_Window(pad * N, pad * N, TITLE);

    int y = pad;
    remaining_pads -= 2; // top and bottom pads.

    auto *box_choice = new Fl_Box(0, y, 0, pad4, "Controller");
    auto *choice = new Fl_Choice(0, y, 0, pad4);
    vert_split(box_choice, choice, 0.3);
    box_choice->align(FL_ALIGN_CENTER);
    y += box_choice->h() + pad;
    remaining_pads -= 5;

    auto *button_setup = new Fl_Button(0, y, 0, pad8, "Setup");
    auto *button_start = new Fl_Light_Button(0, y, 0, pad8, "Start");
    vert_split(button_setup, button_start, 0.5);
    button_start->align(FL_ALIGN_CENTER);
    y += button_setup->h() + pad;
    remaining_pads -= 9;

    auto *button_imp = new Fl_Button(0, y, 0, pad4, "Import");
    auto *input_imp = new Fl_Input(0, y, 0, pad4);
    vert_split(button_imp, input_imp, 0.2);
    y += button_imp->h() + pad;
    remaining_pads -= 5;

    auto *button_exp = new Fl_Button(0, y, 0, pad4, "Export");
    auto *input_exp = new Fl_Input(0, y, 0, pad4);
    vert_split(button_exp, input_exp, 0.2);
    y += button_exp->h() + pad;
    remaining_pads -= 5;

    // text box fills to the end.
    auto *text = new Fl_Multiline_Output(pad, y, pad * (N - 2), pad * remaining_pads);
    text->value("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n");
    text->cursor_color(FL_BACKGROUND_COLOR);
    text->color(FL_BACKGROUND_COLOR);

    // insert text box between choice and setup.
    // position(int, int) does not work for some reason.
    auto shift = text->h() + pad;
    text->resize(text->x(), button_setup->y(), text->w(), text->h());
    button_setup->resize(button_setup->x(), button_setup->y() + shift, button_setup->w(), button_setup->h());
    button_start->resize(button_start->x(), button_start->y() + shift, button_start->w(), button_start->h());
    button_imp->resize(button_imp->x(), button_imp->y() + shift, button_imp->w(), button_imp->h());
    input_imp->resize(input_imp->x(), input_imp->y() + shift, input_imp->w(), input_imp->h());
    button_exp->resize(button_exp->x(), button_exp->y() + shift, button_exp->w(), button_exp->h());
    input_exp->resize(input_exp->x(), input_exp->y() + shift, input_exp->w(), input_exp->h());

    window->end();

    auto *setup = new Fl_Window(200, 100);
    auto width = setup->w();
    auto height = setup->h();

    auto *box_play = new Fl_Box(0, height/10, width, FL_NORMAL_SIZE * 2, "Play a note:");
    box_play->color(FL_BACKGROUND_COLOR);
    box_play->box(FL_FLAT_BOX);

    auto *button_note = new Fl_Button(0, 0, width / 3, height / 3, "-");
    center_on(button_note, width / 2, 2 * height / 3);

    setup->end();

    // Callbacks.
    button_setup->callback(callback_setup, setup);

    window->show();
}

} // namespace midimap
