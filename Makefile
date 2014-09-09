all:
	gcc -Wall -g -o TripleTriad *.c `pkg-config --cflags --libs gtk+-3.0` -lm