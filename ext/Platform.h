#ifndef MLD_PLATFORM_H_
#define MLD_PLATFORM_H_

#include <GL/glfw.h>
#include "Renderer.h"
#include "rice/Array.hpp"

using namespace Rice;

class Platform
{
   Renderer * renderer;

   public:
   Platform();
   ~Platform();
   void update();
   void addDrawCommand(Array a);
   void setViewMatrix(Array a);
};

#endif

