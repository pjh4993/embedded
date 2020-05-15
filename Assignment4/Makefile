BUILDROOT_OUTPUT=/embedded/buildroot/output
KERNEL_DIR=$(BUILDROOT_OUTPUT)/build/linux-custom/
CROSS_COMPILE=$(BUILDROOT_OUTPUT)/host/bin/arm-linux-gcc

obj=util.o main.o
all: main

%.o: %.c
	$(CROSS_COMPILE) -c -o $@ $< -g

main: $(obj)
	$(CROSS_COMPILE) -o $@ $^ -g
	
clean:
	rm -rf *.o
	rm -rf main
