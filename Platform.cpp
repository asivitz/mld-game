#include "Platform.h"

Platform::Platform()
{
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

   renderer = new Renderer();
}

Platform::~Platform()
{
   delete renderer;
   glfwTerminate();
}

void Platform::update()
{
   renderer->draw();
}
