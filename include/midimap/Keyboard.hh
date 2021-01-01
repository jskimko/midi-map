#ifndef MIDIMAP_KEYBOARD_HH
#define MIDIMAP_KEYBOARD_HH

#include "midimap/Key.hh"

#include <array>

namespace midimap {

class Keyboard {
public:
    Keyboard();
    ~Keyboard();

    template <int N>
    bool sendKeys(std::array<Key, N> keys) const;

private:
#if defined XLIB
    Display *display;
#endif
};

template <int N>
bool
Keyboard::
sendKeys(std::array<Key, N> keys) const
{
#if defined _WIN32
    INPUT inputs[N*2];
    ZeroMemory(inputs, sizeof(inputs));

    for (decltype(N) i=0; i<N; i++) {
        inputs[i].type = INPUT_KEYBOARD;
        inputs[i].ki.wVk = key2win(keys[i]);
        printf("(( %d\n", key2win(keys[i]));
    }

    for (decltype(N) i=N; i<N*2; i++) {
        inputs[i].type = INPUT_KEYBOARD;
        inputs[i].ki.wVk = key2win(keys[N - (i % N) - 1]);
        inputs[i].ki.dwFlags = KEYEVENTF_KEYUP;
        printf(")) %d\n", key2win(keys[N - (i % N) - 1]));
    }

    return SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT)) == ARRAYSIZE(inputs);
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
