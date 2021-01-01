#ifndef MIDIMAP_NOTEKEYMAP_HH
#define MIDIMAP_NOTEKEYMAP_HH

#include "midimap/Key.hh"
#include <unordered_map>

namespace midimap {

using NoteKeyMap = std::unordered_map<unsigned char, Key>;

std::string noteKeyMap2str(NoteKeyMap const &map);

} // namespace midimap

#endif // MIDIMAP_NOTEKEYMAP_HH