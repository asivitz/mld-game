CFLAGS=-g -c -Wall
LDFLAGS=-lglfw -framework Cocoa -framework OpenGL

SOURCES=main.cpp ShaderProgram.cpp Renderer.cpp Platform.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin/engine


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	c++ $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	c++ $(CFLAGS) $< -o $@

clean:
	rm bin/engine *.o
