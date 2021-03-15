CC = gcc

SRC = src

# Where the .a and .o files are compiled to
LIB = lib

PROGRAM = clog
CFLAGS= -Wall -g -std=gnu99

INC = -Iinclude

FILES = $(wildcard $(SRC)/*.c)
FILENAMES = $(basename $(notdir $(wildcard $(SRC)/*.c) ))

# Testing exclusive
TESTDIR = testing
TESTFILES = $(wildcard $(TESTDIR)/$(SRC)/*.c)
TESTBUILD = build
TESTPROGRAM = test
TESTLIB = -L . -l:lib/clog.a

all: debug

debug: 
	@mkdir -p $(LIB)

	for path in $(FILENAMES); do \
		$(CC) $(CFLAGS) -c $(SRC)/$$path.c $(INC) -o $(LIB)/$$path.o; \
	done

	ar rcs $(LIB)/$(PROGRAM).a $(wildcard $(LIB)/*.o)

test: debug

	@mkdir -p $(TESTDIR)/$(TESTBUILD)
	$(CC) $(CFLAGS) $(TESTFILES) $(TESTLIB) $(INC) -o $(TESTDIR)/$(TESTBUILD)/$(TESTPROGRAM)
	./$(TESTDIR)/$(TESTBUILD)/$(TESTPROGRAM)

clean:
	rm -rf $(LIB)/*
	rm -rf $(TESTDIR)/$(TESTBUILD)/*