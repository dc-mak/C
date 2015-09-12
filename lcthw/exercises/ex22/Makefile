CFLAGS=-Wall -g
CPPFLAGS=-DNDEBUG

all: ex22_main

ex22_main: ex22.o
	cc $(CFLAGS) $(CPPFLAGS) ex22_main.c ex22.o -o ex22_main

ex22.o:
	cc $(CFLAGS) $(CPPFLAGS) -c -o ex22.o ex22.c

clean:
	\rm -f ex22.o ex22_main
