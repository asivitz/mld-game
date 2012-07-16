#!/usr/bin/env ruby

#$: << File.expand_path(File.join(File.dirname(__FILE__),))

require_relative 'ext/engine'
require_relative 'matrix_graphics'
require_relative 'engine'
require_relative 'sprites'

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
      @sprite = SpriteSheet.new "red_anims"
      @body = $physics.addPlayer(pos, 2.0)
      $body_map[@body.id] = self
      @num_standing_on_solid = 0
      @jump_time = Time.now
      @fire_time = Time.now
      @last_faced_direction = 1
      @animation_start = Time.now
      @animation_time = 0
      @current_animation = "red-idle"
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
      m = m.scale(-1 * @last_faced_direction,1,1)
   end

   def draw
      m = self.mat

      frame = @sprite.timed_frame(@current_animation, (@animation_time - @animation_time.to_i))

      w = frame.w
      h = frame.h

      m = m.translate(-0.4,-1.9,1)
      m = m.scale(0.08,0.08,1)

      if frame.rotated
         w = frame.h
         h = frame.w
         m = m.rotate(-Math::PI/2.0)

         m = m.translate(w/2.0,0,0)
         m = m.scale(w, h, 1)
      else
         m = m.translate(0,h/2.0,0)
         m = m.scale(w, h, 1)
      end

      $platform.addSpriteDrawCommand(@sprite.texid, m.flatten, [frame.x/@sprite.size[0], frame.y/@sprite.size[1], w/@sprite.size[0], h/@sprite.size[1]])
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
         @animation_time = 0.0
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


      delta = (Time.now - @animation_start).to_f
      @animation_start = Time.now

      if @num_standing_on_solid > 0
         speed = (vel.x).abs
         if speed > 2.5
            @current_animation = "red-run"
            delta *= speed / 8.0
         else
            @current_animation = "red-idle"
         end
         @animation_time += delta
      else
         @current_animation = "red-jump"
         @animation_time += delta
         @animation_time = [@animation_time, 0.99].min
      end
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
      @texid = load_image "images/triangle.png"
      @light_texid = load_image "images/light.png"
      @body = $physics.addGrenade(pos,1.0)
      $body_map[@body.id] = self
   end

   def draw
      m = Matrix.identity(4)
      pos = @body.pos
      m = m.translate(pos[0],pos[1],0)
      mat = m.scale(3,3,1)
      $platform.addDrawCommand(@texid, mat.flatten)
      light_mat = m.scale(25,25,1)
      $platform.addLightCommand(@light_texid, light_mat.flatten)
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
