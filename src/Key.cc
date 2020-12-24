#include "midimap/Key.hh"

#ifdef _WIN32
#include <windows.h>
#include <winuser.h>
#else // assume X11
#include <X11/extensions/XTest.h>
#endif // _WIN32

namespace midimap {

std::string key2str(Key key)
{
    static const char *KeyNames[] = {
        "~", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\\",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Enter",
        "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/",
        "Shift", "Control", "Alt", "Space", "Up", "Down", "Left", "Right",
        "None"
    };
    return KeyNames[static_cast<int>(key)];
}

#ifdef _WIN32

Key 
readKey()
{
    return Key::None;
}

#else // assume X11

Key 
readKey()
{
    return Key::None;
}

#endif // _WIN32

} // namespace midimap
