#include "midimap/Controller.hh"

#include "RtMidi.h"
#include <cstdio>

namespace {
    static constexpr unsigned char NOTE_OFF = 0x80;
    static constexpr unsigned char NOTE_ON  = 0x90;
}

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
setupMap(double dt, std::vector<unsigned char> *msg, void *data)
{
    if (msg->size() == 0) { return; }
    auto *ctrl = (Controller*) data;

    unsigned char status = (*msg)[0];
    if ((status & 0xF0) != NOTE_ON) {
        return;
    }

    auto sym = ctrl->converter.symbol((*msg)[1]);
    std::cout << sym << "\n";

    auto key = readKey();
    std::cout << key2str(key) << "\n";
}

void 
Controller::
applyMap(double dt, std::vector<unsigned char> *msg, void *data)
{
}

void 
Controller::
setup()
{
    input->setCallback(&setupMap, this);
    //input->ignoreTypes(false, false, false);
}

void 
Controller::
convert()
{
    input->setCallback(&applyMap, this);
    //input->ignoreTypes(false, false, false);
}

void 
Controller::
stop()
{
    input->cancelCallback();
}

} // namespace midimap
