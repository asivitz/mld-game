#include "Platform.h"
#include <iostream>

#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"
#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"

using namespace Rice;
using namespace std;

Platform::Platform()
{
   window = new sf::Window(sf::VideoMode(800, 600), "OpenGL");
   window->setVerticalSyncEnabled(true);

   renderer = new Renderer();
}

Platform::~Platform()
{
   delete renderer;
   delete window;
}

void Platform::update()
{
   renderer->draw();
   window->display();
}

void Platform::addDrawCommand(Array a)
{
   if (a.size() == 16)
   {
      VALUE * carr = a.to_c_array();
      float m[16];
      for (int i = 0; i < 16; i++)
      {
         m[i] = (float)NUM2DBL(carr[i]);
      }
      renderer->addCommand(m);
   }
}

void Platform::setViewMatrix(Array a)
{
   if (a.size() == 16)
   {
      VALUE * carr = a.to_c_array();
      for (int i = 0; i < 16; i++)
      {
         renderer->viewMatrix[i] = (float)NUM2DBL(carr[i]);
      }
   }
}

   extern "C"
void Init_engine()
{
   Data_Type<Platform> rb_cPlatform =
      define_class<Platform>("Platform")
      .define_constructor(Constructor<Platform>())
      .define_method("addDrawCommand", &Platform::addDrawCommand)
      .define_method("setViewMatrix", &Platform::setViewMatrix)
      .define_method("update", &Platform::update);

   /*
   Data_Type<Renderer> rb_cRenderer =
      define_class<Renderer>("Renderer")
      .define_constructor(Constructor<Renderer>())
      .define_method("update", &Platform::update);
      */
}
