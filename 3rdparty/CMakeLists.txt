cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

set(3RDPARTY_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/../dependencies)

ExternalProject_Add(sfml-tmxloader
    GIT_REPOSITORY https://github.com/fallahn/sfml-tmxloader.git
    SOURCE_DIR ${3RDPARTY_PREFIX}/sfml-tmxloader
    # pretty ugly way. but it works.
    CONFIGURE_COMMAND cmake .
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)
