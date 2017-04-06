CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic
LIBS=
EXENAME=hsh

CFILES=\
	   tokenizer.c

GLOBAL_HEADERS=\
	header.h

# Make goals
all: $(GLOBAL_HEADERS) $(CFILES) main.c
	$(CC) $(CFLAGS) $(CFILES) main.c -o $(EXENAME) $(LIBS)

debug: $(GLOBAL_HEADERS) $(CFILES) main.c
	$(CC) $(CFLAGS) $(OFILES) main.c -o $(EXENAME) $(LIBS) -g

clean:
	rm -f $(EXENAME)