$: << File.expand_path(File.join(File.dirname(__FILE__),))

require 'ext/engine'
require 'matrix'

platform = Platform.new

platform.addDrawCommand([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16])


def ortho(left, right, bottom, top, near, far)
  Matrix[[2.0/(right - left), 0, 0, -(right + left)/(right - left)],
     [0, 2.0/(top - bottom), 0, -(top + bottom)/(top - bottom)],
     [0, 0, -2.0/(far - near), -(far + near)/(far - near)],
     [0, 0, 0, 1]]
end

def scale(mat, x, y, z)
   Matrix[[x,0,0,0], [0,y,0,0], [0,0,z,0],[0,0,0,1]] * mat
end

view = ortho(-150, 150, -150, 150, -30, 1)


platform.setViewMatrix(view.to_a.flatten)

model = Matrix.identity(4)
scale(model, 50, 50, 1)

while true
   platform.addDrawCommand(model.to_a.flatten)
   platform.update
end
