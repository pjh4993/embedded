CC=arm-unknown-linux-gnueabi-gcc
OBJ=main.o es01func.o
CFLAGS=-std=gnu99

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -g

main: $(OBJ)
	$(CC) -o $@ $^ -g

clean:
	rm -rf *.o
	rm -rf main
