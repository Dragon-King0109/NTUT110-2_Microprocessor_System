obj-m := demo.o
kernel_DIR := /usr/src/linux-headers-5.4.0-110-generic/
PWD := $(shell pwd)

all:
		make -C $(kernel_DIR) M=$(PWD)
clean:
		rm *.o *.ko *.mod.c
.PHONY:
		clean
