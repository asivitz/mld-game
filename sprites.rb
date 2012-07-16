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

class SpriteFrame
   attr_accessor :x, :y, :w, :h, :rotated
end

class SpriteSheet
   attr_accessor :texid
   attr_reader :size

   def initialize name
      @metadata = JSON.load File.new("images/#{name}.json") 
      @texid = load_image "images/#{name}.png"
      info = @metadata["meta"]
      @size = [info["size"]["w"], info["size"]["h"]]

      @frames = {}

      @anim_counts = {}

      @metadata["frames"].keys.each do |key|
         data = /(.*)(\d{4})/.match(key)
         name = data[1]
         prev = @anim_counts[name]
         prev = 0 if prev.nil?
         @anim_counts[name] = [prev, data[2].to_i].max
      end
      p @anim_counts
   end

   def timed_frame(name, fraction)
      count = @anim_counts[name]
      idx = (fraction * count).floor + 1
      key = name + "%04d" % idx
      self.frame key
   end

   def frame name
      frame = @frames[name]
      if not frame
         info = @metadata["frames"]["#{name}.png"]
         frame_info = info["frame"]

         frame = SpriteFrame.new
         frame.x = Float(frame_info["x"])
         frame.y = Float(frame_info["y"])
         frame.w = Float(frame_info["w"])
         frame.h = Float(frame_info["h"])

         frame.rotated = info["rotated"]
         @frames[name] = frame
      end
      frame
   end
end
