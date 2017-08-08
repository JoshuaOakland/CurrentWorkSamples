CC = gcc
CFLAGS = -std=c11
LINKS = 
INCLUDES =
SOURCE = *.c
OUTFLAGS = -c
OBJECTS = *.o
OUTPUT = -o program

clean:
	rm *.o && rm program
objects:
	$(CC) $(CFLAGS) $(LINKS) $(INCLUDES) $(SOURCE) $(OUTFLAGS)
prog:
	$(CC) $(CFLAGS) $(LINKS) $(INCLUDES) $(OBJECTS) $(OUTPUT)	
all:
	make objects && make prog
