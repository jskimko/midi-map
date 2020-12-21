add_library(midimap-lib
    midimap.cc
    Controller.cc
)

target_include_directories(midimap-lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(midimap-lib
    PUBLIC
        RtMidi::rtmidi
)
