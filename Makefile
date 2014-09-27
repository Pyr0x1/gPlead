all:
	gcc -Wall -g -o TripleTriad src/*.c `pkg-config --cflags --libs gtk+-3.0` -lm

