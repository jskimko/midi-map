#ifndef MIDIMAP_KEY_HH
#define MIDIMAP_KEY_HH

#if defined _WIN32
#include <windows.h>
#include <winuser.h>
#elif defined XLIB
#include <X11/Xlib.h>
#include <X11/keysym.h>
#if defined XTEST
#include <X11/extensions/XTest.h>
#endif
#endif

#include <string>

namespace midimap {

enum class Key {
    BACKTICK, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, DASH, EQUAL, BACKSPACE,
    TAB, Q, W, E, R, T, Y, U, I, O, P, LEFTBRACKET, RIGHTBRACKET, BACKSLASH,
    CAPSLOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, SINGLEQUOTE, ENTER,
    SHIFT_L, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, SHIFT_R,
    CONTROL_L, META_L, ALT_L, SPACE, ALT_R, META_R, CONTROL_R, UP, DOWN, LEFT, RIGHT,
    ESCAPE, PRINTSCREEN, SCROLLLOCK, PAUSE, NUMLOCK,
    INSERT, HOME, PAGEUP, DELETE_, END, PAGEDOWN,
    NONE
};

std::string key2str(Key key);
Key fltk2key(int k);

#if defined _WIN32
WORD key2win(Key key);
#elif defined XLIB
int key2x11(Key key);
#endif

} // namespace midimap

#endif // MIDIMAP_KEY_HH
