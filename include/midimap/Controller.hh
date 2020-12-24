#ifndef MIDIMAP_CONTROLLER_HH
#define MIDIMAP_CONTROLLER_HH

#include "midimap/Converter.hh"
#include "midimap/Key.hh"

#include <vector>
#include <string>

class RtMidiIn;

namespace midimap {

class Controller {
public:
    Controller();
    ~Controller();

    std::vector<std::string> getPortNames() const;
    bool openPort(int port);

    void setup();
    void convert();
    void stop();

private:
    static void applyMap(double dt, std::vector<unsigned char> *msg, void *data);
    static void setupMap(double dt, std::vector<unsigned char> *msg, void *data);

    RtMidiIn *input;
    Converter converter;
};

} // namespace midimap

#endif // MIDIMAP_CONTROLLER_HH
