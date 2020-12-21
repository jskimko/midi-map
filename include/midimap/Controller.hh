#ifndef MIDIMAP_CONTROLLER_HH
#define MIDIMAP_CONTROLLER_HH

#include <vector>
#include <string>

class RtMidiIn;

namespace midimap {

class Controller {
public:
    Controller();
    ~Controller();

    std::vector<std::string> getPortNames() const;

private:
    RtMidiIn *input;
};

} // namespace midimap

#endif // MIDIMAP_CONTROLLER_HH
