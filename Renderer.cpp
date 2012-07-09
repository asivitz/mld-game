#include "Renderer.h"

#include <iostream>

using namespace std;

Renderer::Renderer()
{
   setupSquareDrawing();
}

Renderer::~Renderer()
{
   if (program)
      delete program;
}

const GLfloat boxVertices[] = {
    -0.5, 0.5,
    -0.5, -0.5,
    0.5, -0.5,
    0.5, 0.5
};

const GLushort boxIndices[] = {
    0,1,2,3
};

const GLshort boxTextureCoords[] = {
    0, 0,
    0, 1,
    1, 1,
    1, 0,
};


void Renderer::setupSquareDrawing()
{
   glGenBuffers(1, &vertexBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);

   glGenBuffers(1, &texCoordBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(boxTextureCoords), boxTextureCoords, GL_STATIC_DRAW);

   glGenBuffers(1, &indexBuffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);


   program = makeProgram("shaders/Shader.vsh", "shaders/SolidColor.fsh");
   if (!program)
   {
      cout << "Couldn't create shader" << endl;
      return;
   }
   program->setAsActive();

   // Update attribute values.
   glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
   glVertexAttribPointer(program->indexForAttribute("position"), 2, GL_FLOAT, 0, 0, 0);
   glEnableVertexAttribArray(program->indexForAttribute("position"));

   // Update attribute values.
   glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
   glVertexAttribPointer(program->indexForAttribute("texCoords"), 2, GL_SHORT, 0, 0, 0);
   glEnableVertexAttribArray(program->indexForAttribute("texCoords"));
}

void Renderer::addCommand(float m[16])
{
   DrawCommand * command = new DrawCommand();
   //command->m = m;
   memcpy(command->m, m, sizeof(float) * 16);
   commands.push(command);
}

void Renderer::executeCommands()
{
   while (!commands.empty())
   {
      DrawCommand * command = commands.front();
      glUniformMatrix4fv(program->locationOfModelMat(), 1, GL_FALSE, command->m);
      glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, 0);
      delete command;
      commands.pop();
   }
}
