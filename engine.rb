#platform is the game engine, not a real platform. bad name choice probably
#most of the class is defined in the C++ extension.
#this stuff is just extra hooks for input handling
class Platform
   def key_map
      @key_map ||= {}
   end

   def key_pressed code
      key_map[code] = true

      if code == 73 # up arrow
         $one.jump
      elsif code == 57
         $one.fire
      elsif code == 16 # letter q
         $running = false
      end
   end

   def key_released code
      key_map[code] = nil
   end
end

class Physics
   def post_collision enta, entb, impulse
      #p "collide #{enta} #{entb} #{impulse}"
   end

   def begin_contact enta, entb
      obj1 = $body_map[enta]
      obj2 = $body_map[entb]
      obj1.begin_contact(obj2)
      obj2.begin_contact(obj1)
   end

   def end_contact enta, entb
      obj1 = $body_map[enta]
      obj2 = $body_map[entb]
      obj1.end_contact(obj2)
      obj2.end_contact(obj1)
   end
end

class WorldObj
   def begin_contact other
   end

   def end_contact other
   end

   def is_jump_platform
      false
   end
end
