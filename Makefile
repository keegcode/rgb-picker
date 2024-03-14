build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o picker 
run:
	./picker
clean:
	rm picker 
