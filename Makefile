CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic
LIBS=
EXENAME=hsh

CFILES=\
	aliasA.c\
	aliasB.c\
	buildarginv.c\
	builtinA.c\
	builtinB.c\
	cd.c\
	environA.c\
	environB.c\
	executeA.c\
	executeB.c\
	file_io.c\
	free.c\
	getline.c\
	helpA.c\
	helpB.c\
	history.c\
	memmalloc.c\
	parseA.c\
	parseB.c\
	path.c\
	pipeline.c\
	ptree.c\
	stdlib_funcs.c\
	stringsA.c\
	stringsB.c\
	stringsC.c\
	tokenize.c\
	tokenizer.c\
	worker.c\
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
