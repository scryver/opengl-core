#include "core.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <SDL.h>
// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "sdlwrapper.hpp"
#include "object.hpp"

int InitError(const char *name) {
    printf("Unable to initialize %s.", name);
    return -1;
}

int RunCore(const char *shaderPath) {
    SDLWrapper *wrapper = new SDLWrapper();
    if (wrapper->GetStatus() != SDLWrapper::INIT) {
        return InitError("SDL");
    }

    glewExperimental=GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        return InitError("GLEW");
    }
    printf("Supported OpenGL version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Object *object = new Object(shaderPath);

    while (!wrapper->MustQuit()) {
        glClear(GL_COLOR_BUFFER_BIT);
        object->Render();
        wrapper->Render();
    }

    delete object;
    delete wrapper;

    return 0;
}
