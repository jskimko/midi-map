#include "midimap/Converter.hh"

#ifdef _WIN32
#include <windows.h>
#include <winuser.h>
#else // assume X11
#include <X11/extensions/XTest.h>
#endif // _WIN32

namespace midimap {

std::map<unsigned char, std::string> Converter::num2sym = {
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

Converter::
Converter()
    : octaveUp(Key::None),
      octaveDown(Key::None)
{
}

std::string 
Converter::
symbol(unsigned char num) const
{
    auto octave = [](unsigned char n) { return (n - 21) / 12; };
    return num2sym.at(num) + std::to_string(octave(num));
}

#ifdef _WIN32

Key 
Converter::
readKey() const
{
    return Key::None;
}

#else // assume X11

Key 
Converter::
readKey() const
{
    return Key::None;
}

#endif // _WIN32

} // namespace midimap