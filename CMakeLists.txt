cmake_minimum_required(VERSION 2.6)
project(run_rabbit)
set(LIB_NAME run_rabbit_run)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)

find_package(OpenGL REQUIRED)

add_library(${LIB_NAME} SHARED
    src/cwrapper.cpp
    src/core.cpp
    src/shader.cpp
    src/texture.cpp
    src/sdlwrapper.cpp
    src/object.cpp
)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(GLEW REQUIRED glew)

include_directories(
    include
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
)

target_link_libraries(${LIB_NAME}
    ${ALL_LIBS}
)

# add_executable(${PROJECT_NAME}
#     src/main.cpp
# )

# target_link_libraries(${PROJECT_NAME}
#     ${LIB_NAME}
# )
