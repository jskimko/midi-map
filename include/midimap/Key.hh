#ifndef MIDIMAP_KEY_HH
#define MIDIMAP_KEY_HH

#include <string>

namespace midimap {

enum class Key {
    BACKTICK, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, DASH, EQUAL, BACKSPACE,
    TAB, Q, W, E, R, T, Y, U, I, O, P, LEFTBRACKET, RIGHTBRACKET, BACKSLASH,
    CAPSLOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, SINGLEQUOTE, ENTER,
    SHIFT_L, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, SHIFT_R,
    CONTROL_L, META_L, ALT_L, SPACE, ALT_R, META_R, CONTROL_R, UP, DOWN, LEFT, RIGHT,
    ESCAPE, PRINTSCREEN, SCROLLLOCK, PAUSE, NUMLOCK,
    INSERT, HOME, PAGEUP, DELETE_, END, PAGEDOWN,
    NONE
};

std::string key2str(Key key);
Key fltk2key(int k);

} // namespace midimap

#endif // MIDIMAP_KEY_HH
