cmake_minimum_required(VERSION 2.6)
project(run_rabbit_run)

find_package(OpenGL REQUIRED)

# find_program(SDL_CONFIG sdl2-config)
# execute_process(COMMAND SDL_CONFIG --cflags
#     OUTPUT_VARIABLE SDL_CFLAGS)
# execute_process(COMMAND SDL_CONFIG --libs
#     OUTPUT_VARIABLE SDL_LIBS)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS})

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}
    ${ALL_LIBS}
)
