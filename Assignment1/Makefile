CC=arm-unknown-linux-gnueabi-gcc
OBJswitch=es01switch.o es01func.o
OBJclear=es01clear.o es01func.o
CFLAGS=-std=gnu99

all: switch clear
	rm -rf *.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -g

switch: $(OBJswitch)
	$(CC) -o $@ $^ -g

clear: $(OBJclear)
	$(CC) -o $@ $^ -g

clean:
	rm -rf switch
	rm -rf clear
