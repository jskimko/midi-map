#ifndef MIDIMAP_CONVERTER_HH
#define MIDIMAP_CONVERTER_HH

#include <string>
#include <map>

namespace midimap {

enum class Key {
    Tilde, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Zero, Dash, Equal, Backspace,
    Q, W, E, R, T, Y, U, I, O, P, LeftBracket, RightBracket, Backslash,
    A, S, D, F, G, H, J, K, L, SemiColon, SingleQuote, Enter,
    Z, X, C, V, B, N, M, Comma, Period, Slash,
    Shift, Control, Alt, Space, Up, Down, Left, Right,
    None
};

class Converter {
public:
    Converter();

    std::string symbol(unsigned char num) const;
    Key readKey() const;

    void insert(std::string sym, Key key);

private:
    static std::map<unsigned char, std::string> num2sym;

    std::map<std::string, Key> sym2key;
    Key octaveUp;
    Key octaveDown;
};

} // namespace midimap

#endif // MIDIMAP_CONVERTER_HH