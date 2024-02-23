# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -D _POSIX_C_SOURCE=199309L
DEPS = ../LIB_ADT/*.h *.h
SRC = $(wildcard *.c ../LIB_ADT/*.c)
OBJ = $(SRC:.c=.o)
EXEC = program

# Regra padrão
all: $(EXEC)

# Regra para o arquivo objeto
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Regra para o executável
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)