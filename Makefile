CC = gcc
CFLAGS = -Wall

OBJECTS = main.o preprocessor.o comment_removal.o macro_handler.o file_inclusion.o

all: mypreprocessor

mypreprocessor: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o mypreprocessor

main.o: main.c preprocessor.h
	$(CC) $(CFLAGS) -c main.c

preprocessor.o: preprocessor.c preprocessor.h comment_removal.h macro_handler.h file_inclusion.h
	$(CC) $(CFLAGS) -c preprocessor.c

comment_removal.o: comment_removal.c comment_removal.h
	$(CC) $(CFLAGS) -c comment_removal.c

macro_handler.o: macro_handler.c macro_handler.h preprocessor.h
	$(CC) $(CFLAGS) -c macro_handler.c

file_inclusion.o: file_inclusion.c file_inclusion.h
	$(CC) $(CFLAGS) -c file_inclusion.c

clean:
	rm -f $(OBJECTS) mypreprocessor inputfile.i

.PHONY: all clean
