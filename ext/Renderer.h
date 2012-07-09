#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glfw.h>
#include "ShaderProgram.h"
#include <queue>

using namespace std;

struct DrawCommand
{
   float m[16];
};

class Renderer
{
   queue<DrawCommand *> commands;
   ShaderProgram * program;

   GLuint    vertexBuffer;
   GLuint    indexBuffer;
   GLuint    texCoordBuffer;

   public:
   Renderer();
   ~Renderer();
   void addCommand(float m[16]);
   void executeCommands();
   void setupSquareDrawing();
   void commitViewMatrix();
   void draw();

   float viewMatrix[16];
};

#endif
