#include "midimap/Converter.hh"

namespace midimap {

std::unordered_map<unsigned char, std::string> Converter::num2sym = {
    // octave 0
    { 21, "A"},
    { 22, "A#"},
    { 23, "B"},
    { 24, "C"},
    { 25, "C#"},
    { 26, "D"},
    { 27, "D#"},
    { 28, "E"},
    { 29, "F"},
    { 30, "F#"},
    { 31, "G"},
    { 32, "G#"}
};

unsigned char
Converter::
octave(unsigned char num)
{
    // A0 == 21, 12 half steps per octave
    return (num - 21) / 12;
}

std::string 
Converter::
symbol(unsigned char num)
{
    // A0 == 21, 12 half steps per octave
    auto note = [](unsigned char n) { return ((n - 21) % 12) + 21; };
    return num2sym.at(note(num)) + std::to_string(octave(num));
}

} // namespace midimap