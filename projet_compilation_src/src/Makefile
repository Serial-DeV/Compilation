
EXE=minicc
UTILS=utils
LIBUTILS=$(UTILS)/libminiccutils.a

DEBUG=0

ifeq ($(DEBUG),1)
	DEBUG_FLAGS=-DYYDEBUG=1
else
	DEBUG_FLAGS=
endif

CFLAGS = -O0 -g -std=c99 -DYY_NO_LEAKS
INCLUDE = -I$(UTILS)

all: minicc

minicc: y.tab.o lex.yy.o common.o passe1.o passe2.o
	gcc $(CFLAGS) $(INCLUDE) -L$(UTILS) y.tab.o lex.yy.o common.o passe1.o passe2.o -o $@ -lminiccutils

y.tab.c: grammar.y Makefile
	yacc -d grammar.y

lex.yy.c: lexico.l Makefile
	lex lexico.l

lex.yy.o: lex.yy.c
	gcc $(DEBUG_FLAGS) $(CFLAGS) $(INCLUDE) -o $@ -c $<

y.tab.o: y.tab.c
	gcc $(DEBUG_FLAGS) $(CFLAGS) $(INCLUDE) -o $@ -c $<

common.o: common.c common.h defs.h Makefile
	gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

passe1.o: passe1.c passe1.h Makefile
	gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

passe2.o: passe2.c passe2.h Makefile
	gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<


clean:
	rm -f *.o a.out *.s

realclean: clean
	rm -f y.tab.c y.tab.h lex.yy.c $(EXE)
