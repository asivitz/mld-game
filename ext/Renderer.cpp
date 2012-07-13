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


   program = makeProgram("shaders/Shader.vsh", "shaders/Shader.fsh");
   if (!program)
   {
      cout << "Couldn't create shader" << endl;
      return;
   }
   program->setAsActive();
   glActiveTexture(GL_TEXTURE0);
   glUniform1i(program->locationOfTex(), 0);

   // Update attribute values.
   glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
   glVertexAttribPointer(program->indexForAttribute("position"), 2, GL_FLOAT, 0, 0, 0);
   glEnableVertexAttribArray(program->indexForAttribute("position"));

   // Update attribute values.
   glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
   glVertexAttribPointer(program->indexForAttribute("texCoords"), 2, GL_SHORT, 0, 0, 0);
   glEnableVertexAttribArray(program->indexForAttribute("texCoords"));
}

void Renderer::addCommand(DrawCommand * command)
{
   drawCommands.push(command);
}

void Renderer::addLightCommand(DrawCommand * command)
{
   lightCommands.push(command);
   //cout << "Adding light command. size: " << lightCommands.size() << endl;
}

void Renderer::commitViewMatrix()
{
   glUniformMatrix4fv(program->locationOfUniform("viewMat"), 1, GL_FALSE, viewMatrix);
}

void Renderer::executeCommands(queue<DrawCommand *> * commands)
{
   while (!commands->empty())
   {
      DrawCommand * command = commands->front();

      glUniformMatrix4fv(program->locationOfModelMat(), 1, GL_FALSE, command->m);
      glBindTexture(GL_TEXTURE_2D, command->texId);
      glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, 0);
      delete command;
      commands->pop();
   }
}

void Renderer::draw()
{
   glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

   glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

   program->setAsActive();
   glUniformMatrix4fv(program->locationOfUniform("viewMat"), 1, GL_FALSE, viewMatrix);
   glUniform4f(program->locationOfUniform("color"), 1.0, 1.0, 1.0, 1.0);

   glVertexAttribPointer(program->indexForAttribute("position"), 2, GL_FLOAT, 0, 0, 0);
   glEnableVertexAttribArray(program->indexForAttribute("position"));
   

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);
   executeCommands(&drawCommands);
   glDisable(GL_BLEND);
}

void Renderer::drawLights()
{
   glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
   glClear( GL_COLOR_BUFFER_BIT );

   glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

   program->setAsActive();
   glUniformMatrix4fv(program->locationOfUniform("viewMat"), 1, GL_FALSE, viewMatrix);
   glUniform4f(program->locationOfUniform("color"), 1.0, 1.0, 1.0, 1.0);

   glVertexAttribPointer(program->indexForAttribute("position"), 2, GL_FLOAT, 0, 0, 0);
   glEnableVertexAttribArray(program->indexForAttribute("position"));
   

   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glBlendFunc(GL_ONE, GL_ONE);
   glEnable(GL_BLEND);
   executeCommands(&lightCommands);
   glDisable(GL_BLEND);
}
