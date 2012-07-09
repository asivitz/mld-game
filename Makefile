all: engine

engine: bin/ShaderProgram.o
	c++ main.cpp bin/ShaderProgram.o -lglfw -framework Cocoa -framework OpenGL -o bin/engine

bin/ShaderProgram.o: ShaderProgram.h ShaderProgram.cpp
	c++ -c ShaderProgram.cpp -o bin/ShaderProgram.o

clean:
	rm bin/engine bin/*.o
