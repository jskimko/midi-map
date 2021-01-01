#ifndef MIDIMAP_SETUPWINDOW_HH
#define MIDIMAP_SETUPWINDOW_HH

#include "midimap/Key.hh"

#include "FL/Fl.H"
#include "FL/Fl_Window.H"

class Fl_Box;
class Fl_Button;

namespace midimap {

struct Bundle;

struct SetupWindow : public Fl_Window {
public:
    static constexpr char *NOTE_TEXT   = "Play a note:";
    static constexpr char *KEY_TEXT    = "Press a key:";
    static constexpr char *OCTAVE_TEXT = "Octave:";
    static constexpr char *EMPTY_TEXT  = "";

    SetupWindow(int w, int h);

    void note();
    void key();
    void down();
    void up();

    bool isNote() const;
    bool isKey() const;
    bool isEmpty() const;
    bool isDown() const;
    bool isUp() const;

    virtual int handle(int e) override;

    Fl_Box    *box_note;
    Fl_Button *button_note;

    Fl_Box    *box_octave;
    Fl_Button *button_down;
    Fl_Button *button_up;

    Bundle *bundle;
};

} // namespace midimap

#endif MIDIMAP_SETUPWINDOW_HH