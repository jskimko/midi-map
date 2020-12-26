#ifndef MIDIMAP_CONTROLLER_HH
#define MIDIMAP_CONTROLLER_HH

#include "midimap/Converter.hh"
#include "midimap/Key.hh"

#include <vector>
#include <string>

class RtMidiIn;
class Fl_Widget;

namespace midimap {

struct Bundle;

class Controller {
public:
    Controller();
    ~Controller();

    std::vector<std::string> getPortNames() const;
    bool openPort(int port);
    void closePort();

    void read(Bundle &bundle);
    void convert(Bundle &bundle);
    void stop();

private:
    static void convertCallback(double dt, std::vector<unsigned char> *msg, void *data);
    static void readCallback(double dt, std::vector<unsigned char> *msg, void *data);

    RtMidiIn *input;
    Converter converter;
};

} // namespace midimap

#endif // MIDIMAP_CONTROLLER_HH
