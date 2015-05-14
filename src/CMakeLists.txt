set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/animation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/animatedsprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/character.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stuffmath.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/reactor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bullet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/eyes.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.h
    ${CMAKE_CURRENT_SOURCE_DIR}/animation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/animatedsprite.h
    ${CMAKE_CURRENT_SOURCE_DIR}/character.h
    ${CMAKE_CURRENT_SOURCE_DIR}/stuffmath.h
    ${CMAKE_CURRENT_SOURCE_DIR}/reactor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bullet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/eyes.h
)

set(EXECUTABLE_NAME "ld32")
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

include_directories(${PROJECT_SOURCE_DIR}/3rdparty/dependencies/sfml-tmxloader/include)
#windows
#include_directories(${PROJECT_SOURCE_DIR}/DEPS/sfml-tmxloader-master/include)


find_library(SFMLTMXLOADER_LIBRARY tmx-loader PATHS ${PROJECT_SOURCE_DIR}/3rdparty/dependencies/sfml-tmxloader DOC "tmx-loader library")
#windows
#find_library(SFMLTMXLOADER_LIBRARY tmx-loader PATHS ${PROJECT_SOURCE_DIR}/DEPS/sfml-tmxloader-master/ DOC "tmx-loader library")
if(NOT SFMLTMXLOADER_LIBRARY)
    message(FATAL_ERROR "Library tmx-loader required, but not found!")
endif(NOT SFMLTMXLOADER_LIBRARY)
target_link_libraries(${EXECUTABLE_NAME} ${SFMLTMXLOADER_LIBRARY})


# windows
#find_package(ZLIB REQUIRED)
#if(ZLIB_FOUND)
    #include_directories(${ZLIB_INCLUDE_DIRS})
#elseif(NOT ZLIB_FOUND)
    #set(ZLIB_ROOT "" CACHE PATH "zlib top-level directory")
    #message("\n-> zlib directory not found. Set ZLIB_ROOT to zlib's top-level path (containing \"include\" and \"lib\" directories).")
    #message("-> Make sure the zlib libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
#endif()
#target_link_libraries(${EXECUTABLE_NAME} ${ZLIB_LIBRARIES})
#find_library(PUGI_LIBRARY pugi PATHS ${PROJECT_SOURCE_DIR}/DEPS/sfml-tmxloader-master/ DOC "pugi library")

find_library(PUGI_LIBRARY pugi PATHS ${PROJECT_SOURCE_DIR}/3rdparty/dependencies/sfml-tmxloader DOC "pugi library")


find_library(PUGI_LIBRARY pugi PATHS ${PROJECT_SOURCE_DIR}/DEPS/sfml-tmxloader-master/ DOC "pugi library")
if(NOT PUGI_LIBRARY)
    message(FATAL_ERROR "Library pugi required, but not found!")
endif(NOT PUGI_LIBRARY)
target_link_libraries(${EXECUTABLE_NAME} ${PUGI_LIBRARY})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules" ${CMAKE_MODULE_PATH})


# windows (also static)
#if(CMAKE_COMPILER_IS_GNUCXX)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#endif()

# static
#add_definitions(-DSFML_STATIC)
#set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2 REQUIRED graphics window system)
#find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
  # static?
  #target_link_libraries(${EXECUTABLE_NAME} ${SFML_DEPENDENCIES})
endif(SFML_FOUND)


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
  target_link_libraries(${EXECUTABLE_NAME} m)
endif(OPENGL_FOUND)


find_package(Thor REQUIRED)
include_directories(${THOR_INCLUDE_DIR})
if (THOR_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} ${THOR_LIBRARY})
endif(THOR_FOUND)


# copy resources folder to output directory
# TODO: this should be a build step, executed after the build
file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${PROJECT_SOURCE_DIR}/build/src)

# installation (check it)
install(TARGETS ${EXECUTABLE_NAME} DESTINATION .)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources DESTINATION .)
install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION .)
