#include <GL/glfw.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "ShaderProgram.h"
#include "Renderer.h"

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

   Renderer * renderer = new Renderer();

   // Main loop
   while( running )
   {
      glClear( GL_COLOR_BUFFER_BIT );
      
      renderer->executeCommands();

      // Swap front and back rendering buffers
      glfwSwapBuffers();
      // Check if ESC key was pressed or window was closed
      running = !glfwGetKey( GLFW_KEY_ESC ) &&
         glfwGetWindowParam( GLFW_OPENED );
   }
   // Close window and terminate GLFW
   glfwTerminate();
   // Exit program
   

   delete renderer;
   exit( EXIT_SUCCESS );
}
