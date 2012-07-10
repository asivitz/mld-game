require 'mkmf-rice'

dir_config('box2d')

is_macosx = (/darwin/ =~ RUBY_PLATFORM)

if is_macosx
   $LDFLAGS = $LDFLAGS + " -framework OpenGL -framework SFML -framework sfml-graphics -framework sfml-window -framework sfml-system -lBox2D"
end


create_makefile('engine')
