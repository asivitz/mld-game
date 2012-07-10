#ifndef MLD_BODY_H_
#define MLD_BODY_H_

#include "Renderer.h"
#include "Physics.h"
#include "rice/Array.hpp"
#include "rice/Director.hpp"
#include <SFML/Window.hpp>

using namespace Rice;

class Body // : public Rice::Director
{

   public:
   b2Body * body;
   //Platform(Object self);
   //~Body(Object self);
   Object pos();
};

#endif

