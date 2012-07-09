$: << File.expand_path(File.join(File.dirname(__FILE__),))

require 'ext/engine'

platform = Platform.new

platform.addDrawCommand([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16])

while true
   platform.update
end
