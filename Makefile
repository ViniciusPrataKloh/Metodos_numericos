CC := cc
CFLAGS := -g -Wall -Wextra -lm -w#-ansi
CPPFLAGS := #-DDEBUG
LD := cc
LDFLAGS := -g
MAIN := euler.c
LIBS :=

PROG := euler

${PROG}: ${OBJS}
	${LD} ${LDFLAGS} ${MAIN} ${CFLAGS} -o ${PROG} ${LIBS}

clean:
	rm -f ${PROG} ${OBJS}
	rm *.dat
	rm *.png

.PHONY: clean
