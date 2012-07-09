//
//  ShaderProgram.m
//  ES2Framework
//
//  Adapted from ShaderProgram.m by Ryan Evans.
//  Copyright 2010 Muteki Corporation. All rights reserved.
//

#include "ShaderProgram.h"
#include <iostream>
#include <fstream>

using namespace std;

ShaderProgram::ShaderProgram(GLint vertShader, GLint fragShader)
{
   m_programID = glCreateProgram();
   m_vertShaderID = vertShader;
   m_fragShaderID = fragShader;
   linkProgram();
   loadAttributeMap();
}

int ShaderProgram::linkProgram()
{
   glAttachShader(m_programID, m_vertShaderID);
   glAttachShader(m_programID, m_fragShaderID);
   glLinkProgram(m_programID);

   GLint linked;
   glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);
   if(!linked) {
      GLint infoLen = 0;
      glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLen);
      if(infoLen > 1) {
         char* infoLog = (char *)malloc(infoLen * sizeof(char));
         glGetProgramInfoLog(m_programID, infoLen, NULL, infoLog);
         cout << "****ERROR LINKING SHADER PROGRAM:\n\t" << infoLog << endl;
         free(infoLog);
         return 1;
      }
   }

#ifdef SHADER_DEBUG
   cout << "Shader Program linked" << endl;
#endif
   return 0;
}

GLuint ShaderProgram::programId()
{
   return m_programID;
}

int ShaderProgram::loadAttributeMap()
{
   GLint numToRead = 0;
   glGetProgramiv(m_programID, GL_ACTIVE_ATTRIBUTES, &numToRead);
   char nameBuf[255];
   GLsizei len;
   GLint size;
   GLenum type;
   for(int i = 0; i < numToRead; i++) 
   {
      bzero(nameBuf, sizeof(char) * 255);
      glGetActiveAttrib(m_programID, i, 255, &len, &size, &type, nameBuf);
      GLint loc = glGetAttribLocation(m_programID, nameBuf);
      string attribName(nameBuf);
#ifdef SHADER_DEBUG
      cout << "Attribute \"" << attribName << "\" using index:" << loc << endl;
#endif
      m_attributeMap[attribName] = loc;
   }
   return 0;
}

GLint ShaderProgram::indexForAttribute(const char * a_attributeName)
{
   return m_attributeMap[string(a_attributeName)];
}

//TODO: cache uniform locations

GLint ShaderProgram::locationOfUniform(const char * inUniformName)
{
   GLint loc = glGetUniformLocation(m_programID, inUniformName);
   return loc;
   /*
   NSNumber * result = [m_uniformMap objectForKey:inUniformName];
   if (result)
   {
      return [result intValue];
   }
   else
   {
      GLint loc = glGetUniformLocation(m_programID, [inUniformName cStringUsingEncoding:NSASCIIStringEncoding]);
      [m_uniformMap setObject:[NSNumber numberWithInt:loc] forKey:inUniformName];
      return loc;
   }
   */
}

GLint ShaderProgram::locationOfTex()
{
   if (texUniformLocation == 0)
   {
      texUniformLocation = locationOfUniform("tex");
   }
   return texUniformLocation;
}

GLint ShaderProgram::locationOfModelMat()
{
    if (modelMatUniformLocation == 0)
    {
        modelMatUniformLocation = locationOfUniform("modelMat");
    }
    return modelMatUniformLocation;
}

ShaderProgram * makeProgram(const char * vertShader, const char * fragShader)
{
   GLint vert = compileShader(vertShader, GL_VERTEX_SHADER);
   GLint frag = compileShader(fragShader, GL_FRAGMENT_SHADER);

   if (vert > 0 && frag > 0)
   {
      ShaderProgram * shader = new ShaderProgram(vert, frag);
      return shader;
   }
   return NULL;
}

ShaderProgram::~ShaderProgram()
{
   glDeleteShader(m_vertShaderID);
   glDeleteShader(m_fragShaderID);
   //TODO: delete program?
}

void ShaderProgram::setAsActive()
{
    glUseProgram(m_programID);
}

char * getString(const char * fileName)
{
   std::ifstream t;
   int length;
   t.open(fileName);      // open input file

   if (t.fail())
   {
      cout << "Couldn't open file " << fileName << endl;
      return NULL;
   }

   t.seekg(0, std::ios::end);    // go to the end
   length = t.tellg();           // report location (this is the length)
   t.seekg(0, std::ios::beg);    // go back to the beginning
   char * buffer = new char[length + 1]();    // allocate memory for a buffer of appropriate dimension
   t.read(buffer, length);       // read the whole file into the buffer
   t.close();                    // close file handle
   return buffer;
}
   

GLint compileShader(const char * fileName, GLenum type)
{
   char * source = getString(fileName);

   if (source)
   {
      const GLchar * sourceData = source;

      GLint shaderID = glCreateShader(type);

      glShaderSource(shaderID, 1, &sourceData, NULL);
      glCompileShader(shaderID);

      free(source);

      GLint compiled;
      glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

      if(!compiled) 
      {
         GLint infoLen = 0;
         glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);
         if(infoLen > 1) 
         {
            char* infoLog = (char *)malloc(infoLen * sizeof(char));
            glGetShaderInfoLog(shaderID, infoLen, NULL, infoLog);
            cout << "****ERROR COMPILING SHADER(" << fileName << ")" << endl << infoLog << endl;
            free(infoLog);
         }
         glDeleteShader(shaderID);
         return -1;
      }
      return shaderID;
   }
   return -1;
}
