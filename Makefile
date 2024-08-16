CC=gcc

SRC=$(shell find . -name "*.c")
OBJ=$(SRC:%=%.o)

FLAGS=-g -Wall
CFLAGS=$(FLAGS)
LDFLAGS=$(FLAGS)

APP=game

.PHONY: app clean

app: $(APP)

clean:
	rm -f $(OBJ) $(APP)

$(APP): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.c.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@
