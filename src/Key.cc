#include "midimap/Key.hh"
#include "FL/Fl.H"

namespace midimap {

std::string key2str(Key key)
{
    static const char *KeyNames[] = {
        "`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\\",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Enter",
        "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/",
        "Shift", "Control", "Alt", "Space", "Up", "Down", "Left", "Right",
        "None"
    };
    return KeyNames[static_cast<int>(key)];
}

Key 
readKey()
{
    return Key::NONE;
}

} // namespace midimap
