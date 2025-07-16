import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

# -----#
from multiprocessing import shared_memory
import time

# Nome da memória compartilhada (sem o "/")
SHM_NAME = "buffer"
BUFFER_SIZE = 256 # Deve ser igual ao MAX_STR_SIZE no C

# Conecta à memória compartilhada existente
shm = shared_memory.SharedMemory(name=SHM_NAME)

# DataFrame onde vamos armazenar os dados
robo = pd.DataFrame(columns=["t", "y1", "y2", "teta", "xref", "yref"])

# Para verificar repetição
ultima_linha = ""

print("Lendo dados da Memória Compartilhada...\n")

try:
    while True:
        # Lê a string da memória compartilhada
        raw_bytes = bytes(shm.buf[:BUFFER_SIZE])  # Converte memoryview para bytes
        linha = raw_bytes.split(b'\x00', 1)[0].decode('utf-8').strip()

        # Encerra se o valor for "-1"
        if linha == "-1":
            print("Plotando Grafico...")
            break

        # Adiciona no DataFrame se for diferente da última
        if linha and linha != ultima_linha:
            # Exibe a linha lida
            try:
                valores = list(map(float, linha.split(",")))
                if len(valores) == 6:
                    robo .loc[len(robo )] = valores
                    ultima_linha = linha
            except ValueError:
                pass  # Ignora linhas mal formatadas
        
        # Aguarda um pouco antes de ler novamente
        time.sleep(0.600)

finally:
    # Fecha o acesso à memória compartilhada
    try:
        shm.close()
    except BufferError:
        print("Erro ao fechar a memória compartilhada. Certifique-se de que não há referências pendentes.")
    # Libera a memória compartilhada (desvincula)
    try:
        shm.unlink()
    except FileNotFoundError:
        print("Memória compartilhada já foi desvinculada.")
        

## Converte todos os dados do DataFrame para valores numéricos
#T = pd.Series(robo['t'].diff().dropna())
#
## Total
#print("Total: ", T.sum(), "s")
#
## Média
#Tmedia = T.mean()
#print("Média: ", Tmedia * 1000, "ms")
#
## Variância
#print("Variância: ", T.var() * 1000, "ms")
#
## Desvio padrão
#print("Desvio padrão: ", T.std() * 1000, "ms")
#
## Máximo
#print("Máximo: ", T.max() * 1000, "ms")
#
## Mínimo
#print("Mínimo: ", T.min() * 1000, "ms")
#
## Jitter
#Delta_T = T - Tmedia
#Jitter = Delta_T.abs().mean()
#print("Jitter: ", Jitter * 1000, "ms")

# Gráficos sobrepostos na mesma figura
plt.figure(figsize=(12, 8))
plt.plot(robo ['t'], robo ['xref'], label='Referência Xref', color='b')
plt.plot(robo ['t'], robo ['yref'], label='Trajetória Yref', color='r')
#plt.plot(T['t'], T['x2'], label='Trajetória Y', color='r')

plt.title('Comparação entre Trajetória de Referência')
plt.xlabel('Posição X')
plt.ylabel('Posição Y')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.show()

