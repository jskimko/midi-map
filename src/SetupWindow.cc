#include "midimap/SetupWindow.hh"
#include "midimap/Bundle.hh"
#include "midimap/Key.hh"

#include "FL/Fl_Box.H"
#include "FL/Fl_Button.H"

namespace midimap {

SetupWindow::
SetupWindow(int w, int h)
    : Fl_Window(w, h),
      bundle(nullptr)
{
    auto w_half = w / 2;
    auto h_half = h / 2;

    auto center_on = [](Fl_Widget *w, int x, int y) {
        w->position(x - w->w() / 2, y - w->h() / 2);
    };

    box_note = new Fl_Box(0, h_half / 10, w, FL_NORMAL_SIZE * 2);
    box_note->color(FL_BACKGROUND_COLOR);
    box_note->box(FL_FLAT_BOX);

    button_note = new Fl_Button(0, 0, w / 3, h_half / 3);
    center_on(button_note, w / 2, 2 * h_half / 3);

    box_octave = new Fl_Box(0, h_half + h_half / 10, w, FL_NORMAL_SIZE * 2, OCTAVE_TEXT);
    box_note->color(FL_BACKGROUND_COLOR);
    box_note->box(FL_FLAT_BOX);

    button_down = new Fl_Button(0, 0, w / 3, h_half / 3);
    button_down->copy_label(key2str(Key::DOWN).c_str());
    center_on(button_down, w * 0.25 , h_half + 2 * h_half / 3);

    button_up = new Fl_Button(0, 0, w / 3, h_half / 3);
    button_up->copy_label(key2str(Key::UP).c_str());
    center_on(button_up, w * 0.75 , h_half + 2 * h_half / 3);

    this->end();
}

void
SetupWindow::
note()
{
    box_note->label(NOTE_TEXT);
    button_note->label(EMPTY_TEXT);
}

void
SetupWindow::
key()
{
    box_note->label(KEY_TEXT);
    button_note->label(EMPTY_TEXT);
}

bool
SetupWindow::
isNote() const
{
    return box_note->label() == NOTE_TEXT;
}

bool
SetupWindow::
isKey() const
{
    return box_note->label() == KEY_TEXT;
}

bool
SetupWindow::
isEmpty() const
{
    return button_note->label() == EMPTY_TEXT;
}

int
SetupWindow::
handle(int e)
{
    if (isKey() && e == FL_KEYUP) {
        bundle->key = fltk2key(Fl::event_key());
        button_note->copy_label(key2str(bundle->key).c_str());
        return 1;
    }
    return Fl_Window::handle(e);
}

} // namespace midimap