Hello World module
==================

Setup
-----

This is my first module and will be build out of the tree, i.e., we will need to
have a complete and precompiled kernel source tree and has to be the same
version of the host.

We have installed the prebuilt kernel, only headers, with:
```bash
sudo apt-get update
sudo apt-get install linux-headers-`uname-r`
```

The headers will be installed in `/usr/src/linux-headers-$(uname -r)` and
`/lib/modules/$(uname -r)/build` is a soft link that point to it.

Building and executing the module
---------------------------------

We are using `make`, so first we have to run it. This will generate the .ko and
some other files.

Then we have to load the module with `insmod` and unload it with `rmmod`.
The printed messages can be showned with `dmesg`.
```bash
make
sudo insmod helloworld.ko
sudo rmmod  helloworld.ko
dmesg
```
