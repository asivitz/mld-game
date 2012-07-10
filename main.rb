#!/usr/bin/env ruby

#$: << File.expand_path(File.join(File.dirname(__FILE__),))

require_relative 'ext/engine'
require_relative 'matrix_graphics'
require_relative 'engine'

class Player
   attr_accessor :pos, :move_imp

   def initialize
      @pos = vec2(0.0,0.0)
      @move_imp = vec2(0.0,0.0)

      @texid = $platform.loadImage "images/triangle.png"
   end
   
   def mat
      m = Matrix.identity(4)
      m = m.translate(@pos.x,@pos.y,0)
      m = m.scale(40,40,1)
   end

   def draw
      $platform.addDrawCommand(@texid, self.mat.flatten)
   end
end

def process_input key_map
   if key_map[71]
      $one.move_imp.x = -1.0
   elsif key_map[72]
      $one.move_imp.x = 1.0
   else
      $one.move_imp.x = 0
   end

   if key_map[16]
      $running = false
   end
end

def update
   $one.pos += $one.move_imp
end

$platform = Platform.new
wall = $platform.addWall(10,10,100,10)
$platform.addWall(10,40,100,10)

grenade = $platform.addGrenade(10,60,5)

$running = true
$one = Player.new

view = Matrix.ortho(-150, 150, -150, 150, -30, 1)

$platform.setViewMatrix(view.flatten)

while $platform.isWindowOpen and $running
   $one.draw
   $platform.update

   process_input $platform.key_map
   update
end
