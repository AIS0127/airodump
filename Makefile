
CC = gcc

all: airodump

airodump: main.o airodump.o
	gcc -o airodump main.o airodump.o  -lpcap 
main.o: main.c 
	gcc -c -o main.o main.c
airodump.o: airodump.c 
	gcc -c -o airodump.o airodump.c
clean:
	rm -f *.o airodump
