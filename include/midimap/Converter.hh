#ifndef MIDIMAP_CONVERTER_HH
#define MIDIMAP_CONVERTER_HH

#include "midimap/Key.hh"

#include <string>
#include <unordered_map>

namespace midimap {

class Converter {
public:
    static unsigned char octave(unsigned char num);
    static std::string symbol(unsigned char num);

    void insert(std::string sym, Key key);

private:
    static std::unordered_map<unsigned char, std::string> num2sym;
};

} // namespace midimap

#endif // MIDIMAP_CONVERTER_HH