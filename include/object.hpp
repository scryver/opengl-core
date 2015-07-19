#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <GL/glew.h>
#include <glm/glm.hpp>

class Object
{
public:
    Object(const char *shaderPath);
    ~Object();

    void Render(const GLfloat *value);
    void ChangeColor();

private:
    static const GLfloat m_vertexBufferData[];
    GLfloat m_colorBufferData[12 * 3 * 3];

    GLuint m_vertexArrayID;
    GLuint m_programID;
    GLuint m_vertexBuffer;
    GLuint m_colorBuffer;
    GLuint m_matrixID;
};

#endif // __OBJECT_HPP__
