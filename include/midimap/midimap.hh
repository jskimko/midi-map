#ifndef MIDIMAP_HH
#define MIDIMAP_HH

#include "midimap/Controller.hh"
#include "midimap/Layout.hh"

namespace midimap {

class Attorney;
struct RegisterCallbacks;

class MidiMap {
public:
    bool run();

private:
    friend Attorney;
    Layout& layout() { return layout_; }
    Controller& controller() { return controller_; }

    void register_callbacks();

    Controller controller_;
    Layout layout_;
};

class Attorney {
private:
    static Layout& layout(MidiMap &client) { return client.layout(); }
    static Controller& controller(MidiMap &client) { return client.controller(); }
    friend RegisterCallbacks;
};

} // namespace midimap

#endif // MIDIMAP_HH
