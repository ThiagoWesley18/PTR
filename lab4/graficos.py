import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

current_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(current_dir, 'arqSaida.csv')

robo = pd.read_csv(file_path)

T = []
for i in range(1, len(robo['t'])):
    T.append(robo['t'][i] - robo['t'][i-1])

print("Total: ", sum(T), "s")
T = pd.DataFrame(T)

# media 
Tmedia = np.mean(T)
print("Media: ", Tmedia * 1000, "ms")

# variância
print("Variancia: ", np.var(T, axis=0).item() * 1000, "ms")

# desvio padrão
print("Desvio padrão: ", np.std(T, axis=0).item() * 1000, "ms")

# maximo
print("Maximo: ", np.max(T) * 1000, "ms")

# minimo
print("Minimo: ", np.min(T) * 1000, "ms")

# jiter
Delta_T = T - Tmedia
Jitter = np.mean(np.abs(Delta_T))
print("Jitter: ", Jitter * 1000, "ms")


# Gráficos sobrepostos na mesma figura
plt.figure(figsize=(12, 8))
#plt.plot(robo['t'], robo['xref'], label='Referência Xref', color='b')
#plt.plot(robo['t'], robo['yref'], label='Trajetória Yref', color='r')
#plt.plot(robo['t'], robo['x2'], label='Trajetória Y', color='r')

plt.title('Comparação entre Trajetória de Referência')
plt.xlabel('Posição X')
plt.ylabel('Posição Y')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.show()

