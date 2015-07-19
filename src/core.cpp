#include "core.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
// #include <GL/gl.h>

#include <SDL.h>
#define PROGRAM_NAME "Run rabbit, run"

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "shader.hpp"

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

int RunCore(void) {
    SDL_Window *mainWindow;
    SDL_GLContext mainContext;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDLDie("Unable to initialize SDL");
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    mainWindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainWindow) {
        SDLDie("Unable to create window");
        return -1;
    }

    CheckSDLError(__LINE__);
    mainContext = SDL_GL_CreateContext(mainWindow);
    CheckSDLError(__LINE__);

    SDL_GL_SetSwapInterval(1);

    glewExperimental=GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        printf("Unable to initialize GLEW");
        return -1;
    }
    printf("Supported OpenGL version: %s\n", glGetString(GL_VERSION));

    SDL_Event event;
    int quit = 0;

    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders("../core/shaders/simple");

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    GLuint VertexBuffer;
    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    while (!quit) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        SDL_GL_SwapWindow(mainWindow);
        SDL_Delay(20);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
                    break;
                default:
                    break;
            }
        }
    }

    glDeleteBuffers(1, &VertexBuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}
