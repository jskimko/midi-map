#include "midimap/Keyboard.hh"

namespace midimap {

Keyboard::
Keyboard()
#if defined _WIN32
#elif defined XLIB
    : display(XOpenDisplay(nullptr))
#endif
{
}

Keyboard::
~Keyboard()
{
#if defined _WIN32
#elif defined XLIB
    if (display) { XCloseDisplay(display); }
#endif
}

} // namespace midimap