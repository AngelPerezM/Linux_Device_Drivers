# obj-<X>, where <X> is set to
# m, built as a module
# y, built as part of the kernel (built-in module)
# n, not be built
obj-m :=helloworld.o

KERNEL_DIR ?=/lib/modules/$(shell uname -r)/build

all default: modules
install: modules_install

# M: directory of the external module to be built, wher .c is located.
modules modules_install help:
	$(MAKE) -C $(KERNEL_DIR) M=$(shell pwd) $@

check: modules
	$(info Nothing to test if it was build.)

clean:
	rm -f ${obj-m}
