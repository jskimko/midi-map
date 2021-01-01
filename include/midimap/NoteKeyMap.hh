#ifndef MIDIMAP_NOTEKEYMAP_HH
#define MIDIMAP_NOTEKEYMAP_HH

#include <unordered_map>

namespace midimap {

using NoteKeyMap = std::unordered_map<unsigned char, Key>;

} // namespace midimap

#endif // MIDIMAP_NOTEKEYMAP_HH