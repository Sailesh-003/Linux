obj-m += sim_kthread.o
obj-m += mutex_kthread.o
obj-m += test1.o

all:
        make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
        make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
