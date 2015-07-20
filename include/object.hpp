#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Object
{
public:
    Object(const char *shaderPath, const char *imagePath);
    ~Object();

    void Render(const GLfloat *value);

private:
    static const GLfloat m_vertexBufferData[];
    std::vector<GLfloat> m_uvBufferData;

    GLuint m_vertexArrayID;
    GLuint m_vertexBuffer;
    GLuint m_programID;
    GLuint m_textureID;
    GLuint m_texture;
    GLuint m_uvBuffer;
    GLuint m_matrixID;
};

#endif // __OBJECT_HPP__
