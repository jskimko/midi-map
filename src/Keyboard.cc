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
#elif defined XLIB
    if (display) { XCloseDisplay(display); }
#endif
}

bool
Keyboard::
sendKey(Key key) const
{
#if defined _WIN32
    INPUT inputs[2];
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key2win(key);

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = key2win(key);
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    return SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT)) == ARRAYSIZE(inputs);
#elif defined XLIB
    if (!display) { return false; }

    #if defined XTEST
        XTestFakeKeyEvent(display, key2x11(key), 1, 0);
        XTestFakeKeyEvent(display, key2x11(key), 0, 0);
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
        event.keycode = key2x11(key);

        event.type = KeyPress;
        XSendEvent(event.display, event.window, True, KeyPressMask, &event);

        event.type = KeyRelease;
        XSendEvent(event.display, event.window, True, KeyPressMask, &event);
    #endif

    return true;
#endif
}

} // namespace midimap