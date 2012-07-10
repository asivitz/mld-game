require 'mkmf-rice'

dir_config('box2d')

is_macosx = (/darwin/ =~ RUBY_PLATFORM)
is_win32 = (/mswin32|mingw|cygwin|bccwin32/ =~ RUBY_PLATFORM)

if is_macosx
   $LDFLAGS = $LDFLAGS + " -framework OpenGL -framework SFML -framework sfml-graphics -framework sfml-window -framework sfml-system -lBox2D"
elsif is_win32
   $LDFLAGS = $LDFLAGS + " -lGL -lSFML -lsfml-graphics -lsfml-window -lsfml-system -lBox2D"
end


create_makefile('engine')
