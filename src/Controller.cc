#include "midimap/Controller.hh"
#include "RtMidi.h"
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <bitset>

namespace midimap {

Controller::
Controller() 
    : input(new RtMidiIn()),
      converter()
{
}

Controller::
~Controller() 
{
    if (input) { delete input; }
}

std::vector<std::string>
Controller::
getPortNames() const
{
    std::vector<std::string> ret;

    auto n = input->getPortCount();
    for (decltype(n) i=0; i<n; i++) {
        try {
            ret.push_back(input->getPortName(i));
        } catch (RtMidiError &e) {
            std::string s = "(error) " + e.getMessage();
            ret.push_back(s);
        }
    }

    return ret;
}

bool 
Controller::
openPort(int port)
{
    try {
        input->openPort(port);
		return true;
    } catch (RtMidiError &e) {
        fprintf(stderr, "Controller::openPort: %s\n", e.what());
        return false;
    }
}

void 
Controller::
callback(double dt, std::vector<unsigned char> *msg, void *data)
{
    if (msg->size() == 0) { return; }

    std::stringstream ss;
//    int val = 0;
//    for (int i=0u; i<msg->size(); i++) {
//        val |= ((*msg)[i] << (i*8));
//   }
//    ss << "ts: " << dt << "\n";
    ss << std::hex << std::setfill('0');
    unsigned char stat = (*msg)[0] & 0xF0;
    if (stat == 0x80 || stat == 0x90) {
        for (int b : *msg) {
            ss << std::setw(2) << b << " ";
        }
        ss << "\n";
    }
//    ss << val << "\n";
//    for (int b : *msg) {
//        ss << std::setw(2) << b << " ";
//    }
//    ss << "\n";
//    for (auto b : *msg) {
//        ss << std::bitset<8>(b) << " ";
//    }
    std::cout << ss.str();
}

void 
Controller::
start()
{
    input->setCallback(&callback);
    //input->ignoreTypes(false, false, false);
}

void 
Controller::
stop()
{
    input->cancelCallback();
}

} // namespace midimap
