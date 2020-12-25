#include "midimap/midimap.hh"

#include <iostream>

namespace mm = midimap;

int main(int argc, char** argv) {
    mm::MidiMap midiMap;
    return midiMap.run();

//    mm::Controller ctrl;
//
//    auto names = ctrl.getPortNames();
//    if (names.size() == 0) {
//        std::cout << "No ports available.";
//        return 0;
//    }
//
//    std::cout << "Available ports:\n";
//    for (decltype(names.size()) i = 0; i < names.size(); i++) {
//        std::cout << i << ": " << names[i] << "\n";
//    }
//
////    int port = -1;
////    std::cout << "Please select a port: ";
////    std::cin >> port;
////    ctrl.openPort(port);
//    ctrl.openPort(0);
//
//    ctrl.setup();
//
//    std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
//    std::cin.ignore();
//    std::cin.get();
//
//    ctrl.stop();

    return 0;
}
