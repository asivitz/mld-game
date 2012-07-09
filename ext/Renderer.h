#ifndef RENDERER_H_
#define RENDERER_H_

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "ShaderProgram.h"
#include <queue>

using namespace std;

struct DrawCommand
{
   float m[16];
   GLuint texId;
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
   void addCommand(DrawCommand * command);
   void executeCommands();
   void setupSquareDrawing();
   void commitViewMatrix();
   void draw();

   float viewMatrix[16];
};

#endif
