#include "midimap/midimap.hh"

#include <iostream>

namespace mm = midimap;

int main(int argc, char **argv) {
    mm::Controller ctrl;
    auto names = ctrl.getPortNames();

    for (auto const &name : names) {
        std::cout << name << "\n";
    }

    return 0;
}
