/*
 *  BContactListener.h
 *  Button
 *
 *  Created by Axis Sivitz on 12/22/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __B_CONTACT_LISTENER_H_
#define __B_CONTACT_LISTENER_H_

#include <Box2D/Box2D.h>

class BContactListener : public b2ContactListener
{

    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif
