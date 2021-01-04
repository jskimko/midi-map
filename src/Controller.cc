#include "midimap/Controller.hh"
#include "midimap/Bundle.hh"

#include "RtMidi.h"
#include "FL/Fl.H"
#include "FL/Fl_Button.H"

#include <cstdio>

namespace {
    static constexpr unsigned char NOTE_OFF = 0x80;
    static constexpr unsigned char NOTE_ON  = 0x90;
}

namespace midimap {

Controller::
Controller() 
    : input(new RtMidiIn()),
      converter()
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
            std::string s = "(error) " + e.getMessage();
            ret.push_back(s);
        }
    }

    return ret;
}

bool 
Controller::
openPort(int port)
{
    try {
        input->openPort(port);
		return true;
    } catch (RtMidiError &e) {
        fprintf(stderr, "Controller::openPort: %s\n", e.what());
        return false;
    }
}

void 
Controller::
closePort()
{
    input->closePort();
}

void 
Controller::
readCallback(double dt, std::vector<unsigned char> *msg, void *data)
{
    if (msg->size() == 0) { return; }
    auto *bundle = (Bundle*) data;

    unsigned char status = (*msg)[0] & 0xF0;
    if (status != NOTE_ON) {
        return;
    }

    // save the read note.
    bundle->note = (*msg)[1];

    // update the note button.
    auto sym = Converter::symbol(bundle->note);
    bundle->widget->copy_label(sym.c_str());
    bundle->widget->redraw();
    Fl::flush();
}

void 
Controller::
convertCallback(double dt, std::vector<unsigned char> *msg, void *data)
{
    if (msg->size() == 0) { return; }
    auto *bundle = (Bundle*) data;

    unsigned char status = (*msg)[0] & 0xF0;
    if (status != NOTE_ON && status != NOTE_OFF) {
        return;
    }

    auto on = status == NOTE_ON;
    auto note = (*msg)[1];
    auto &noteKeyMap = *bundle->noteKeyMap;
    auto &keyboard = bundle->controller->keyboard;

    if (noteKeyMap.count(note)) {
        // if the note has a mapped key.
        if (on) { keyboard.sendKeys<1, true>({noteKeyMap[note]}); }
        else    { keyboard.sendKeys<1, false>({noteKeyMap[note]}); }
    } else {
        // else, check if +/- 1 octave is available.
        if ((bundle->octaveDown != Key::NONE) && (Converter::octave(note) == bundle->minOctave - 1)) {
            auto known = note + 12;
            auto it = noteKeyMap.find(known);
            if (it != noteKeyMap.end()) {
                if (on) { keyboard.sendKeys<2, true>({bundle->octaveDown, noteKeyMap[known]}); }
                else    { keyboard.sendKeys<2, false>({noteKeyMap[known], bundle->octaveDown}); }
            }
        } else if ((bundle->octaveUp != Key::NONE) && (Converter::octave(note) == bundle->maxOctave + 1)) {
            auto known = note - 12;
            auto it = noteKeyMap.find(known);
            if (it != noteKeyMap.end()) {
                if (on) { keyboard.sendKeys<2, true>({bundle->octaveUp, noteKeyMap[known]}); }
                else    { keyboard.sendKeys<2, false>({noteKeyMap[known], bundle->octaveUp}); }
            }
        }
    }
}

void 
Controller::
read(Bundle &bundle)
{
    input->setCallback(&readCallback, &bundle);
}

void 
Controller::
convert(Bundle &bundle)
{
    keyboard.start();
    input->setCallback(&convertCallback, &bundle);
}

void 
Controller::
stop()
{
    keyboard.stop();
    input->cancelCallback();
}

} // namespace midimap
