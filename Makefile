build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o picker 
run:
	./picker
debug:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -g -o picker 
	gdb ./picker
clean:
	rm picker 
