add_library(midimap-lib
    midimap.cc
    Controller.cc
    Converter.cc
    Key.cc
)

target_include_directories(midimap-lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${RtMidi_INCLUDE_DIRECTORIES}"
)

target_link_libraries(midimap-lib
    PUBLIC
        RtMidi::rtmidi
)
