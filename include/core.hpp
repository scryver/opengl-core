#ifndef __CORE_HPP__
#define __CORE_HPP__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "sdlwrapper.hpp"
#include "object.hpp"

class Core
{
public:
    Core();
    ~Core();

    void Init(const char *shaderPath, const char *imagePath);
    void Run();

private:
    SDLWrapper  *m_wrapper;
    Object      *m_object;
    glm::mat4   m_mvp;

};

int RunCore(const char *shaderPath, const char *imagePath);

#endif // __CORE_HPP__
