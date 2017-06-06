all: calculator

calculator: source.c stack.c stack.h
	gcc -lm source.c stack.c stack.h -o calculator
clean:
	rm -rf *o calculator
	