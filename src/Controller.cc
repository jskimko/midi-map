#include "midimap/Controller.hh"
#include "RtMidi.h"

namespace midimap {

Controller::
Controller() 
    : input(new RtMidiIn())
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
            ret.push_back("(error)");
        }
    }

    return ret;
}

} // namespace midimap
