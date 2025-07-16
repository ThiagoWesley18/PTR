#!/bin/bash

# Executa o make para compilar o programa
make

# Verifica se o make foi bem-sucedido
if [ $? -ne 0 ]; then
    echo "Erro ao compilar o programa. Abortando."
    exit 1
fi




# Executa o programa ./lab4 em segundo plano
./lab4 &

# Salva o PID do processo ./lab4
PID_LAB4=$!


# Executa o script Python graficos.py
python3 graficos.py

# Aguarda o término do processo ./lab4
wait $PID_LAB4

