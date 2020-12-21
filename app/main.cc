#include "midimap/midimap.hh"

int main(int argc, char **argv) {

    RtMidiIn  *midiin = 0;
    RtMidiOut *midiout = 0;
  
    // RtMidiIn constructor
    try {
      midiin = new RtMidiIn();
    }
    catch ( RtMidiError &error ) {
      error.printMessage();
      exit( EXIT_FAILURE );
    }
  
    // Check inputs.
    unsigned int nPorts = midiin->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
    std::string portName;
    for ( unsigned int i=0; i<nPorts; i++ ) {
      try {
        portName = midiin->getPortName(i);
      }
      catch ( RtMidiError &error ) {
        error.printMessage();
        goto cleanup;
      }
      std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
    }

    return 0;
}
