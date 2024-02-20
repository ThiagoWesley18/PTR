clc,clear,close all

% Abre o arquivo 'teste.txt' para leitura
fileID = fopen('resultado.txt','r');

% Define o formato dos dados
formatSpec = '%f [%f %f] [%f %f %f]';

% Lê os dados do arquivo
dados = fscanf(fileID, formatSpec, [6 Inf]);

% Fecha o arquivo
fclose(fileID);

% Transpõe a matriz para que cada linha corresponda a uma entrada de dados
dados = dados';

% Extrai os vetores x, u1, u2, y1, y2 e y3 dos dados
t = dados(:,1);
u1 = dados(:,2);
u2 = dados(:,3);
y1 = dados(:,4);
y2 = dados(:,5);
y3 = dados(:,6);

y = [y1 y2 y3];
u = [u1, u2];

% Plota os dados
plot(t,y);
%plot(t,u);
hold on;
grid on;
legend('t','y');

% Definir os limites dos eixos x e y
axis([-1 21 -1 1]);

% Adicionar legendas aos eixos
xlabel('Tempo (s)');
ylabel('Trajetoria');