cmake_minimum_required(VERSION 2.6)
project(run_rabbit)
set(LIB_NAME run_rabbit_run)

include(FindPkgConfig)

find_package(OpenGL REQUIRED)

add_library(${LIB_NAME} SHARED
    src/core.cpp
)

pkg_search_module(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS} include)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARIES}
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
