PREFIX= /usr/local
CFLAGS= -g -DATW_VERSION -I../
PRODFLAGS = -O3 -m32 #-pg -g3
LIB=libbud.a
DEVFLAGS = -O0 -g3 -DDEBUG -Wunused -Wreturn-type -Wimplicit-int #-Wall

OS := $(shell uname -s | tr "[:upper:]" "[:lower:]")


CFLAGS += -pthread

OBJS= main.o m.o y.o u.o p.o r.o k.o f.o s.o o.o n.o i.o q.o j.o b.o nsf.o z.o \
	../dap/argsfirst.o ../dap/argsgetopt.o ../dap/error.o ../dap/args_data.o \
	../dap/brealloc.o ../dap/bfree.o ../dap/balloc.o ../dap/buffalloc.o \
	../dap/argsnext.o ../dap/buffputlong.o ../dap/buffstuff.o ../dap/buffroom.o \
	../dap/ultohex.o ../dap/ultodec.o

LDFLAGS = -lm -ldl

all: bud

lib: $(LIB)

$(LIB): $(OBJS)
	$(AR) crv $@ $(OBJS)

bud: CFLAGS += $(PRODFLAGS)
bud: $(OBJS) 
	$(CC) ${CFLAGS} $^ -o $@ $(LDFLAGS)

install:
	install bud $(PREFIX)/bin/bud

clean:
	$(RM) -r bud *.exe  a/*.o

TAGS: *.c *.h
	etags *.[ch]

%.t.o: %.c
	$(CC) $(CFLAGS) -c $(CPPFLAGS) -o $@ $<

.PHONY: all clean install

# Dependencies.
${OBJS}: u.h
${OBJS}: k.h
main.o nsf.o y.o j.o m.o n.o k.o i.o f.o s.o o.o u.o p.o: f.h
u.o p.o: s.h
nsf.o: fir.h
nsf.o n.o: x.h
main.o: args.h


# DO NOT DELETE
