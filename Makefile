FLAGS=-g

all: engine

engine: bin/ShaderProgram.o bin/Renderer.o
	c++ $(FLAGS) main.cpp bin/ShaderProgram.o bin/Renderer.o -lglfw -framework Cocoa -framework OpenGL -o bin/engine

bin/ShaderProgram.o: ShaderProgram.h ShaderProgram.cpp
	c++ $(FLAGS) -c ShaderProgram.cpp -o bin/ShaderProgram.o

bin/Renderer.o: Renderer.h Renderer.cpp bin/ShaderProgram.o
	c++ $(FLAGS) -c Renderer.cpp -o bin/Renderer.o

clean:
	rm bin/engine bin/*.o
