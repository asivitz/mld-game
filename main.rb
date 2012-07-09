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
   end
   
   def mat
      #p "mat!"
      #p "x: #{@x}"
      m = Matrix.identity(4)
      m = m.translate(@x,@y,0)
      m = m.scale(20,20,1)
   end
end

$running = true
$one = Player.new

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

platform = Platform.new

platform.addDrawCommand([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16])

view = Matrix.ortho(-150, 150, -150, 150, -30, 1)


platform.setViewMatrix(view.flatten)

while platform.isWindowOpen and $running
   model = $one.mat
   platform.addDrawCommand(model.flatten)
   platform.update

   platform.process_input
   $one.x += $one.ximp
end
