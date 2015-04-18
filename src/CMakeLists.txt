set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set(HEADERS
)

set(EXECUTABLE_NAME "ld32")
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

#find_library(BOX2D_LIBRARY Box2D PATHS ${PROJECT_SOURCE_DIR}/3rdparty/dependencies/Box2D/Box2D DOC "Box2D library")
#if(NOT BOX2D_LIBRARY)
    #message(FATAL_ERROR "Library Box2D required, but not found!")
#endif(NOT BOX2D_LIBRARY)
#include_directories(${PROJECT_SOURCE_DIR}/3rdparty/dependencies/Box2D/)
#target_link_libraries(${EXECUTABLE_NAME} ${BOX2D_LIBRARY})

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
