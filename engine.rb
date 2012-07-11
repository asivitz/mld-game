#platform is the game engine, not a real platform. bad name choice probably
#most of the class is defined in the C++ extension.
#this stuff is just extra hooks for input handling
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
end
