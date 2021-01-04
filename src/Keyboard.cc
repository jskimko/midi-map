#include "midimap/Keyboard.hh"

namespace midimap {

Keyboard::
Keyboard()
#if defined _WIN32
#elif defined XLIB
    : display(XOpenDisplay(nullptr))
#endif
{
}

Keyboard::
~Keyboard()
{
#if defined _WIN32
    stop();
#elif defined XLIB
    if (display) { XCloseDisplay(display); }
#endif
}

void
Keyboard::
start() 
{
    // check if already started.
    if (t.joinable()) { return; }

    // reset the promise and launch a new thread.
    p = {};
    t = std::thread([this](decltype(p.get_future()) f) {
        while (f.wait_for(std::chrono::seconds(0)) != std::future_status::ready) 
        {
            // repeat the existing key downs.
            {
                std::lock_guard<std::mutex> lock(this->m);
                if (inputs.size()) {
                    SendInput(inputs.size(), inputs.data(), sizeof(INPUT));
                }
            }

            // hardcoded delay. maybe there is a way to get the system's keyboard tick?
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }, p.get_future());
}

void
Keyboard::
stop() 
{
    // check if already stopped.
    if (!t.joinable()) { return; }

    // stop the thread.
    p.set_value();
    t.join();
}

} // namespace midimap