#include "midimap/NoteKeyMap.hh"
#include "midimap/Converter.hh"

#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>

namespace midimap {

std::string noteKeyMap2str(NoteKeyMap const &map)
{
    if (map.size() == 0) { return {}; }

    auto minOctave = Converter::octave(map.begin()->first);
    auto maxOctave = minOctave;

    for (auto it=map.begin(); it != map.end(); it++) {
        auto octave = Converter::octave(it->first);
        if      (octave < minOctave) { minOctave = octave; }
        else if (octave > maxOctave) { maxOctave = octave; }
    }

    std::vector<std::vector<std::pair<unsigned char, Key>>> octaves(maxOctave - minOctave + 1);
    for (auto it=map.begin(); it != map.end(); it++) {
        auto o = Converter::octave(it->first) - minOctave;
        octaves[o].push_back(*it);
    }

    std::vector<std::string::size_type> maxSymLens(octaves.size());
    std::vector<std::string::size_type> maxKeyLens(octaves.size());
    for (decltype(octaves.size()) i=0; i<octaves.size(); i++) {
        std::sort(octaves[i].begin(), octaves[i].end(), std::greater<>()); 

        for (auto const &p : octaves[i]) {
            auto len = Converter::symbol(p.first).size();
            if (len > maxSymLens[i]) { maxSymLens[i] = len; }
            len = key2str(p.second).size();
            if (len > maxKeyLens[i]) { maxKeyLens[i] = len; }
        }
    }

    auto format_entry = [&maxSymLens, &maxKeyLens](std::stringstream &ss, 
                                                   std::pair<unsigned char, Key> const &p,
                                                   int col) {
        ss << std::left << std::setfill(' ') << std::setw(maxSymLens[col])
           << Converter::symbol(p.first) << " -> " 
           << std::setw(maxKeyLens[col]) << key2str(p.second);
    };

    auto format_row = [](std::stringstream &ss, 
                         std::string const &s, 
                         std::string::size_type w, 
                         bool last) {
        ss << std::setw(w) << s;
        if (!last) { ss << " | "; }
    };

    std::stringstream ss;
    decltype(octaves[0].size()) r=0;
    std::vector<std::string::size_type> maxEntryLens(octaves.size());
    while (1) {
        bool any = false;
        for (decltype(octaves.size()) c=0; c<octaves.size(); c++) {
            if (r < octaves[c].size()) {
                any = true;
                break;
            }
        }
        if (!any) { break; }

        for (decltype(octaves.size()) c=0; c<octaves.size(); c++) {
            std::stringstream entry;
            if (r < octaves[c].size()) {
                format_entry(entry, octaves[c][r], c);
            }
            if (entry.str().size() > maxEntryLens[c]) { 
                maxEntryLens[c] = entry.str().size(); 
            }
            format_row(ss, entry.str(), maxEntryLens[c], c == octaves.size() - 1);
        }
        ss << "\n";

        r++;
    }

    return ss.str();
}

} // namespace midimap
