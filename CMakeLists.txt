cmake_minimum_required(VERSION 3.0)

project(midimap
        VERSION 0.1
        LANGUAGES CXX
)

find_package(RtMidi REQUIRED)

add_subdirectory(app)
add_subdirectory(src)
