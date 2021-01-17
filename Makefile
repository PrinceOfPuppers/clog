CC = gcc

SRC = src
BUILD = lib
PROGRAM = clog
CFLAGS= -Wall -g -std=gnu99

INC = include
FILES = $(wildcard $(SRC)/*.c)


all: debug

debug: 
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $(FILES) -I$(INC) -o $(BUILD)/$(PROGRAM).o
	ar rcs lib/clog.a lib/clog.o 

clean:
	rm -rf $(BUILD)/*