IDIR =../include
CC=g++
CFLAGS=-std=c++1y -I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lboost_unit_test_framework

_DEPS = parray.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tests.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all run clean
all : test run

$(ODIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run:  test
	./test

clean:
	rm -rf $(ODIR) test
