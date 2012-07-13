#ifndef MLD_PLATFORM_H_
#define MLD_PLATFORM_H_

#include "Renderer.h"
#include "Physics.h"
#include "rice/Array.hpp"
#include "rice/Director.hpp"
#include <SFML/Window.hpp>
//#include <SFML/RenderTexture.hpp>
#include <SFML/Graphics.hpp>


using namespace Rice;

class Platform : public Rice::Director
{
   Renderer * renderer;
   Physics * physics;

   sf::Window * window;
   sf::RenderTexture * lightMap;

   public:
   Platform(Object self);
   ~Platform();
   void update(double time);
   void draw();
   Object getPhysics();
   void addDrawCommand(int texid, Array a);
   void addLightCommand(int texid, Array a);
   void setViewMatrix(Array a);
   bool isWindowOpen();
   int loadImage(string fileName);
   void setPhysics(Physics * phys);
};

#endif

