set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/character.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.h
    ${CMAKE_CURRENT_SOURCE_DIR}/character.h
)

set(EXECUTABLE_NAME "ld32")
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

include_directories(${PROJECT_SOURCE_DIR}/3rdparty/dependencies/sfml-tmxloader/include)

find_library(SFMLTMXLOADER_LIBRARY tmx-loader PATHS ${PROJECT_SOURCE_DIR}/3rdparty/dependencies/sfml-tmxloader DOC "tmx-loader library")
if(NOT SFMLTMXLOADER_LIBRARY)
    message(FATAL_ERROR "Library tmx-loader required, but not found!")
endif(NOT SFMLTMXLOADER_LIBRARY)
target_link_libraries(${EXECUTABLE_NAME} ${SFMLTMXLOADER_LIBRARY})

find_library(PUGI_LIBRARY pugi PATHS ${PROJECT_SOURCE_DIR}/3rdparty/dependencies/sfml-tmxloader DOC "pugi library")
if(NOT PUGI_LIBRARY)
    message(FATAL_ERROR "Library pugi required, but not found!")
endif(NOT PUGI_LIBRARY)
target_link_libraries(${EXECUTABLE_NAME} ${PUGI_LIBRARY})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif(SFML_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
  target_link_libraries(${EXECUTABLE_NAME} m)
endif(OPENGL_FOUND)

# copy resources folder to output directory
# TODO: this should be a build step, executed after the build
file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${PROJECT_SOURCE_DIR}/build/src)