#ifndef MIDIMAP_KEY_HH
#define MIDIMAP_KEY_HH

#include <string>

namespace midimap {

enum class Key {
    Tilde, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Zero, Dash, Equal, Backspace,
    Q, W, E, R, T, Y, U, I, O, P, LeftBracket, RightBracket, Backslash,
    A, S, D, F, G, H, J, K, L, SemiColon, SingleQuote, Enter,
    Z, X, C, V, B, N, M, Comma, Period, Slash,
    Shift, Control, Alt, Space, Up, Down, Left, Right,
    None
};

std::string key2str(Key key);
Key readKey();

} // namespace midimap

#endif // MIDIMAP_KEY_HH
