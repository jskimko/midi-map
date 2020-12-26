#include "midimap/Key.hh"

#include "FL/Fl.H"
#include "FL/Enumerations.H"

#include <unordered_map>

namespace midimap {

std::string key2str(Key key)
{
    static const char *KeyNames[] = {
        "`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BackSpace",
        "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\\",
        "CapsLock", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Enter",
        "Shift_L", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Shift_R",
        "Control_L", "Meta_L", "Alt_L", "Space", "Alt_R", "Meta_R", "Control_R", 
        "Up", "Down", "Left", "Right",
        "Escape", "PrintScreen", "ScrollLock", "Pause", "NumLock",
        "Insert", "Home", "PageUp", 
        "Delete", "End", "PageDown",
        "None"
    };
    return KeyNames[static_cast<int>(key)];
}

Key 
fltk2key(int k)
{
    static std::unordered_map<int, Key> fltkMap = {
        { 96, Key::BACKTICK },
        { 49, Key::ONE },
        { 50, Key::TWO },
        { 51, Key::THREE },
        { 52, Key::FOUR },
        { 53, Key::FIVE },
        { 54, Key::SIX },
        { 55, Key::SEVEN },
        { 56, Key::EIGHT },
        { 57, Key::NINE },
        { 48, Key::ZERO },
        { 45, Key::DASH },
        { 61, Key::EQUAL },
        { FL_BackSpace, Key::BACKSPACE },
        { FL_Tab, Key::TAB },
        { 113, Key::Q },
        { 119, Key::W },
        { 101, Key::E },
        { 114, Key::R },
        { 116, Key::T },
        { 121, Key::Y },
        { 117, Key::U },
        { 105, Key::I },
        { 111, Key::O },
        { 112, Key::P },
        { 91, Key::LEFTBRACKET },
        { 93, Key::RIGHTBRACKET },
        { 92, Key::BACKSLASH },
        { FL_Caps_Lock, Key::CAPSLOCK },
        { 97, Key::A },
        { 115, Key::S },
        { 100, Key::D },
        { 102, Key::F },
        { 103, Key::G },
        { 104, Key::H },
        { 106, Key::J },
        { 107, Key::K },
        { 108, Key::L },
        { 59, Key::SEMICOLON },
        { 39, Key::SINGLEQUOTE },
        { FL_Enter, Key::ENTER },
        { FL_Shift_L, Key::SHIFT_L },
        { 122, Key::Z },
        { 120, Key::X },
        { 99, Key::C },
        { 118, Key::V },
        { 98, Key::B },
        { 110, Key::N },
        { 109, Key::M },
        { 44, Key::COMMA },
        { 46, Key::PERIOD },
        { 47, Key::SLASH },
        { FL_Shift_R, Key::SHIFT_R },
        { FL_Control_L, Key::CONTROL_L },
        { FL_Meta_L, Key::META_L },
        { FL_Alt_L, Key::ALT_L },
        { 32, Key::SPACE },
        { FL_Alt_R, Key::ALT_R },
        { FL_Meta_R, Key::META_R },
        { FL_Control_R, Key::CONTROL_R },
        { FL_Up, Key::UP },
        { FL_Down, Key::DOWN },
        { FL_Left, Key::LEFT },
        { FL_Right, Key::RIGHT },
        { FL_Escape, Key::ESCAPE },
        { FL_Print, Key::PRINTSCREEN },
        { FL_Scroll_Lock, Key::SCROLLLOCK },
        { FL_Pause, Key::PAUSE },
        { FL_Num_Lock, Key::NUMLOCK },
        { FL_Insert, Key::INSERT },
        { FL_Home, Key::HOME },
        { FL_Page_Up, Key::PAGEUP }, 
        { FL_Delete, Key::DELETE_ },
        { FL_End, Key::END },
        { FL_Page_Down, Key::PAGEDOWN }
    };

    auto it = fltkMap.find(k);
    if (it != fltkMap.end()) {
        return (*it).second;
    } else { 
        return Key::NONE;
    }
}

} // namespace midimap
