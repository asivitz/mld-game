//
//  ShaderProgram.h
//  Copyright 2012 Axis Sivitz
//
#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_

#include <GL/glfw.h>
#include <map>

using namespace std;

#define SHADER_DEBUG 1

class ShaderProgram
{
   GLuint m_programID;
   GLuint m_vertShaderID;
   GLuint m_fragShaderID;

   map<string, int> m_attributeMap;
   map<string, int> m_uniformMap;

   GLint texUniformLocation;
   GLint modelMatUniformLocation;

   int linkProgram();
   int loadAttributeMap();

   public:
    ShaderProgram(GLint vertShader, GLint fragShader);
    ~ShaderProgram();
    GLuint programId();
    void setAsActive();
    GLint indexForAttribute(const char * a_attributeName);
    GLint locationOfUniform(const char * inUniformName);
    GLint locationOfTex();
    GLint locationOfModelMat();
};

GLint compileShader(const char * fileName, GLenum type);
ShaderProgram * makeProgram(const char * vertShader, const char * fragShader);

#endif
