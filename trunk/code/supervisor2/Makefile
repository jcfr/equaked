OBJS     = listener.o logger.o 
DEST     = supervisor2

CC       = g++
INCLUDES = 
CFLAGS   = -Wall -O2
CLIBS    = -lm

all: Makefile $(OBJS)
	$(CC) -o $(DEST) $(CFLAGS) $(OBJS) supervisor2.c

%.o: Makefile %.c
	$(CC) -c -o $(*F).o $(CFLAGS) $(INCLUDES) $(*F).c

%.o: Makefile %.s
	$(CC) -c -o $(*F).o $(CFLAGS) $(INCLUDES) $(*F).s

%.o: Makefile %.S
	$(CC) -c -o $(*F).o $(CFLAGS) $(INCLUDES) $(*F).S

clean:
	rm -rf $(OBJS) $(DEST) supervisor2.o
