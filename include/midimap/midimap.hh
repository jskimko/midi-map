#ifndef MIDIMAP_HH
#define MIDIMAP_HH

#include "midimap/Controller.hh"

class Fl_Window;

namespace midimap {

class MidiMap {
public:
    static constexpr char *TITLE = "MidiMap";

    MidiMap();

    bool run();
private:
    Fl_Window *window;
};

} // namespace midimap

#endif // MIDIMAP_HH
