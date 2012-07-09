$: << File.expand_path(File.join(File.dirname(__FILE__),))

require 'ext/engine'
require 'matrix_graphics'

platform = Platform.new

platform.addDrawCommand([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16])

view = Matrix.ortho(-150, 150, -150, 150, -30, 1)


platform.setViewMatrix(view.flatten)

model = Matrix.identity(4)
model = model.scale(50, 50, 1)

while true
   model = model.rotate(0.1)
   platform.addDrawCommand(model.flatten)
   platform.update
end
