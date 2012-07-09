$: << File.expand_path(File.join(File.dirname(__FILE__),))

require 'ext/engine'
require 'matrix_graphics'

class Player
   attr_accessor :x,:y, :ximp, :yimp

   def initialize
      @x = 0.0
      @y = 0.0
      @ximp = 0.0
      @yimp = 0.0

      @texid = $platform.loadImage "images/bossfire.png"
   end
   
   def mat
      #p "mat!"
      #p "x: #{@x}"
      m = Matrix.identity(4)
      m = m.translate(@x,@y,0)
      m = m.scale(40,40,1)
   end

   def draw
      $platform.addDrawCommand(@texid, self.mat.flatten)
   end
end

class Platform
   def key_map
      @key_map ||= {}
   end

   def key_pressed code
      key_map[code] = true
   end

   def key_released code
      key_map[code] = nil
   end

   def process_input
      if key_map[71]
         $one.ximp = -1.0
      elsif key_map[72]
         $one.ximp = 1.0
      else
         $one.ximp = 0
      end

      if key_map[16]
         $running = false
      end
   end
end

$platform = Platform.new

$running = true
$one = Player.new


view = Matrix.ortho(-150, 150, -150, 150, -30, 1)


$platform.setViewMatrix(view.flatten)

while $platform.isWindowOpen and $running
   $one.draw
   $platform.update

   $platform.process_input
   $one.x += $one.ximp
end
