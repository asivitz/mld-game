#include <stdlib.h>
#include <iostream>

using namespace std;

#include "Platform.h"

void draw()
{
}

int main(int argc, char **argv) 
{

   int running = GL_TRUE;

   Platform * platform = new Platform();

   // Main loop
   while( running )
   {
      platform->update();
      
      // Check if ESC key was pressed or window was closed
      running = !glfwGetKey( GLFW_KEY_ESC ) &&
         glfwGetWindowParam( GLFW_OPENED );
   }

   delete platform;
   exit( EXIT_SUCCESS );
}
