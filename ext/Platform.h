#ifndef MLD_PLATFORM_H_
#define MLD_PLATFORM_H_

#include "Renderer.h"
#include "rice/Array.hpp"
#include <SFML/Window.hpp>

using namespace Rice;

class Platform
{
   Renderer * renderer;
   sf::Window * window;

   public:
   Platform();
   ~Platform();
   void update();
   void addDrawCommand(Array a);
   void setViewMatrix(Array a);
};

#endif

