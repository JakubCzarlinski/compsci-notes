CFLAGS	:= -g -Wall
LFLAGS	:=

EXE	:= $(BIN_DIR)/main

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INC_DIR := ../include

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INC_DIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

.PHONY: all clean

all: main

main: main.o processes.o
	gcc ./obj/main.o ./obj/processes.o -o ./bin/main

main.o: main.c
	gcc -c main.c -o ./obj/main.o

processes.o: ./src/processes.c ./include/processes.h
	gcc -c ./src/processes.c -o ./obj/processes.o -I.

clean:
	rm -f ./$(OBJ_DIR)/*.o ./$(BIN_DIR)/$(EXE)
