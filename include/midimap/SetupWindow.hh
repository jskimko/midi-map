#ifndef MIDIMAP_SETUPWINDOW_HH
#define MIDIMAP_SETUPWINDOW_HH

#include "FL/Fl.H"
#include "FL/Fl_Window.H"

class Fl_Box;
class Fl_Button;

namespace midimap {

struct SetupWindow : public Fl_Window {
public:
    static constexpr char *NOTE_TEXT  = "Play a note:";
    static constexpr char *KEY_TEXT   = "Press a key:";
    static constexpr char *EMPTY_TEXT = "";

    SetupWindow(int w, int h);

    void note();
    void key();
    bool isNote() const;
    bool isKey() const;
    bool isEmpty() const;

    virtual int handle(int e) override;

    Fl_Box    *box;
    Fl_Button *button;
};

} // namespace midimap

#endif MIDIMAP_SETUPWINDOW_HH