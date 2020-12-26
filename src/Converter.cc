#include "midimap/Converter.hh"

namespace midimap {

std::unordered_map<unsigned char, std::string> Converter::num2sym = {
    // octave 0
    { 21, "A"},
    { 22, "A#/Bb"},
    { 23, "B"},
    { 24, "C"},
    { 25, "C#/Db"},
    { 26, "D"},
    { 27, "D#/Eb"},
    { 28, "E"},
    { 29, "F"},
    { 30, "F#/Gb"},
    { 31, "G"},
    { 32, "G#/Ab"}
};

std::string 
Converter::
symbol(unsigned char num)
{
    auto note = [](unsigned char n) { return ((n - 21) % 12) + 21; };
    auto octave = [](unsigned char n) { return (n - 21) / 12; };
    return num2sym.at(note(num)) + std::to_string(octave(num));
}

Converter::
Converter()
    : octaveUp(Key::NONE),
      octaveDown(Key::NONE)
{
}

} // namespace midimap