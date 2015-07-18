// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>

#include <SDL.h>
#define PROGRAM_NAME "Run rabbit, run"

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

void SDLDie(const char *msg) {
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}

void CheckSDLError(int line = -1) {
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

int main (int argc, char *argv[]) {
    SDL_Window *mainWindow;
    SDL_GLContext mainContext;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        SDLDie("Unable to initialize SDL");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    mainWindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainWindow)
        SDLDie("Unable to create window");

    CheckSDLError(__LINE__);
    mainContext = SDL_GL_CreateContext(mainWindow);
    CheckSDLError(__LINE__);

    SDL_GL_SetSwapInterval(1);

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mainWindow);
    SDL_Delay(5000);

    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}
