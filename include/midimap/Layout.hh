#ifndef MIDIMAP_LAYOUT_HH
#define MIDIMAP_LAYOUT_HH

class Fl_Window;
class Fl_Box;
class Fl_Choice;
class Fl_Output;
class Fl_Button;
class Fl_Input;

namespace midimap {

struct SetupWindow;

struct Layout {
    static constexpr char *TITLE_TEXT = "MidiMap";
    static constexpr int FONT_SIZE    = 10;

    void draw();
    void show();
    void deactivate();

    Fl_Window *window;
    Fl_Box    *box_choice;
    Fl_Choice *choice;
    Fl_Output *output;
    Fl_Button *button_setup;
    Fl_Button *button_start;
    Fl_Button *button_import;
    Fl_Button *button_export;
    Fl_Input  *input_import;
    Fl_Input  *input_export;

    SetupWindow *setup;
};

} // namespace midimap

#endif // MIDIMAP_LAYOUT_HH