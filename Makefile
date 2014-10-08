all:
	gcc -Wall -g -o gPlead src/*.c `pkg-config --cflags --libs gtk+-3.0` -lm

