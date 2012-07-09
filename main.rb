$: << File.expand_path(File.join(File.dirname(__FILE__),))

require 'ext/engine'

platform = Platform.new

while true
   platform.update
end
