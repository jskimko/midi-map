#include "midimap/midimap.hh"
#include "FL/Fl.H"
#include "FL/Fl_Window.H"

#include <cstdio>

namespace midimap {

MidiMap::
MidiMap()
    : window(new Fl_Window(400, 300, TITLE))
{
}

bool 
MidiMap::
run()
{
    window->end();
    window->show();
    return Fl::run();
}

} // namespace midimap
