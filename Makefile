CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRCS = main.c funcoes.c
OBJS = $(SRCS:.c=.o)
TARGET = meu_programa

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c funcoes.h
    $(CC) $(CFLAGS) -c main.c

funcoes.o: funcoes.c funcoes.h
    $(CC) $(CFLAGS) -c funcoes.c

clean:
    rm -f $(OBJS) $(TARGET)
