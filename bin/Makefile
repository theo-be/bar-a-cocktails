CC = gcc -Wall
EXEC = menu
SRC = $(wildcard ../sources/*.c)
HEAD = $(SRC:.c=.h)
OBJ = $(SRC:.c=.o)
RM = rm -i

all : $(EXEC)

%.o : %.c
	$(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

.PHONY : clean

clean :
	$(RM) $(OBJ)

