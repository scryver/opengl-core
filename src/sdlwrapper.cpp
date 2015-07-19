#include "sdlwrapper.hpp"

#include <SDL.h>

#include "definitions.h"

static void SDLDie(const char *msg) {
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
}

static void CheckSDLError(int line = -1) {
#ifndef NDEBUG
    const char *error = SDL_GetError();
    if (*error != '\0') {
        printf("SDL Error: %s\n", error);
        if (line != -1)
            printf(" + line: %i\n", line);
        SDL_ClearError();
    }
#endif
}

SDLWrapper::SDLWrapper() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDLDie("Unable to initialize SDL");
        m_status = NO_INIT;
    }
    else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        m_window = SDL_CreateWindow(PROGRAM_NAME,SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!m_window) {
            SDLDie("Unable to create window");
            m_status = NO_WINDOW;
        }
        else {
            CheckSDLError(__LINE__);
            m_context = SDL_GL_CreateContext(m_window);
            CheckSDLError(__LINE__);

            SDL_GL_SetSwapInterval(1);
            m_status = INIT;
        }
    }
}

SDLWrapper::~SDLWrapper() {
    if (m_status == INIT) {
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
    }
    SDL_Quit();
}

void SDLWrapper::Render() {
    if (m_status == INIT) {
        SDL_GL_SwapWindow(m_window);
        SDL_Delay(20);
    }
}

int SDLWrapper::MustQuit() {
    int quit = 0;

    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
                break;
            default:
                break;
        }
    }

    return quit;
}
