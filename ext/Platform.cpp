#include "Platform.h"
#include <iostream>

#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"
#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"

#include <SFML/Graphics.hpp>
//#include <SFML/Image.hpp>

#include "Body.h"

using namespace Rice;
using namespace std;

Platform::Platform(Object self) : Rice::Director(self)
{
   window = new sf::Window(sf::VideoMode(600, 600), "OpenGL");
   window->setVerticalSyncEnabled(true);
   window->setKeyRepeatEnabled(false);

   renderer = new Renderer();

   lightMap = new sf::RenderTexture();
   if (!lightMap->create(600, 600))
      cout << "ERROR: Couldn't create lightMap" << endl;
}

Platform::~Platform()
{
   delete renderer;
   delete window;
}

void Platform::setPhysics(Physics * phys)
{
   physics = phys;

   ShaderProgram * program = makeProgram("shaders/Shader.vsh", "shaders/SolidColor.fsh");
   if (program)
   {
      physics->m_debugDraw->shaderProgram = program;
   }
   else
      cout << "Couldn't create shader" << endl;
}

void Platform::draw()
{
   sf::Event event;
   while (window->pollEvent(event))
   {
      // Close window : exit
      if (event.type == sf::Event::Closed)
         window->close();
      else if (event.type == sf::Event::KeyPressed)
      {
         getSelf().call("key_pressed", (int)event.key.code);
      }
      else if (event.type == sf::Event::KeyReleased)
      {
         getSelf().call("key_released", (int)event.key.code);
      }
   }

   lightMap->setActive(true);
   renderer->drawLights();
   lightMap->display();


   bool draw_debug = true;
   window->setActive(true);
   renderer->draw();

   const float lightModel[]= 
   {60, 0, 0, 0, 
      0, 60, 0, 0, 
      0, 0, 1, 0,
      0, 0, 0, 1};
   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glBlendFunc(GL_DST_COLOR, GL_ZERO);
   
   {
      ShaderProgram * prog = renderer->program;
      glEnable(GL_BLEND);
      lightMap->getTexture().bind();
      glUniform1i(prog->locationOfTex(), 1);
      glUniform4f(prog->locationOfUniform("color"), 1.0, 1.0, 1.0, 1.0);
      glUniformMatrix4fv(prog->locationOfUniform("viewMat"), 1, GL_FALSE, renderer->viewMatrix);
      glUniformMatrix4fv(prog->locationOfModelMat(), 1, GL_FALSE, lightModel);
      glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, 0);
      glDisable(GL_BLEND);
   }

   if (draw_debug)
   {
      ShaderProgram * prog = physics->m_debugDraw->shaderProgram;
      prog->setAsActive();
      float model[16] = {1,0,0,0,
         0,1,0,0,
         0,0,1,0,
         0,0,0,1};
      glUniformMatrix4fv(prog->locationOfUniform("viewMat"), 1, GL_FALSE, renderer->viewMatrix);
      glUniformMatrix4fv(prog->locationOfUniform("modelMat"), 1, GL_FALSE, model);
      physics->debugDraw();
   }
   window->display();
}

void Platform::update(double time)
{
   physics->tick(time);
}

bool Platform::isWindowOpen()
{
   return window->isOpen();
}

void Platform::addDrawCommand(int texid, Array a)
{
   if (a.size() == 16)
   {
      DrawCommand * command = new DrawCommand();
      VALUE * carr = a.to_c_array();
      for (int i = 0; i < 16; i++)
      {
         command->m[i] = (float)NUM2DBL(carr[i]);
      }
      command->texId = texid;
      renderer->addCommand(command);
   }
}

void Platform::addLightCommand(int texid, Array a)
{
   if (a.size() == 16)
   {
      DrawCommand * command = new DrawCommand();
      VALUE * carr = a.to_c_array();
      for (int i = 0; i < 16; i++)
      {
         command->m[i] = (float)NUM2DBL(carr[i]);
      }
      command->texId = texid;
      renderer->addLightCommand(command);
   }
}

void checkGLError()
{
   for (int e = glGetError(); e != GL_NO_ERROR; e = glGetError())
   {
      cout << "******************GLERROR****************";
      switch (e)
      {
         case GL_INVALID_ENUM:   cout << "OpenGL: Invalid enum" << endl; break;
         case GL_INVALID_VALUE:  cout << "OpenGL: Invalid value" << endl; break;
         case GL_INVALID_OPERATION:      cout << "OpenGL: Invalid operation" << endl; break;
         case GL_STACK_OVERFLOW:         cout << "OpenGL: Stack overflow" << endl; break;
         case GL_STACK_UNDERFLOW:        cout << "OpenGL: Stack underflow" << endl; break;
         case GL_OUT_OF_MEMORY:  cout << "OpenGL: Out of memory" << endl; break;
         default: cout << "OpenGL: Unknown Error" << endl;
      }
   }
}

int Platform::loadImage(string fileName)
{
   sf::Image image;

   if(!image.loadFromFile(fileName.c_str()))
   {
      return 0;
   }

   glActiveTexture(GL_TEXTURE0);
   GLuint textureID;
   glGenTextures(1, &textureID);
   glBindTexture(GL_TEXTURE_2D, textureID);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

   cout << "Loaded image " << fileName << " " << image.getSize().x << "x" << image.getSize().y << endl;
   
   checkGLError();
   return textureID;
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
      .define_constructor(Constructor<Platform, Rice::Object>())
      .define_method("addDrawCommand", &Platform::addDrawCommand)
      .define_method("addLightCommand", &Platform::addLightCommand)
      .define_method("setViewMatrix", &Platform::setViewMatrix)
      .define_method("physics=", &Platform::setPhysics)
      .define_method("isWindowOpen", &Platform::isWindowOpen)
      .define_method("loadImage", &Platform::loadImage)
      //.define_method("addWall", &Platform::addWall)
      //.define_method("addGrenade", &Platform::addGrenade)
      .define_method("update", &Platform::update)
      .define_method("draw", &Platform::draw);

   Data_Type<Physics> rb_cPhysics =
      define_class<Physics>("Physics")
      .define_constructor(Constructor<Physics, Rice::Object>())
      .define_method("addWall", &Physics::addWall)
      .define_method("addGrenade", &Physics::addGrenade)
      .define_method("addPlayer", &Physics::addPlayer)
      .define_method("addBoundaries", &Physics::addBoundaries)
      .define_method("update", &Physics::tick);

   Data_Type<Body> rb_cBody =
      define_class<Body>("Body")
      .define_method("pos", &Body::pos)
      .define_method("vel", &Body::getVel)
      .define_method("vel=", &Body::setVel)
      .define_method("id", &Body::getId)
      .define_method("push", &Body::push);

   /*
   Data_Type<Renderer> rb_cRenderer =
      define_class<Renderer>("Renderer")
      .define_constructor(Constructor<Renderer>())
      .define_method("update", &Platform::update);
      */
}
