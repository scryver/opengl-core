#include "core.hpp"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>

#include <SDL.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// using namespace glm;

#include "sdlwrapper.hpp"
#include "object.hpp"

int InitError(const char *name) {
    printf("Unable to initialize %s.", name);
    return -1;
}

Core::Core() {
    srand(time(NULL));

    m_wrapper = new SDLWrapper();
    if (m_wrapper->GetStatus() != SDLWrapper::INIT) {
        InitError("SDL");
    }

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        InitError("GLEW");
    }
    printf("Supported OpenGL version: %s\n", glGetString(GL_VERSION));

    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    glm::mat4 Model = glm::mat4(1.0f);
    m_mvp = Projection * View * Model;
}

Core::~Core() {
    if (m_object)
        delete m_object;
    delete m_wrapper;
}

void Core::Init(const char *shaderPath, const char *imagePath) {
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    m_object = new Object(shaderPath, imagePath);
}

void Core::Run() {
    while (!m_wrapper->MustQuit()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_object->Render(&m_mvp[0][0]);
        m_wrapper->Render();
    }
}
