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
   queue<DrawCommand *> drawCommands;
   queue<DrawCommand *> lightCommands;

   GLuint    vertexBuffer;
   GLuint    indexBuffer;
   GLuint    texCoordBuffer;

   public:
   ShaderProgram * program;
   Renderer();
   ~Renderer();
   void addCommand(DrawCommand * command);
   void addLightCommand(DrawCommand * command);
   void executeCommands(queue<DrawCommand *> * commands);
   void setupSquareDrawing();
   void commitViewMatrix();
   void draw();
   void drawLights();

   float viewMatrix[16];
};

#endif
