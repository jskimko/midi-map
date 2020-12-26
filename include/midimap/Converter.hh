#ifndef MIDIMAP_CONVERTER_HH
#define MIDIMAP_CONVERTER_HH

#include "midimap/Key.hh"

#include <string>
#include <unordered_map>

namespace midimap {

class Converter {
public:
    static std::string symbol(unsigned char num);

    Converter();
    void insert(std::string sym, Key key);

private:
    static std::unordered_map<unsigned char, std::string> num2sym;

    std::unordered_map<std::string, Key> sym2key;
    Key octaveUp;
    Key octaveDown;
};

} // namespace midimap

#endif // MIDIMAP_CONVERTER_HH