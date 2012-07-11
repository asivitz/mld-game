//
//  Physics.m
//  Button
//
//  Created by Axis Sivitz on 12/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Physics.h"
#include "Body.h"

#import <Box2D/Box2D.h>
//#import "BContactListener.h"
//#import "RayCastCallbacks.h"
//#import "QueryCallbacks.h"
//#import "global.h"

vec2 centerPoint(vec2 inPoint)
{
    return vec2(floor(inPoint.x) + 0.5, floor(inPoint.y) + 0.5);
}

vec2 midpoint(vec2 one, vec2 two)
{
   return lerp(one, two, 0.5);
}

vec2 lerp(vec2 one, vec2 two, float interp)
{
    vec2 diff = two - one;
    diff *= interp;
    one += diff;
    return one;
}

bool isVecZero(vec2 inVec)
{
    return inVec.Length() < 0.001;
}

float dotProduct(vec2 vec1, vec2 vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

vec2 rotate(vec2 inVec, float angle)
{
   vec2 res;
   res.x = (inVec.x * cosf(angle)) - (inVec.y * sinf(angle));
   res.y =(inVec.y * cosf(angle)) + (inVec.x * sinf(angle));
   return res;
}

/*
template<>
Rice::Object to_ruby<b2Body>(b2Body const & param) 
{
   Body body;
   body.body = &param;
   return to_ruby<Body>(body);
}
*/

Rice::Object makeBody(b2Body * b2body)
{
   Body * body = new Body();
   body->body = b2body;
   Data_Object<Body> obj(body);
   return obj;
}

Physics::Physics()
{

   vec2 gravity = vec2(0.0f, -20.0f);
   boxworld = new b2World(gravity);
   //m_contactListener = new BContactListener();
   //boxworld->SetContactListener(m_contactListener);

   defaultFilter.categoryBits = 0x0001;
   defaultFilter.maskBits = 0xFFFF;
   defaultFilter.groupIndex = 0;

   initDebugDrawing();
}

void Physics::debugDraw()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    boxworld->DrawDebugData();
}

void Physics::initDebugDrawing()
{
    m_debugDraw = new GLESDebugDraw();
    uint32 flags = 0;
    flags += 1	* b2Draw::e_shapeBit;
    //flags += 1	* b2Draw::e_jointBit;
    //	flags += 1	* b2DebugDraw::e_controllerBit;
    //	flags += 1	* b2DebugDraw::e_coreShapeBit;
    //	flags += 1	* b2DebugDraw::e_aabbBit;
    //	flags += 1	* b2DebugDraw::e_obbBit;
    flags += 1	* b2Draw::e_pairBit;
    flags += 1	* b2Draw::e_centerOfMassBit;
    m_debugDraw->SetFlags(flags);
    m_debugDraw->wireframe = true;
    boxworld->SetDebugDraw(m_debugDraw);
}

Object Physics::addWall(vec2 pos, vec2 extens)
{
    b2BodyDef bodyDef;

    bodyDef.position.Set(pos.x, pos.y);

    b2Body* body = boxworld->CreateBody(&bodyDef);

    b2PolygonShape crateBox;

    crateBox.SetAsBox(extens.x, extens.y);

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &crateBox;
    fixtureDef.filter = defaultFilter;

    //fixtureDef.density = 1.0f;
    //fixtureDef.friction = 0.0f;
    //fixtureDef.restitution = 0.8;
    body->CreateFixture(&crateBox, 0.0);
    //body->CreateFixture(&fixtureDef);

    return makeBody(body);
}

b2Body * Physics::addSensor(vec2 pos, vec2 extens)
{
    b2BodyDef bd;
    bd.position.Set(pos.x,pos.y);
    b2Body * body = boxworld->CreateBody(&bd);

    b2PolygonShape shape;
    shape.SetAsBox(extens.x, extens.y);

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &shape;
    fixtureDef.isSensor = true;

    fixtureDef.filter = defaultFilter;
    body->CreateFixture(&fixtureDef);

    return body;
}

//useful for testing visibility of a drawn but non-interactive object
b2Body * Physics::addDummy(vec2 pos, vec2 extens)
{
    b2BodyDef bd;
    bd.position.Set(pos.x,pos.y);
    b2Body * body = boxworld->CreateBody(&bd);

    b2PolygonShape shape;
    shape.SetAsBox(extens.x, extens.y);

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &shape;
    fixtureDef.isSensor = true;

    b2Filter filter;
    filter.categoryBits = 0x0000;
    filter.maskBits = 0x0000;
    filter.groupIndex = 0;

    fixtureDef.filter = filter;
    body->CreateFixture(&fixtureDef);

    return body;
}

b2Body * Physics::addEmptyBody(vec2 pos)
{
    b2BodyDef bd;
    bd.position.Set(pos.x,pos.y);
    b2Body * body = boxworld->CreateBody(&bd);

    return body;
}

b2Body * Physics::addParticle(vec2 pos)
{
    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.fixedRotation = false;

    b2Body* body = boxworld->CreateBody(&bodyDef);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 0.05;

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &dynamicCircle;

    b2Filter filter;

    filter.categoryBits = 0x0004;
    filter.maskBits = 0x0001;
    filter.groupIndex = 0;


    fixtureDef.filter = filter;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.8;
    body->CreateFixture(&fixtureDef);

    return body;
}

Object Physics::addGrenade(vec2 pos, float size)
{
    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    //bodyDef.fixedRotation = true;
    //bodyDef.bullet = true;

    b2Body* body = boxworld->CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = size;

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &dynamicCircle;

    fixtureDef.filter = defaultFilter;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.3f;
    body->CreateFixture(&fixtureDef);

    return makeBody(body);
}

Object Physics::addPlayer(vec2 pos, float size)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.fixedRotation = true;

    b2Body* body = boxworld->CreateBody(&bodyDef);

    b2PolygonShape crateBox;

    crateBox.SetAsBox(0.5 * size, size);

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &crateBox;

    fixtureDef.filter = defaultFilter;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.3f;
    body->CreateFixture(&fixtureDef);

    return makeBody(body);
}

/*
b2Body * Physics::castRay(vec2 from, vec2 to)
{
    RayCastClosestCallback callback;
    //callback.ignore = ignore;
    boxworld->RayCast(&callback, from, to);
    if (callback.m_hit)
    {
        //printf("Hit point: %f %f", callback.m_point.x, callback.m_point.y);
        return callback.m_fixture->GetBody();
    }
    return NULL;
}
*/

vec2 Physics::worldBottomRight()
{
    vec2 bottomRight = VECZERO;

    b2Body * body = boxworld->GetBodyList();
    while (body != NULL)
    {
        b2Transform xf = body->GetTransform();

        b2Fixture * fixture = body->GetFixtureList();
        while (fixture != NULL)
        {

            b2Shape * shape = fixture->GetShape();

            if (shape->GetType() == b2Shape::e_polygon)
            {
                b2PolygonShape * polyShape = (b2PolygonShape *)shape;
                for (int i = 0; i < polyShape->GetVertexCount(); i++)
                {
                    vec2 point = b2Mul(xf, polyShape->m_vertices[i]);
                    if (point.x > bottomRight.x)
                        bottomRight.x = point.x;
                    if (point.y > bottomRight.y)
                        bottomRight.y = point.y;
                }
            }

            fixture = fixture->GetNext();
        }

        body = body->GetNext();
    }

    return bottomRight;
}

void Physics::remove(b2Body * obj)
{
    if (obj == NULL)
        return;

    boxworld->DestroyBody(obj);
}

void Physics::tick(double time)
{
    boxworld->Step(time, 10, 10);
    boxworld->ClearForces();
}

Physics::~Physics()
{
    //delete m_contactListener;
    delete boxworld;
    delete m_debugDraw;
}
