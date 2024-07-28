build:
	clang -Wall -std=c++20 ./src/*.cpp -I"./libs/" -I"/usr/local/include" -lSDL2 -o renderer
run:
	./renderer
clear:
	rm renderer
