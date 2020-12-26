#ifndef MIDIMAP_BUNDLE_HH
#define MIDIMAP_BUNDLE_HH

#include "midimap/Key.hh"
#include <unordered_map>

class Fl_Widget;

namespace midimap {

class Controller;

struct Bundle {
    // Owned data.
    std::unordered_map<unsigned char, Key> note2key;

    // Buffers.
    Controller *controller;
    Fl_Widget *widget;
    Key key;
};

} // namespace midi

#endif // MIDIMAP_BUNDLE_HH