INCLUDES=$(wildcard *.h)
SOURCES=$(wildcard *.c)
OBJFILES=$(SOURCES:.c=.o)
EXEC=corectl
CARGS=-Wall -g -Werror
LDARGS=
CC=gcc

.SUFFIXES : .c .o

.c.o:
	@echo "CC $< > $@"
	@$(CC) $(CARGS) -c $<

${EXEC}: ${OBJFILES}
	@echo "CC $^ > $@"
	@$(CC) $(CARGS) $(LDARGS) -o $@ $^

${OBJFILES}: ${SOURCES} ${INCLUDES}

run: ${EXEC}
	./${EXEC}

clean:
	rm -f ${OBJFILES} ${EXEC}

install: corectl
	install corectl /usr/local/bin/corectl
	chown root:wheel /usr/local/bin/corectl
	chmod u+s /usr/local/bin/corectl
	chmod o-x /usr/local/bin/corectl

uninstall:
	rm /usr/local/bin/corectl
