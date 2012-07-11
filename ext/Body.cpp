#include "Body.h"
#include <inttypes.h>
#include <iostream>

#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"
#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"

#include <SFML/Graphics.hpp>
//#include <SFML/Image.hpp>

using namespace Rice;
using namespace std;

/*
Body::Body(Object self) : Rice::Director(self)
{
}
*/

/*
Body::~Body()
{
}
*/

template<>
Rice::Object to_ruby<vec2>(vec2 const & param) 
{
   Array arr;
   arr.push(param.x);
   arr.push(param.y);
   return arr;
}

template<>
vec2 from_ruby<vec2>(Rice::Object x) 
{
   Array arr(x);
   if (arr.size() == 2)
   {
      vec2 v;
      VALUE * carr = arr.to_c_array();
      v.x = NUM2DBL(carr[0]);
      v.y = NUM2DBL(carr[1]);
      return v;
   }
   return VECNULL;
}


/*
template<>
vec2 from_ruby<vec2>(Rice::Object x) 
{
   Array arr(x);
   if (arr.size() == 2)
   {
      vec2 v;
      VALUE * carr = arr.to_c_array();
      v.x = NUM2DBL(carr[0]);
      v.y = NUM2DBL(carr[1]);
      return v;
   }
   return VECNULL;
}
*/

Object Body::pos()
{
   vec2 pos = body->GetPosition();
   return to_ruby<vec2>(pos);
   //Array arr;
   //arr.push(pos.x);
   //arr.push(pos.y);
   //return arr;
}

void Body::push(vec2 vel)
{
   body->ApplyLinearImpulse(vel, VECZERO);
}

Object Body::getVel()
{
   vec2 vel = body->GetLinearVelocity();
   return to_ruby<vec2>(vel);
}

void Body::setVel(vec2 vel)
{
   body->SetLinearVelocity(vel);
}

int Body::getId()
{
   return (intptr_t)body->GetUserData();
}
