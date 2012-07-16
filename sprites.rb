require 'json'

$tex_map = {}

def load_image name
   texid = $tex_map[name]
   if not texid
      texid = $platform.loadImage name
      $tex_map[name] = texid
   end
   texid
end

class SpriteSheet
   attr_accessor :texid

   def initialize name
      @metadata = JSON.load File.new("images/#{name}.json") 
      @texid = load_image "images/#{name}.png"
      info = @metadata["meta"]
      @size = [info["size"]["w"], info["size"]["h"]]
   end

   def info name
      info = @metadata["frames"]["#{name}.png"]
      frame = info["frame"]
      x = Float(frame["x"]) / @size[0]
      y = Float(@size[1] - frame["y"]) / @size[1]
      w = Float(frame["w"]) / @size[0]
      h = Float(frame["h"]) / @size[1]
      [x,y,w,h]
   end
end
