all: engine

engine: ShaderProgram.o
	c++ main.cpp ShaderProgram.o -lglfw -framework Cocoa -framework OpenGL -o bin/engine

ShaderProgram.o: ShaderProgram.h ShaderProgram.cpp
	c++ -c ShaderProgram.cpp

clean:
	rm bin/engine
