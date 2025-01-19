#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "../Dstring.h"
#include "../Matrix.h"
#include "../Integral.h"

int main(){
    printf("<----------Teste Dstring---------->\n");
    Dstring str1, str2, str3, str4, str5, str6, str8, str9;
    char *str7;
    str1 = $("Hello World!");
    str2= $("Ola Mundo!");
    str3 = $(123);
    str4 = $(123.23);
    str5 = $(1234567890L);
    str6 = $( (char)'A');
    str7 = dstringToChar(str1);
    printf("   str1: %s\n", str1.string);
    printf("   str2: %s\n", str2.string);

    printf("\n <----------Funcoes de Conversao---------->\n");
    printf(" - int para Dstring: %s\n", str3.string);
    printf(" - float para Dstring: %s\n", str4.string);
    printf(" - long para Dstring: %s\n", str5.string);
    printf(" - char 'A' para Dstring: %s\n", str6.string);
    printf(" - Dstring para char[0] de str1: %c\n", str7[0]);

    printf("\n <----------Funcao de Concatenacao---------->\n");
    str8 = $(" - ");
    str9 =  concat(str1, str8, str2, NULL);
    printf(" - str1 + str2: %s\n", str9.string);
    
    printf("\n <----------Tamanho da Dstring---------->\n");
    printf(" - Tamanho str1: %d\n", tamanho(str1));
    printf(" - Tamanho str2: %d\n", tamanho(str2));

    printf("\n<----------Teste Matrix---------->\n");

    Matrix matriz_1 = newMatrix(2, 2);
    Matrix matriz_2 = newMatrix(2, 2);

    matriz_1.matriz[0][0] = 1.5;
    matriz_1.matriz[0][1] = 2.6;
    matriz_1.matriz[1][0] = 3.7;
    matriz_1.matriz[1][1] = 4.8;
    for(int i = 0; i < matriz_1.linha; i++){
        for(int j = 0; j < matriz_1.coluna; j++){
            printf("   matriz_1[%d][%d]: %.2lf\n", i, j, matriz_1.matriz[i][j]);
        }
    }

    matriz_2.matriz[0][0] = 5.2;
    matriz_2.matriz[0][1] = 6.3;
    matriz_2.matriz[1][0] = 7.4;
    matriz_2.matriz[1][1] = 8.5;
    printf("\n");
    for(int i = 0; i < matriz_2.linha; i++){
        for(int j = 0; j < matriz_2.coluna; j++){
            printf("   matriz_2[%d][%d]: %.2lf\n", i, j, matriz_2.matriz[i][j]);
        }
    }

    printf("\n <----------Operacao de Matrizes---------->\n");
    printf(" - Soma de Matrizes:\n");
    Matrix matriz_Soma = sumMatrix(matriz_1, matriz_2);
    for(int i = 0; i < matriz_Soma.linha; i++){
        for(int j = 0; j < matriz_Soma.coluna; j++){
            printf("   matriz_Soma[%d][%d]: %.2lf\n", i, j, matriz_Soma.matriz[i][j]);
        }
    }
    printf("\n - Subtracao de Matrizes:\n");
    Matrix matriz_Sub = subMatrix(matriz_1, matriz_2);
    for(int i = 0; i < matriz_Sub.linha; i++){
        for(int j = 0; j < matriz_Sub.coluna; j++){
            printf("   matriz_Sub[%d][%d]: %.2lf\n", i, j, matriz_Sub.matriz[i][j]);
        }
    }
    printf("\n - Multiplicacao de Matrizes:\n");
    Matrix matriz_Mul = multMatrix(matriz_1, matriz_2);
    for(int i = 0; i < matriz_Mul.linha; i++){
        for(int j = 0; j < matriz_Mul.coluna; j++){
            printf("   matriz_Mul[%d][%d]: %.2lf\n", i, j, matriz_Mul.matriz[i][j]);
        }
    }
    printf("\n - Multiplicacao da Matriz_1 por Escalar 2:\n");
    Matrix matriz_MulEscalar = scalarMultMatrix(matriz_1, 2);
    for(int i = 0; i < matriz_MulEscalar.linha; i++){
        for(int j = 0; j < matriz_MulEscalar.coluna; j++){
            printf("   matriz_MulEscalar[%d][%d]: %.2lf\n", i, j, matriz_MulEscalar.matriz[i][j]);
        }
    }
    printf("\n - Soma da Matriz_1 por Escalar 2:\n");
    Matrix matriz_SomaEscalar = scalarSomaMatrix(matriz_1, 2);
    for(int i = 0; i < matriz_SomaEscalar.linha; i++){
        for(int j = 0; j < matriz_SomaEscalar.coluna; j++){
            printf("   matriz_SomaEscalar[%d][%d]: %.2lf\n", i, j, matriz_SomaEscalar.matriz[i][j]);
        }
    }
    printf("\n - Subtracao da Matriz_1 por Escalar 2:\n");
    Matrix matriz_SubEscalar = scalarSubMatrix(matriz_1, 2);
    for(int i = 0; i < matriz_SubEscalar.linha; i++){
        for(int j = 0; j < matriz_SubEscalar.coluna; j++){
            printf("   matriz_SubEscalar[%d][%d]: %.2lf\n", i, j, matriz_SubEscalar.matriz[i][j]);
        }
    }
    printf("\n - Transposta da Matriz_1:\n");
    Matrix matriz_transposta = transpostaMatrix(matriz_1);
    for(int i = 0; i < matriz_transposta.linha; i++){
        for(int j = 0; j < matriz_transposta.coluna; j++){
            printf("   matriz_transposta[%d][%d]: %.2lf\n", i, j, matriz_transposta.matriz[i][j]);
        }
    }
    printf("\n - Inversa da Matriz_1:\n");
    Matrix matriz_inversa = inversaMatrix(matriz_1);
    for(int i = 0; i < matriz_inversa.linha; i++){
        for(int j = 0; j < matriz_inversa.coluna; j++){
            printf("   matriz_inversa[%d][%d]: %.2lf\n", i, j, matriz_inversa.matriz[i][j]);
        }
    }
    printf("\n - Determinante da Matriz_1: \n");
    double matriz_det = detMatrix(matriz_1);
    printf("   matriz_det: %.2lf\n", matriz_det);

    printf("\n <----------Teste Integral---------->\n");

    printf(" - Integral definida de 0 a 2 de 2x^2: \n");
    FuncPointer Pfunc = func;
    double integral = simpsonRule(Pfunc, 0, 2, 100);
    printf("   integral: %.2lf\n", integral);

    printf("\n <----------Liberando Memoria---------->\n");
    freeDstring(str1, str2, str3, str4, str5, str6, str7, str8, str9, NULL);
    freeMatrix(matriz_1, matriz_2, matriz_Soma, matriz_Sub, matriz_Mul, matriz_MulEscalar, matriz_SomaEscalar, matriz_SubEscalar, matriz_transposta, matriz_inversa, NULL);
    return 0;
}

double func(double x){
        return 2 * pow(x, 2);
}

