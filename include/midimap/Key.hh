#ifndef MIDIMAP_KEY_HH
#define MIDIMAP_KEY_HH

#include <string>

namespace midimap {

enum class Key {
    TILDE, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, DASH, EQUAL, BACKSPACE,
    Q, W, E, R, T, Y, U, I, O, P, LEFTBRACKET, RIGHTBRACKET, BACKSLASH,
    A, S, D, F, G, H, J, K, L, SEMICOLON, SINGLEQUOTE, ENTER,
    Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH,
    SHIFT, CONTROL, ALT, SPACE, UP, DOWN, LEFT, RIGHT,
    NONE
};

std::string key2str(Key key);
Key readKey();

} // namespace midimap

#endif // MIDIMAP_KEY_HH
