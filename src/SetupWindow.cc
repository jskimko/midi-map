#include "midimap/SetupWindow.hh"
#include "midimap/Bundle.hh"
#include "midimap/Key.hh"

#include "FL/Fl_Box.H"
#include "FL/Fl_Button.H"

#include <string>
#include <algorithm>

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
    button_note->clear_visible_focus();
    center_on(button_note, w / 2, 2 * h_half / 3);

    box_octave = new Fl_Box(0, h_half + h_half / 10, w, FL_NORMAL_SIZE * 2, OCTAVE_TEXT);
    box_note->color(FL_BACKGROUND_COLOR);
    box_note->box(FL_FLAT_BOX);

    button_down = new Fl_Button(0, 0, w / 3, h_half / 3);
    button_down->clear_visible_focus();
    center_on(button_down, (int) (w * 0.25), (int) (h_half + 2 * h_half / 3));

    button_up = new Fl_Button(0, 0, w / 3, h_half / 3);
    button_up->clear_visible_focus();
    center_on(button_up, (int) (w * 0.75), (int) (h_half + 2 * h_half / 3));

    this->end();
}

void
SetupWindow::
note()
{
    // clear octave reading state.
    if (isUp()) { button_up->copy_label(key2str(bundle->octaveUp).c_str()); }
    else if (isDown()) { button_down->copy_label(key2str(bundle->octaveDown).c_str()); }

    // set note reading state.
    box_note->label(NOTE_TEXT);
    button_note->label(EMPTY_TEXT);
}

void
SetupWindow::
key()
{
    // clear octave reading state.
    if (isUp()) { button_up->copy_label(key2str(bundle->octaveUp).c_str()); }
    else if (isDown()) { button_down->copy_label(key2str(bundle->octaveDown).c_str()); }

    // set key reading state.
    box_note->label(KEY_TEXT);
    button_note->label(EMPTY_TEXT);
}

void
SetupWindow::
down()
{
    // clear up octave reading state.
    if (isUp()) { button_up->copy_label(key2str(bundle->octaveUp).c_str()); }

    // set down octave reading state.
    button_down->label(EMPTY_TEXT);
    Fl::flush();
}

void
SetupWindow::
up()
{
    // clear down octave reading state.
    if (isDown()) { button_down->copy_label(key2str(bundle->octaveDown).c_str()); }

    // set up octave reading state.
    button_up->label(EMPTY_TEXT);
    Fl::flush();
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

bool
SetupWindow::
isDown() const
{
    return button_down->label() == EMPTY_TEXT;
}

bool
SetupWindow::
isUp() const
{
    return button_up->label() == EMPTY_TEXT;
}

int
SetupWindow::
handle(int e)
{
    if (e == FL_KEYUP) {
        if (isDown() || isUp() || isKey()) {
            // check if key up exists in map or octave keys.
            auto exists = [this](Key key) {
                if (key == bundle->octaveDown || key == bundle->octaveUp) { return true; }
                auto it = std::find_if(
                    bundle->noteKeyMap->begin(), bundle->noteKeyMap->end(),
                    [key](const auto &kv) { return kv.second == key; }
                );

                if (it != bundle->noteKeyMap->end()) { return true; }

                return false;
            };

            auto key = fltk2key(Fl::event_key());

            Fl_Button *button = button_note;
            Key *dst = &bundle->key;

            if (isDown()) {
                button = button_down;
                dst = &bundle->octaveDown;
            } else if (isUp()) {
                button = button_up;
                dst = &bundle->octaveUp;
            }

            if (!exists(key)) { 
                // check current button labels.
                auto s = key2str(key);
                if (isDown() || isUp()) {
                    if (s != std::string(button_note->label())) {
                        *dst = key;
                    }
                } else if (isKey()) {
                    if (!(s == std::string(button_down->label()) 
                       || s == std::string(button_up->label()))) {
                        *dst = key;
                    }
                }
            }

            button->copy_label(key2str(*dst).c_str());
            return 1;
        }
    }
    return Fl_Window::handle(e);
}

} // namespace midimap