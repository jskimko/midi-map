#ifndef MIDIMAP_HH
#define MIDIMAP_HH

#include "midimap/Controller.hh"
#include "midimap/Layout.hh"

namespace midimap {

class Attorney;
class RegisterCallbacks;

class MidiMap {
public:
    bool run();

private:
    friend Attorney;
    Layout& layout() { return layout_; }

    void register_callbacks();

    Controller controller;
    Layout layout_;
};

class Attorney {
private:
    static Layout& layout(MidiMap &client) { return client.layout(); }
    friend RegisterCallbacks;
};

} // namespace midimap

#endif // MIDIMAP_HH
