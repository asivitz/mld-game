CFLAGS=-g -c -Wall
LDFLAGS=-lglfw -framework Cocoa -framework OpenGL

SOURCES=main.cpp ShaderProgram.cpp Renderer.cpp Platform.cpp
OBJECTS=$(addprefix bin/, $(SOURCES:.cpp=.o))
EXECUTABLE=bin/engine


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	c++ $(LDFLAGS) $(OBJECTS) -o $@

bin/%.o: %.cpp
	c++ $(CFLAGS) $< -o $@

clean:
	rm bin/engine bin/*.o
