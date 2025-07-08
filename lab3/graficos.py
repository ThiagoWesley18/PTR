import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

current_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(current_dir, 'arqSaida.csv')

robo = pd.read_csv(file_path)
print(robo.columns)

T = []
for i in range(1, len(robo['t'])):
    T.append(robo['t'][i] - robo['t'][i-1])

print("Periodo: " + str(len(T)))

T = pd.DataFrame(T)

# media 
Tmedia = np.mean(T)
print("Media: " + str(Tmedia))

# variância
print("Variancia: " + str(np.var(T, axis=0).item()))

# desvio padrão
print("Desvio padrão: " + str(np.std(T, axis=0).item()))

# maximo
print("Maximo: " + str(np.max(T)))

# minimo
print("Minimo: " + str(np.min(T)))

# jiter
Delta_T = T - Tmedia
Jitter = np.mean(np.abs(Delta_T))
print("Jitter: " + str(Jitter))



# gráfico
plt.figure(figsize=(8, 6))
plt.plot(robo['y1'], robo['y2'], label='Xc x Yc', color='r')
plt.title('Trajetória Xc x Yc')
plt.xlabel('Xc')
plt.ylabel('Yc')
plt.legend()
plt.grid(True)
plt.show(block=False)

# Manter as janelas abertas
input("Pressione Enter para fechar os gráficos...")