#ifndef MIDIMAP_KEYBOARD_HH
#define MIDIMAP_KEYBOARD_HH

#include "midimap/Key.hh"

#include <array>
#include <future>

namespace midimap {

class Keyboard {
public:
    Keyboard();
    ~Keyboard();

    template <int N, bool Press>
    void sendKeys(std::array<Key, N> keys);

    void start();
    void stop();

private:
    std::promise<void> p;
    std::thread t;
    std::mutex m;

#if defined _WIN32
    std::vector<INPUT> inputs;
#elif defined XLIB
    Display *display;
#endif
};

template <int N, bool Press>
void
Keyboard::
sendKeys(std::array<Key, N> keys)
{
#if defined _WIN32
    if constexpr (Press) {
        INPUT in[N];
        ZeroMemory(in, sizeof(in));

        for (decltype(N) i=0; i<N; i++) {
            in[i].type = INPUT_KEYBOARD;
            in[i].ki.wVk = key2win(keys[i]);
        }

        // send initial keypress asap.
        SendInput(ARRAYSIZE(in), in, sizeof(INPUT));

        // update the repeater.
        {
            std::lock_guard<std::mutex> lock(m);
            auto size = inputs.size();
            inputs.resize(size + N);
            CopyMemory(inputs.data() + size, in, sizeof(in));
        }
    } else {
        // stop the repeater asap.
        std::array<decltype(key2win(keys.front())), N> wins;
        std::transform(keys.begin(), keys.end(), wins.begin(), key2win);
        {
            std::lock_guard<std::mutex> lock(m);
            inputs.erase(std::remove_if(inputs.begin(), inputs.end(), [&wins](auto const &input) {
                return std::find(wins.begin(), wins.end(), input.ki.wVk) != wins.end();
            }), inputs.end());
        }

        // send keyup.
        INPUT in[N];
        ZeroMemory(in, sizeof(in));

        for (decltype(N) i=0; i<N; i++) {
            in[i].type = INPUT_KEYBOARD;
            in[i].ki.wVk = key2win(keys[i]);
            in[i].ki.dwFlags = KEYEVENTF_KEYUP;
        }

        SendInput(ARRAYSIZE(in), in, sizeof(INPUT));
    }
    
#elif defined XLIB
    if (!display) { return false; }

#if defined XTEST
    for (decltype(N) i=0; i<N; i++) {
        XTestFakeKeyEvent(display, key2x11(keys[i]), 1, 0);
    }

    for (decltype(N) i=N; i<N*2; i++) {
        XTestFakeKeyEvent(display, key2x11(keys[N - (i % N) - 1]), 0, 0);
    }

    XFlush(display);
#else
    Window root = XDefaultRootWindow(display);

    Window focus;
    XGetInputFocus(display, &focus, nullptr);

    XKeyEvent event;
    event.display = display;
    event.window = focus;
    event.root = root;
    event.subwindow = None;
    event.time = CurrentTime;
    event.x = 1;
    event.y = y;
    event.x_root = 1;
    event.y_root = 1;
    event.same_screen = True;
    event.state = 0;

    event.type = KeyPress;
    for (decltype(N) i=0; i<N; i++) {
        event.keycode = key2x11(keys[i]);
        XSendEvent(event.display, event.window, True, KeyPressMask, &event);
    }

    event.type = KeyRelease;
    for (decltype(N) i=N; i<N*2; i++) {
        event.keycode = key2x11(keys[N - (i % N) - 1]);
        XSendEvent(event.display, event.window, True, KeyPressMask, &event);
    }
#endif

    return true;
#endif
}

} // namespace midimap

#endif // MIDIMAP_KEYBOARD_HH
