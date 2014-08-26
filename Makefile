.PHONY: clean

CFILES = sse-sort

CC 		= gcc
AR 		= ar

APP		= sse-sort
SRC   = $(wildcard *.c)
OBJ   = $(addsuffix .o, $(basename $(SRC)))
ASM   = $(addsuffix .s, $(basename $(SRC)))
BIN   = $(APP)

WARN_FLAGS = -Wno-unused-but-set-variable -Wno-unused-variable -Wno-implicit-function-declaration
CFLAGS    += -m32 -msse -Wall -g -O3 $(WARN_FLAGS)
INCLUDE   += -I./
LDFLAGS    = -lm -lrt

#======================================================
all: clean comp run-csl

comp: $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(LDFLAGS) $(CFLAGS)

asm: $(ASM)

run-csl:
	./$(BIN)

%.s: %.c
	$(CC) -S $(CFLAGS) $<

%.o: %.c
	@$(CC) -c $(CFLAGS) $(INCLUDE) $<

clean:
	rm -f $(BIN) *.s *.o
