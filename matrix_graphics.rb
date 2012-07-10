require 'matrix'

def vec2(x,y)
   Matrix.column_vector([x,y])
end

class Matrix
   #vector stuff
   def x
      self[0,0]
   end

   def x=(val)
      self[0,0] = val
   end
   
   def y
      self[1,0]
   end

   def y=(val)
      self[1,0] = val
   end

   def Matrix.ortho(left, right, bottom, top, near, far)
      Matrix[[2.0/(right - left), 0, 0, -(right + left)/(right - left)],
         [0, 2.0/(top - bottom), 0, -(top + bottom)/(top - bottom)],
         [0, 0, -2.0/(far - near), -(far + near)/(far - near)],
         [0, 0, 0, 1]]
   end

   def scale(x, y, z)
      Matrix[[x,0,0,0], [0,y,0,0], [0,0,z,0],[0,0,0,1]] * self
   end

   def translate(x, y, z)
      Matrix[[1,0,0,0], [0,1,0,0], [0,0,1,0],[x,y,z,1]] * self
   end

   def rotate(angle)
      cos = Math.cos(angle)
      sin = Math.sin(angle)
      Matrix[[cos, -sin, 0, 0], [sin, cos, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]] * self
   end

   def flatten
      self.to_a.flatten
   end
end
