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

Key fltk2key(int k)
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

#if defined _WIN32
WORD key2win(Key key)
{
    static std::unordered_map<Key, WORD> winMap = {
        { Key::BACKTICK , VK_OEM_3},
        { Key::ONE , 0x31 },
        { Key::TWO , 0x32 },
        { Key::THREE , 0x33 },
        { Key::FOUR , 0x34 },
        { Key::FIVE , 0x35 },
        { Key::SIX , 0x36 },
        { Key::SEVEN , 0x37 },
        { Key::EIGHT , 0x38 },
        { Key::NINE , 0x39 },
        { Key::ZERO , 0x30 },
        { Key::DASH , VK_OEM_MINUS },
        { Key::EQUAL , VK_OEM_PLUS },
        { Key::BACKSPACE , VK_BACK },
        { Key::TAB , VK_TAB },
        { Key::Q , 0x51 },
        { Key::W , 0x57 },
        { Key::E , 0x45 },
        { Key::R , 0x52 },
        { Key::T , 0x54 },
        { Key::Y , 0x59 },
        { Key::U , 0x55 },
        { Key::I , 0x49 },
        { Key::O , 0x4F },
        { Key::P , 0x50 },
        { Key::LEFTBRACKET , VK_OEM_4 },
        { Key::RIGHTBRACKET , VK_OEM_6 },
        { Key::BACKSLASH , VK_OEM_5 },
        { Key::CAPSLOCK , VK_CAPITAL },
        { Key::A , 0x41 },
        { Key::S , 0x53 },
        { Key::D , 0x44 },
        { Key::F , 0x46 },
        { Key::G , 0x47 },
        { Key::H , 0x48 },
        { Key::J , 0x4A },
        { Key::K , 0x4B },
        { Key::L , 0x4C },
        { Key::SEMICOLON , VK_OEM_1 },
        { Key::SINGLEQUOTE , VK_OEM_7 },
        { Key::ENTER , VK_RETURN },
        { Key::SHIFT_L , VK_LSHIFT },
        { Key::Z , 0x5A },
        { Key::X , 0x58 },
        { Key::C , 0x43 },
        { Key::V , 0x56 },
        { Key::B , 0x42 },
        { Key::N , 0x4E },
        { Key::M , 0x4D },
        { Key::COMMA , VK_OEM_COMMA },
        { Key::PERIOD , VK_OEM_PERIOD },
        { Key::SLASH , VK_OEM_2 },
        { Key::SHIFT_R , VK_RSHIFT },
        { Key::CONTROL_L , VK_LCONTROL },
        { Key::META_L , VK_MENU },
        { Key::ALT_L , VK_MENU },
        { Key::SPACE , VK_SPACE },
        { Key::ALT_R , VK_MENU },
        { Key::META_R , VK_MENU },
        { Key::CONTROL_R , VK_RCONTROL },
        { Key::UP , VK_UP },
        { Key::DOWN , VK_DOWN },
        { Key::LEFT , VK_LEFT },
        { Key::RIGHT , VK_RIGHT },
        { Key::ESCAPE , VK_ESCAPE },
        { Key::PRINTSCREEN , VK_SNAPSHOT },
        { Key::SCROLLLOCK , VK_SCROLL },
        { Key::PAUSE , VK_PAUSE },
        { Key::NUMLOCK , VK_NUMLOCK },
        { Key::INSERT , VK_INSERT },
        { Key::HOME , VK_HOME },
        { Key::PAGEUP , VK_PRIOR }, 
        { Key::DELETE_ , VK_DELETE },
        { Key::END , VK_END },
        { Key::PAGEDOWN , VK_NEXT }
    };

    auto it = winMap.find(key);
    if (it != winMap.end()) {
        return (*it).second;
    } else { 
        return 0x0F; // unassigned
    }
}
#elif defined XLIB
int key2x11(Key key)
{
    static std::unordered_map<Key, WORD> x11Map = {
        { Key::BACKTICK , XK_grave },
        { Key::ONE , XK_1 },
        { Key::TWO , XK_2 },
        { Key::THREE , XK_3 },
        { Key::FOUR , XK_4 },
        { Key::FIVE , XK_5 },
        { Key::SIX , XK_7 },
        { Key::SEVEN , XK_7 },
        { Key::EIGHT , XK_8 },
        { Key::NINE , XK_9 },
        { Key::ZERO , XK_0 },
        { Key::DASH , XK_minus },
        { Key::EQUAL , XK_equal },
        { Key::BACKSPACE , XK_BackSpace },
        { Key::TAB , XK_Tab },
        { Key::Q , XK_q },
        { Key::W , XK_w },
        { Key::E , XK_e },
        { Key::R , XK_r },
        { Key::T , XK_t },
        { Key::Y , XK_y },
        { Key::U , XK_u },
        { Key::I , XK_i },
        { Key::O , XK_o },
        { Key::P , XK_p },
        { Key::LEFTBRACKET , XK_bracketleft },
        { Key::RIGHTBRACKET , XK_bracketright },
        { Key::BACKSLASH , XK_backslash },
        { Key::CAPSLOCK , XK_Caps_Lock },
        { Key::A , XK_a },
        { Key::S , XK_s },
        { Key::D , XK_d },
        { Key::F , XK_f },
        { Key::G , XK_g },
        { Key::H , XK_h },
        { Key::J , XK_j },
        { Key::K , XK_k },
        { Key::L , XK_l },
        { Key::SEMICOLON , XK_semicolon },
        { Key::SINGLEQUOTE , XK_apostrophe },
        { Key::ENTER , XK_Return },
        { Key::SHIFT_L , XK_Shift_L },
        { Key::Z , XK_z },
        { Key::X , XK_x },
        { Key::C , XK_c },
        { Key::V , XK_v },
        { Key::B , XK_b },
        { Key::N , XK_n },
        { Key::M , XK_m },
        { Key::COMMA , XK_comma },
        { Key::PERIOD , XK_period },
        { Key::SLASH , XK_slash },
        { Key::SHIFT_R , XK_Shift_R },
        { Key::CONTROL_L , XK_Control_L },
        { Key::META_L , XK_Meta_L },
        { Key::ALT_L , XK_Alt_L },
        { Key::SPACE , XK_space },
        { Key::ALT_R , XK_Alt_R },
        { Key::META_R , XK_Meta_R },
        { Key::CONTROL_R , XK_Control_R },
        { Key::UP , XK_Up },
        { Key::DOWN , XK_Down },
        { Key::LEFT , XK_Left },
        { Key::RIGHT , XK_Right },
        { Key::ESCAPE , XK_Escape },
        { Key::PRINTSCREEN , XK_Print },
        { Key::SCROLLLOCK , XK_Scroll_Lock },
        { Key::PAUSE , XK_Pause },
        { Key::NUMLOCK , XK_Num_Lock },
        { Key::INSERT , XK_Insert },
        { Key::HOME , XK_Home },
        { Key::PAGEUP , XK_Prior }, 
        { Key::DELETE_ , XK_Delete },
        { Key::END , XK_End },
        { Key::PAGEDOWN , XK_Next }
    };

    auto it = x11Map.find(key);
    if (it != x11Map.end()) {
        return (*it).second;
    } else { 
        return XK_VoidSymbol;
    }
}
#endif

} // namespace midimap
