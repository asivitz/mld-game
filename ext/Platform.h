#ifndef MLD_PLATFORM_H_
#define MLD_PLATFORM_H_

#include <GL/glfw.h>
#include "Renderer.h"

class Platform
{
   Renderer * renderer;

   public:
   Platform();
   ~Platform();
   void update();
};

#endif

