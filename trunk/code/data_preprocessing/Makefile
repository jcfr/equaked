OBJS     =  
DEST     = preprocess

CC       = g++
INCLUDES = 
CFLAGS   = -Wall -O2
CLIBS    = -lm

all: Makefile $(OBJS)
	$(CC) -o $(DEST) $(CFLAGS) $(OBJS) preprocess.c

%.o: Makefile %.c
	$(CC) -c -o $(*F).o $(CFLAGS) $(INCLUDES) $(*F).c

%.o: Makefile %.s
	$(CC) -c -o $(*F).o $(CFLAGS) $(INCLUDES) $(*F).s

%.o: Makefile %.S
	$(CC) -c -o $(*F).o $(CFLAGS) $(INCLUDES) $(*F).S

clean:
	rm -rf $(OBJS) $(DEST) preprocess.o
