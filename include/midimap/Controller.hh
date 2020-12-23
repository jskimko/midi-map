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
    bool openPort(int port);

    void start();
    void stop();

private:
    static void callback(double dt, std::vector<unsigned char> *msg, void *data);

    RtMidiIn *input;
};

} // namespace midimap

#endif // MIDIMAP_CONTROLLER_HH
