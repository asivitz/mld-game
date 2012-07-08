#include <GL/glfw.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "ShaderProgram.h"

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

GLuint    vertexBuffer;
GLuint    indexBuffer;
GLuint    texCoordBuffer;

void setupSquareDrawing()
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


   ShaderProgram * program = makeProgram("Shader.vsh", "SolidColor.fsh");
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

void draw()
{
}

int main(int argc, char **argv) 
{
   int running = GL_TRUE;
   // Initialize GLFW
   if( !glfwInit() )
   {
      exit( EXIT_FAILURE );
   }
   // Open an OpenGL window
   if( !glfwOpenWindow( 300,300, 0,0,0,0,0,0, GLFW_WINDOW ) )
   {
      glfwTerminate();
      exit( EXIT_FAILURE );
   }


   setupSquareDrawing();

   // Main loop
   while( running )
   {
      glClear( GL_COLOR_BUFFER_BIT );
      
      draw();

      // Swap front and back rendering buffers
      glfwSwapBuffers();
      // Check if ESC key was pressed or window was closed
      running = !glfwGetKey( GLFW_KEY_ESC ) &&
         glfwGetWindowParam( GLFW_OPENED );
   }
   // Close window and terminate GLFW
   glfwTerminate();
   // Exit program
   exit( EXIT_SUCCESS );
}
