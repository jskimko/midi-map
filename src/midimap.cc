#include "midimap/midimap.hh"

#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

#include <cstdio>

namespace midimap {

namespace {

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
    window = new Fl_Window(400, 350, TITLE);
    int width = window->w();
    int height = window->h();

    static constexpr double ratio = 0.95;
    int pad_w = (int) (width * (1 - ratio) / 2);
    int pad_h = (int) (height * (1 - ratio) / 2);
    int pad = (pad_w < pad_h) ? pad_w : pad_h;

    int max_w = width - 2 * pad;
    int max_h = height - 2 * pad;

    int x = pad;
    int y = pad;

    static constexpr double td_h = 0.65;
    auto *text = new Fl_Text_Display(x, y, max_w, max_h * td_h);
    auto *buf = new Fl_Text_Buffer();
    std::string s = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n";
    buf->text(s.c_str());
    text->buffer(buf);
    y += max_h * td_h + pad_h;

    static constexpr double button_h = (ratio - td_h) / 3;
    auto *button_setup = new Fl_Button(x, y, (max_w - pad) / 2, max_h * button_h, "Setup");
    auto *button_start = new Fl_Light_Button(x + pad + (max_w - pad) / 2, y, (max_w - pad) / 2, max_h * button_h, "Start");
    button_start->align(FL_ALIGN_CENTER);
    y += max_h * button_h + pad_h;

    static constexpr double button_w = 0.2;
    auto *button_imp = new Fl_Button(x, y, (max_w * button_w) - pad / 2, FL_NORMAL_SIZE * 2, "Import");
    auto *input_imp = new Fl_Input(x + (max_w * button_w) + pad / 2, y, max_w * (1 - button_w), FL_NORMAL_SIZE * 2);
    y += FL_NORMAL_SIZE * 2 + pad_h;

    auto *button_exp = new Fl_Button(x, y, (max_w * button_w) - pad / 2, FL_NORMAL_SIZE * 2, "Export");
    auto *input_exp = new Fl_Input(x + (max_w * button_w) + pad / 2, y, max_w * (1 - button_w), FL_NORMAL_SIZE * 2);
    y += FL_NORMAL_SIZE * 2 + pad_h;

    window->end();
    window->show();
}

} // namespace midimap
