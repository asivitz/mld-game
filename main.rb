#!/usr/bin/env ruby

#$: << File.expand_path(File.join(File.dirname(__FILE__),))

require_relative 'ext/engine'
require_relative 'matrix_graphics'
require_relative 'engine'

# maps physics body ids to game objects
$body_map = {}

MAX_VEL = 5.0
MOVE_IMP = 2.0
JUMP_IMP = 20.0
class Player
   attr_accessor :pos, :move_imp
   attr_reader :body

   def initialize
      @move_imp = vec2(0.0,0.0)

      @texid = $platform.loadImage "images/triangle.png"
      @body = $platform.physics.addPlayer([0,5], 2.0)
      $body_map[@body.id] = self
   end
   
   def mat
      m = Matrix.identity(4)
      pos = @body.pos
      m = m.translate(pos.x,pos.y,0)
      m = m.scale(4,4,1)
   end

   def draw
      $platform.addDrawCommand(@texid, self.mat.flatten)
   end

   def move_right
      if @body.vel.x < MAX_VEL
         @body.push([MOVE_IMP,0.0])
      end
   end

   def move_left
      if @body.vel.x > -MAX_VEL
         @body.push([-MOVE_IMP,0.0])
      end
   end

   def jump
      @body.push([0.0,JUMP_IMP])
   end
end

def process_input key_map
   if key_map[71]
      $one.move_left
   elsif key_map[72]
      $one.move_right
   end

   if key_map[73]
      $one.jump
   end

   if key_map[16]
      $running = false
   end
end

$platform = Platform.new
wall = $platform.physics.addWall([0,0],[10,1])

$grenade = $platform.physics.addGrenade([0,10],1.0)

$running = true
$one = Player.new

view = Matrix.ortho(-15, 15, -15, 15, -30, 1)

$platform.setViewMatrix(view.flatten)

$phys = $platform.physics
timeStep = 1/60.0
lastTime = Time.now
accumTime = 0.0
while $platform.isWindowOpen and $running
   currentTime = Time.now
   accumTime += (currentTime - lastTime).to_f
   lastTime = currentTime

   while accumTime >= timeStep
      $phys.update(timeStep)
      accumTime -= timeStep
   end
   $one.draw
   $platform.draw

   process_input $platform.key_map
end
