/*
 *  BContactListener.cpp
 *  Button
 *
 *  Created by Axis Sivitz on 12/22/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BContactListener.h"
#include <inttypes.h>
#include "Physics.h"

void BContactListener::BeginContact(b2Contact* contact)
{
   //[contactHandler handleBeginContact:contact];


   /*
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

    PhysicsObject * objA = physObjForBody(bodyA);
    PhysicsObject * objB = physObjForBody(bodyB);

    if ([objA respondsToSelector:@selector(enter:)])
    {
        [(id)objA enter:bodyB];
    }
    else if ([objB respondsToSelector:@selector(enter:)])
    {
        [(id)objB enter:bodyA];
    }*/
}

void BContactListener::EndContact(b2Contact* contact)
{
   //[contactHandler handleEndContact:contact];

   /*
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

    PhysicsObject * objA = physObjForBody(bodyA);
    PhysicsObject * objB = physObjForBody(bodyB);

    if ([objA respondsToSelector:@selector(exit:)])
    {
        [(id)objA exit:bodyB];
    }
    else if ([objB respondsToSelector:@selector(exit:)])
    {
        [(id)objB exit:bodyA];
    }*/
}

void BContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
   //[contactHandler handlePreSolve:contact];

   /*
   b2Body * bodyA = contact->GetFixtureA()->GetBody();
   b2Body * bodyB = contact->GetFixtureB()->GetBody();

   int enta = (int)bodyA->GetUserData();
   int entb = (int)bodyB->GetUserData();

   if (enta == entb)
   {
      contact->SetEnabled(false);
   }
   */

   /*
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    vec2 contactPoint = VECZERO;
    for (int i = 0; i < contact->GetManifold()->pointCount; i++)
    {
        contactPoint += worldManifold.points[i];
    }
    contactPoint *= (1.0/contact->GetManifold()->pointCount);


    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

    PhysicsObject * objA = physObjForBody(bodyA);
    PhysicsObject * objB = physObjForBody(bodyB);

    if ([objA handlePreCollision:objB ContactPoint:contactPoint MyFixture:contact->GetFixtureA()])
        contact->SetEnabled(false);

    if ([objB handlePreCollision:objA ContactPoint:contactPoint MyFixture:contact->GetFixtureB()])
        contact->SetEnabled(false);*/
}

void BContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
   b2Body * bodyA = contact->GetFixtureA()->GetBody();
   b2Body * bodyB = contact->GetFixtureB()->GetBody();

   int enta = (intptr_t)bodyA->GetUserData();
   int entb = (intptr_t)bodyB->GetUserData();

   b2WorldManifold worldManifold;
   contact->GetWorldManifold(&worldManifold);

   vec2 contactPoint = VECZERO;
   for (int i = 0; i < contact->GetManifold()->pointCount; i++)
   {
      contactPoint += worldManifold.points[i];
   }
   contactPoint *= (1.0/contact->GetManifold()->pointCount);

   float imp = 0;
   for (int i = 0; i < contact->GetManifold()->pointCount; i++)
   {
      imp += fabs(impulse->normalImpulses[i]);
      //	NSLog(@"Normal impulse:%f Tangent Impulse:%f", impulse->normalImpulses[i], impulse->tangentImpulses[i]);
   }

   //[contactHandler addCollisionBetweenEntA:enta entB:entb contactPoint:contactPoint impulse:imp];
}
