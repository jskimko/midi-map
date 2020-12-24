#ifndef MIDIMAP_HH
#define MIDIMAP_HH

#include "midimap/Controller.hh"

class Fl_Window;

namespace midimap {

class MidiMap {
public:
    static constexpr char *TITLE = "MidiMap";
    static constexpr int FONT_SIZE = 10;

    bool run();

private:
    void draw();

    Fl_Window *window;
};

} // namespace midimap

#endif // MIDIMAP_HH
