# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -D _POSIX_C_SOURCE=199309L -pthread -lm
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
	$(CC) -o $@ $^ $(CFLAGS) 

# Regra para limpar os arquivos gerados
clean:
	rm -f mainRobo.o simulacaoAPI.o ../LIB_ADT/DstringAPI.o ../LIB_ADT/IntegralAPI.o ../LIB_ADT/MatrixAPI.o program