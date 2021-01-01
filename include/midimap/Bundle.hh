#ifndef MIDIMAP_BUNDLE_HH
#define MIDIMAP_BUNDLE_HH

#include "midimap/Key.hh"
#include "midimap/NoteKeyMap.hh"

class Fl_Widget;

namespace midimap {

class Controller;

struct Bundle {
    Controller *controller;
    Fl_Widget  *widget;
    NoteKeyMap *noteKeyMap;

    unsigned char note;
    Key key;
};

} // namespace midi

#endif // MIDIMAP_BUNDLE_HH