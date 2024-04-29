build:
	gcc -Wall -std=c99 ./src/*.c -I"./libs/" -I"/usr/local/include" -lSDL2 -o renderer
run:
	./renderer
clear:
	rm renderer
