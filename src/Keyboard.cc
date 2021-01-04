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
    if (t.joinable()) { return; }

    p = {};
    t = std::thread([this](decltype(p.get_future()) f) {
        while (f.wait_for(std::chrono::seconds(0)) != std::future_status::ready) 
        {
            {
                std::lock_guard<std::mutex> lock(this->m);
                if (inputs.size()) {
                    SendInput(inputs.size(), inputs.data(), sizeof(INPUT));
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }, p.get_future());
}

void
Keyboard::
stop() 
{
    if (!t.joinable()) { return; }

    p.set_value();
    t.join();
}

} // namespace midimap