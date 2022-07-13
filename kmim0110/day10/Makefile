obj-m := blocking_IO.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

install: 
	make -C /lib/modules/`uname -r`/build M=`pwd` install
		
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
