import pandas as pd
import matplotlib.pyplot as plt

robo = pd.read_csv('arqSaida.csv')
robo.columns


plt.figure(figsize=(10, 6))
plt.plot(robo['t'], robo['v'], label='Velocidade Linear', color='b')


plt.title('Parte v(t) - velocidade linear')
plt.xlabel('Tempo (t)')
plt.ylabel('Valores de v')
plt.legend()
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(robo['t'], robo['w'], label='Velocidade Angular', color='r')


plt.title('Parte w(t) - velocidade Angular')
plt.xlabel('Tempo (t)')
plt.ylabel('Valores de w')
plt.legend()
plt.show()