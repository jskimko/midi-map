cmake_minimum_required(VERSION 3.0)

project(midimap
        VERSION 0.1
        LANGUAGES CXX
)

find_package(RtMidi REQUIRED)
# RtMidi exports its include directories as PRIVATE, so we need to get it ourselves.
get_target_property(RtMidi_INCLUDE_DIRECTORIES RtMidi::rtmidi LOCATION) # lib path
get_filename_component(RtMidi_INCLUDE_DIRECTORIES "${RtMidi_INCLUDE_DIRECTORIES}" DIRECTORY) # lib dir
get_filename_component(RtMidi_INCLUDE_DIRECTORIES "${RtMidi_INCLUDE_DIRECTORIES}" DIRECTORY) # root dir
set(RtMidi_INCLUDE_DIRECTORIES "${RtMidi_INCLUDE_DIRECTORIES}/include") # include dir
    
add_subdirectory(app)
add_subdirectory(src)
