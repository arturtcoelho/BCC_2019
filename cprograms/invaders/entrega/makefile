CFLAGS = -Wall -Wextra -ansi
CC = gcc
LBLIBS = -lncurses

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = invaders

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)