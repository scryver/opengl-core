#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <GL/glew.h>

class Object
{
public:
    Object(const char *shaderPath);
    ~Object();

    void Render();

private:
    static const GLfloat m_vertexBufferData[];

    GLuint m_vertexArrayID;
    GLuint m_programID;
    GLuint m_vertexBuffer;
};

#endif // __OBJECT_HPP__
