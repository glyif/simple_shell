CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic
LIBS=
EXENAME=hsh

CFILES=\
	strings.c\
	getline.c\
	memmalloc.c\
	linked_helper.c\
	execfuncs.c\
	tokenizer.c\
	builtin_funcs.c\
	file_io.c\
	stdlib_funcs.c\
	path.c\
	ptree.c\
	parse.c\
	history.c\
	worker.c\
	pipeline.c\
	write.c

GLOBAL_HEADERS=\
	header.h

# Make goals
all: $(GLOBAL_HEADERS) $(CFILES) main.c
	$(CC) $(CFLAGS) $(CFILES) main.c -o $(EXENAME) $(LIBS)

debug: $(GLOBAL_HEADERS) $(CFILES) main.c
	$(CC) $(CFLAGS) $(CFILES) main.c -o $(EXENAME) $(LIBS) -g

clean:
	rm -f $(EXENAME)
