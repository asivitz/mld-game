#!/usr/bin/env ruby

#$: << File.expand_path(File.join(File.dirname(__FILE__),))

require_relative 'ext/engine'
require_relative 'matrix_graphics'
require_relative 'engine'

# maps physics body ids to game objects
$body_map = {}
$drawables = []

MAX_VEL = 10.0
MOVE_IMP = 4.0
JUMP_IMP = 140.0
class Player < WorldObj
   attr_reader :body
   attr_accessor :num_standing_on_solid

   def initialize pos
      @texid = $platform.loadImage "2player\ shooter/images/redGuyLeft.png"
      #@texid = $platform.loadImage "images/triangle.png"
      @body = $physics.addPlayer(pos, 2.0)
      $body_map[@body.id] = self
      @num_standing_on_solid = 0
      @jump_time = Time.now
      @fire_time = Time.now
      @last_faced_direction = 1
   end

   def begin_contact other
      if other.is_jump_platform
         @num_standing_on_solid += 1
      end
   end

   def end_contact other
      if other.is_jump_platform
         @num_standing_on_solid -= 1
      end
   end
   
   def mat
      m = Matrix.identity(4)
      pos = @body.pos
      m = m.translate(pos[0],pos[1],0)
      m = m.scale(-2 * @last_faced_direction,4,1)
   end

   def draw
      $platform.addDrawCommand(@texid, self.mat.flatten)
   end

   def move_right
      @last_faced_direction = 1
      if @body.vel.x < MAX_VEL
         @body.push([MOVE_IMP,0.0])
      end
   end

   def move_left
      @last_faced_direction = -1
      if @body.vel.x > -MAX_VEL
         @body.push([-MOVE_IMP,0.0])
      end
   end

   def jump
      if @num_standing_on_solid > 0 && (Time.now - @jump_time).to_f > 0.5
         @body.push([0.0,JUMP_IMP])
         @jump_time = Time.now
      end
   end

   def is_jump_platform
      true
   end

   def update time
      #factor = 1.0
      #factor = 4.0 if @num_standing_on_solid > 0
      vel = $one.body.vel
      vel.x *= 1.0 - 1.0 * time #* factor
      $one.body.vel = vel
   end

   def fire
      if (Time.now - @fire_time).to_f > 0.1
         pos = vec(*@body.pos)
         dir = vec(@last_faced_direction, 0.4).normalize
         pos += dir
         gren = Grenade.new pos.to_a
         $drawables << gren
         dir *= 100
         gren.body.push dir.to_a

         @fire_time = Time.now
      end
   end
end

def process_input key_map
   if key_map[71] # left arrow
      $one.move_left
   elsif key_map[72] # right arrow
      $one.move_right
   end
end

class Floor < WorldObj
   attr_reader :body

   def initialize pos
      #@texid = $platform.loadImage "2player\ shooter/images/redGuyLeft.png"
      @body = $physics.addWall(pos, [10.0, 1.0])
      $body_map[@body.id] = self
   end

   def is_jump_platform
      true # player can jump off of this
   end
end

class Grenade < WorldObj
   attr_reader :body

   def initialize pos
      @texid = $platform.loadImage "images/light.png"
      @body = $physics.addGrenade(pos,1.0)
      $body_map[@body.id] = self
   end

   def mat
      m = Matrix.identity(4)
      pos = @body.pos
      m = m.translate(pos[0],pos[1],0)
      m = m.scale(18,18,1)
   end

   def draw
      $platform.addLightCommand(@texid, self.mat.flatten)
   end
end

class Boundary < WorldObj
   attr_reader :body

   def initialize
      #@texid = $platform.loadImage "2player\ shooter/images/redGuyLeft.png"
      @body = $physics.addBoundaries(-28.0, 28.0, -28.0, 28.0)
      $body_map[@body.id] = self
   end

   def is_jump_platform
      true # player can jump off of this
   end
end

$platform = Platform.new
$physics = Physics.new
$platform.physics = $physics

$running = true
$one = Player.new [0,10]
$floor = Floor.new [0,0]
$boundary = Boundary.new

view = Matrix.ortho(-30, 30, -30, 30, -30, 1)

$platform.setViewMatrix(view.flatten)

timeStep = 1/60.0
lastTime = Time.now
accumTime = 0.0
while $platform.isWindowOpen and $running
   currentTime = Time.now
   accumTime += (currentTime - lastTime).to_f
   lastTime = currentTime

   while accumTime >= timeStep
      $physics.update(timeStep)
      accumTime -= timeStep

      $one.update timeStep
   end
   $one.draw
   $platform.draw
   $drawables.each { |d| d.draw }

   process_input $platform.key_map

end
