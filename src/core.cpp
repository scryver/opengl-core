#include "core.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>

#include <SDL.h>
// Include GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// using namespace glm;

#include "sdlwrapper.hpp"
#include "object.hpp"

int InitError(const char *name) {
    printf("Unable to initialize %s.", name);
    return -1;
}

int RunCore(const char *shaderPath) {
    srand(time(NULL));

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

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Object *object = new Object(shaderPath);

    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );

    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 MVP = Projection * View * Model;

    int counter = 0;

    while (!wrapper->MustQuit()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        object->Render(&MVP[0][0]);
        wrapper->Render();

        counter++;
        if (counter >= 60) {
            counter = 0;
            object->ChangeColor();
        }
    }

    delete object;
    delete wrapper;

    return 0;
}
