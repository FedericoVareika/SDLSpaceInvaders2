build_run: 
	make build 
	make run

build: 
	gcc -Wall -std=c99 -I/opt/homebrew/include -L/opt/homebrew/lib -o spaceinvaders2 ./src/*.c -lSDL2

run:
	./spaceinvaders2

clean: 
	rm spaceinvaders2
