#include "Platform.h"

#include "rice/Class.hpp"
#include "rice/String.hpp"

using namespace Rice;

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

   extern "C"
void Init_Platform()
{
   Data_Type<Platform> rb_cPlatform =
      define_class<Platform>("Platform")
      .define_constructor(Constructor<Platform>())
      .define_method("update", &Platform::update);
}
