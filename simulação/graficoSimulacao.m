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




% Plota os dados
plot(y1, y2);
hold on;
grid on;
title("Saida Yc");


% Adicionar legendas aos eixos
xlabel('Xc');
ylabel('Yc');