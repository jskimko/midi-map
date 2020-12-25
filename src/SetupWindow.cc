#include "midimap/SetupWindow.hh"

#include "FL/Fl_Box.H"
#include "FL/Fl_Button.H"

namespace midimap {

SetupWindow::
SetupWindow(int w, int h)
    : Fl_Window(w, h)
{
    box = new Fl_Box(0, h / 10, w, FL_NORMAL_SIZE * 2);
    box->color(FL_BACKGROUND_COLOR);
    box->box(FL_FLAT_BOX);

    auto center_on = [](Fl_Widget *w, int x, int y) {
        w->position(x - w->w() / 2, y - w->h() / 2);
    };

    button = new Fl_Button(0, 0, w / 3, h / 3);
    center_on(button, w / 2, 2 * h / 3);

    this->end();
}

void
SetupWindow::
note()
{
    box->label(NOTE_TEXT);
    button->label(EMPTY_TEXT);
}

void
SetupWindow::
key()
{
    box->label(KEY_TEXT);
    button->label(EMPTY_TEXT);
}

bool
SetupWindow::
isNote() const
{
    return box->label() == NOTE_TEXT;
}

bool
SetupWindow::
isKey() const
{
    return box->label() == KEY_TEXT;
}

bool
SetupWindow::
isEmpty() const
{
    return button->label() == EMPTY_TEXT;
}

int
SetupWindow::
handle(int e)
{
    switch (e) {
        case FL_KEYUP:
            printf("@@ KEYUP %s %d\n", Fl::event_text(), Fl::event_key());
            button->copy_label(Fl::event_text());
            return 1;
        default:
            return Fl_Window::handle(e);
    }
}

} // namespace midimap