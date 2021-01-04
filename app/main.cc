#include "midimap/midimap.hh"

#include <iostream>

namespace mm = midimap;

int main(int argc, char** argv) {
    mm::MidiMap midiMap;
    return midiMap.run();
}
