#ifndef MIDIMAP_HH
#define MIDIMAP_HH

#include "midimap/Controller.hh"
#include "midimap/Layout.hh"
#include "midimap/Bundle.hh"

namespace midimap {

class Attorney;
struct RegisterCallbacks;

class MidiMap {
public:
    bool run();

private:
    void register_callbacks();

    friend Attorney;
    Controller& controller() { return controller_; }
    Layout& layout() { return layout_; }
    Bundle& bundle() { return bundle_; }

    Controller controller_;
    Layout layout_;
    Bundle bundle_;
};

class Attorney {
private:
    static Layout& layout(MidiMap &client) { return client.layout(); }
    static Controller& controller(MidiMap &client) { return client.controller(); }
    static Bundle& bundle(MidiMap &client) { return client.bundle(); }
    friend RegisterCallbacks;
};

} // namespace midimap

#endif // MIDIMAP_HH
