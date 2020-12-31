#ifndef MIDIMAP_KEYBOARD_HH
#define MIDIMAP_KEYBOARD_HH

#include "midimap/Key.hh"

namespace midimap {

class Keyboard {
public:
    Keyboard();
    ~Keyboard();

    bool sendKey(Key key) const;

private:
#if defined XLIB
    Display *display;
#endif
};

} // namespace midimap

#endif // MIDIMAP_KEYBOARD_HH
