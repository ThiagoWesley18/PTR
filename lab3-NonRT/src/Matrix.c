#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "Matrix.h"

Matrix newMatrix(int linha, int coluna){
    Matrix matrix;
    matrix.linha = linha;
    matrix.coluna = coluna;

    matrix.matriz = malloc(linha * sizeof(double*));
     if(matrix.matriz != NULL){
        for(int i = 0; i < linha; i++){
            matrix.matriz[i] = malloc(coluna * sizeof(double));
            if(matrix.matriz[i] == NULL){
                printf("Falha na alocação de memória.\n");
                exit(1);
            }
        }
    } else {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }
    
    return matrix;
}

Matrix sumMatrix(Matrix matrix1, Matrix matrix2){
    Matrix matrix;
    matrix.linha = matrix1.linha;
    matrix.coluna = matrix1.coluna;

    if(matrix1.linha != matrix2.linha || matrix1.coluna != matrix2.coluna){
        printf("Erro: As matrizes devem ter as mesmas dimensões para a soma.\n");
        exit(1);
    }

    matrix.matriz = malloc(matrix.linha * sizeof(double*));
    if(matrix.matriz == NULL){
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for(int i = 0; i < matrix.linha; i++){
        matrix.matriz[i] = malloc(matrix.coluna * sizeof(double));
        if(matrix.matriz[i] == NULL){
            printf("Falha na alocação de memória.\n");
            exit(1);
        }
    }

    for(int i = 0; i < matrix.linha; i++){
        for(int j = 0; j < matrix.coluna; j++){
            matrix.matriz[i][j] = matrix1.matriz[i][j] + matrix2.matriz[i][j];
        }
    }
    return matrix;
}

Matrix subMatrix(Matrix matrix1, Matrix matrix2){
    if(matrix1.linha != matrix2.linha || matrix1.coluna != matrix2.coluna){
        printf("Erro: As matrizes devem ter as mesmas dimensões para a subtração.\n");
        exit(1);
    }

    Matrix matrix;
    matrix.linha = matrix1.linha;
    matrix.coluna = matrix1.coluna;

    matrix.matriz = malloc(matrix.linha * sizeof(double*));
    if(matrix.matriz == NULL){
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for(int i = 0; i < matrix.linha; i++){
        matrix.matriz[i] = malloc(matrix.coluna * sizeof(double));
        if(matrix.matriz[i] == NULL){
            printf("Falha na alocação de memória.\n");
            exit(1);
        }
    }

    for(int i = 0; i < matrix.linha; i++){
        for(int j = 0; j < matrix.coluna; j++){
            matrix.matriz[i][j] = matrix1.matriz[i][j] - matrix2.matriz[i][j];
        }
    }
    return matrix;
}

Matrix multMatrix(Matrix matrix1, Matrix matrix2){
    if(matrix1.coluna != matrix2.linha){
        printf("Erro: O número de colunas da primeira matriz deve ser igual ao número de linhas da segunda matriz.\n");
        exit(1);
    }

    Matrix matrix;
    matrix.linha = matrix1.linha;
    matrix.coluna = matrix2.coluna;

    matrix.matriz = malloc(matrix.linha * sizeof(double*));
    if(matrix.matriz == NULL){
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for(int i = 0; i < matrix.linha; i++){
        matrix.matriz[i] = malloc(matrix.coluna * sizeof(double));
        if(matrix.matriz[i] == NULL){
            printf("Falha na alocação de memória.\n");
            exit(1);
        }
    }

    for(int i = 0; i < matrix.linha; i++){
        for(int j = 0; j < matrix.coluna; j++){
            matrix.matriz[i][j] = 0;
            for(int k = 0; k < matrix1.coluna; k++){
                matrix.matriz[i][j] += matrix1.matriz[i][k] * matrix2.matriz[k][j];
            }
        }
    }
    return matrix;
}

Matrix scalarMultMatrix(Matrix matrix, double scalar){
    Matrix matrixMult;
    matrixMult.linha = matrix.linha;
    matrixMult.coluna = matrix.coluna;

    matrixMult.matriz = malloc(matrixMult.linha * sizeof(double*));
    if(matrixMult.matriz == NULL){
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for(int i = 0; i < matrixMult.linha; i++){
        matrixMult.matriz[i] = malloc(matrixMult.coluna * sizeof(double));
        if(matrixMult.matriz[i] == NULL){
            printf("Falha na alocação de memória.\n");
            exit(1);
        }
    }

    for(int i = 0; i < matrixMult.linha; i++){
        for(int j = 0; j < matrixMult.coluna; j++){
            matrixMult.matriz[i][j] = matrix.matriz[i][j] * scalar;
        }
    }
    return matrixMult;
}

Matrix scalarSomaMatrix(Matrix matrix, double scalar){
    Matrix matrixSoma;
    matrixSoma.linha = matrix.linha;
    matrixSoma.coluna = matrix.coluna;

    matrixSoma.matriz = malloc(matrixSoma.linha * sizeof(double*));
    if(matrixSoma.matriz == NULL){
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for(int i = 0; i < matrixSoma.linha; i++){
        matrixSoma.matriz[i] = malloc(matrixSoma.coluna * sizeof(double));
        if(matrixSoma.matriz[i] == NULL){
            printf("Falha na alocação de memória.\n");
            exit(1);
        }
    }

    for(int i = 0; i < matrixSoma.linha; i++){
        for(int j = 0; j < matrixSoma.coluna; j++){
            matrixSoma.matriz[i][j] = matrix.matriz[i][j] + scalar;
        }
    }
    return matrixSoma;
}

Matrix scalarSubMatrix(Matrix matrix, double scalar){
    Matrix matrixSub;
    matrixSub.linha = matrix.linha;
    matrixSub.coluna = matrix.coluna;

    matrixSub.matriz = malloc(matrixSub.linha * sizeof(double*));
    if(matrixSub.matriz == NULL){
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for(int i = 0; i < matrixSub.linha; i++){
        matrixSub.matriz[i] = malloc(matrixSub.coluna * sizeof(double));
        if(matrixSub.matriz[i] == NULL){
            printf("Falha na alocação de memória.\n");
            exit(1);
        }
    }

    for(int i = 0; i < matrixSub.linha; i++){
        for(int j = 0; j < matrixSub.coluna; j++){
            matrixSub.matriz[i][j] = matrix.matriz[i][j] - scalar;
        }
    }
    return matrixSub;
}

Matrix transpostaMatrix(Matrix matrix){
    Matrix matrixTransposta;
    matrixTransposta.linha = matrix.coluna;
    matrixTransposta.coluna = matrix.linha;

    matrixTransposta.matriz = malloc(matrixTransposta.linha * sizeof(double*));
    if(matrixTransposta.matriz == NULL){
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for(int i = 0; i < matrixTransposta.linha; i++){
        matrixTransposta.matriz[i] = malloc(matrixTransposta.coluna * sizeof(double));
        if(matrixTransposta.matriz[i] == NULL){
            printf("Falha na alocação de memória.\n");
            exit(1);
        }
    }

    for(int i = 0; i < matrixTransposta.linha; i++){
        for(int j = 0; j < matrixTransposta.coluna; j++){
            matrixTransposta.matriz[i][j] = matrix.matriz[j][i];
        }
    }
    return matrixTransposta;
}

Matrix criaIdentidadeMatrix(int n){
    Matrix matrix;
    matrix.linha = n;
    matrix.coluna = n;

    matrix.matriz = malloc(n * sizeof(double*));
    if(matrix.matriz == NULL){
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for(int i = 0; i < n; i++){
        matrix.matriz[i] = malloc(n * sizeof(double));
        if(matrix.matriz[i] == NULL){
            printf("Falha na alocação de memória.\n");
            exit(1);
        }
        for(int j = 0; j < n; j++){
            if(i == j){
                matrix.matriz[i][j] = 1;
            } else {
                matrix.matriz[i][j] = 0;
            }
        }
    }
    return matrix;
}

Matrix inversaMatrix(Matrix matrix){
    if(matrix.linha != matrix.coluna){
        printf("Erro: A matriz deve ser quadrada para calcular a inversa.\n");
        exit(1);
    }

    int n = matrix.linha;
    Matrix matrixInversa = criaIdentidadeMatrix(n);

    // Cria uma cópia da matriz original
    Matrix matrixCopia = newMatrix(n, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrixCopia.matriz[i][j] = matrix.matriz[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        if(matrixCopia.matriz[i][i] == 0){
            int pivotFound = 0;
            for(int j = i + 1; j < n; j++){
                if(matrixCopia.matriz[j][i] != 0){
                    // Troca os elementos das linhas i e j
                    for(int k = 0; k < n; k++){
                        double temp = matrixCopia.matriz[i][k];
                        matrixCopia.matriz[i][k] = matrixCopia.matriz[j][k];
                        matrixCopia.matriz[j][k] = temp;

                        temp = matrixInversa.matriz[i][k];
                        matrixInversa.matriz[i][k] = matrixInversa.matriz[j][k];
                        matrixInversa.matriz[j][k] = temp;
                    }

                    pivotFound = 1;
                    break;
                }
            }
            if(!pivotFound){
                printf("Erro: A matriz é singular e não tem inversa.\n");
                // Retorna uma matriz nula
                for(int a = 0; a < n; a++){
                    for(int b = 0; b < n; b++){
                        matrixInversa.matriz[a][b] = 0;
                    }
                }
                return matrixInversa;
            }
        }

        double diagonal = matrixCopia.matriz[i][i];
        for(int j = 0; j < n; j++){
            matrixCopia.matriz[i][j] /= diagonal;
            matrixInversa.matriz[i][j] /= diagonal;
        }

        for(int j = 0; j < n; j++){
            if(i != j){
                double ratio = matrixCopia.matriz[j][i];

                for(int k = 0; k < n; k++){
                    matrixCopia.matriz[j][k] -= ratio * matrixCopia.matriz[i][k];
                    matrixInversa.matriz[j][k] -= ratio * matrixInversa.matriz[i][k];
                }
            }
        }
    }

    return matrixInversa;
}

double detMatrix(Matrix matrix){
    if(matrix.linha != matrix.coluna){
        printf("Erro: A matriz deve ser quadrada para calcular o determinante.\n");
        exit(1);
    }

    int n = matrix.linha;
    double det = 0.0;

    if(n == 1){
        return matrix.matriz[0][0];
    } else if(n == 2){
        return matrix.matriz[0][0] * matrix.matriz[1][1] - matrix.matriz[0][1] * matrix.matriz[1][0];
    } else if(n == 3){
        return matrix.matriz[0][0] * matrix.matriz[1][1] * matrix.matriz[2][2] +
               matrix.matriz[0][1] * matrix.matriz[1][2] * matrix.matriz[2][0] +
               matrix.matriz[0][2] * matrix.matriz[1][0] * matrix.matriz[2][1] -
               matrix.matriz[0][2] * matrix.matriz[1][1] * matrix.matriz[2][0] -
               matrix.matriz[0][1] * matrix.matriz[1][0] * matrix.matriz[2][2] -
               matrix.matriz[0][0] * matrix.matriz[1][2] * matrix.matriz[2][1];
    } else {
        for(int p = 0; p < n; p++){
            Matrix subMatrix;
            subMatrix.linha = n - 1;
            subMatrix.coluna = n - 1;
            subMatrix.matriz = (double**) malloc((n - 1) * sizeof(double*));
            for(int i = 0; i < n - 1; i++){
                subMatrix.matriz[i] = (double*) malloc((n - 1) * sizeof(double));
            }

            for(int i = 1; i < n; i++){
                int j1 = 0;
                for(int j = 0; j < n; j++){
                    if(j == p){
                        continue;
                    }
                    subMatrix.matriz[i - 1][j1] = matrix.matriz[i][j];
                    j1++;
                }
            }

            double subDet = detMatrix(subMatrix);
            if(subDet != 0){
                det += pow(-1, p) * matrix.matriz[0][p] * subDet;
            }
            freeMatrix(&subMatrix,NULL);
        }
    }

    return det;
}

void apagaMatrix(Matrix matrix) {
    if (matrix.matriz != NULL) {
        // Libere a memória alocada para cada linha
        for (int i = 0; i < matrix.linha; i++) {
            if (matrix.matriz[i] != NULL) {
                free(matrix.matriz[i]);
                matrix.matriz[i] = NULL; // Defina como NULL após liberar
            }
        }
        // Libere a memória alocada para o array de ponteiros
        free(matrix.matriz);
        matrix.matriz = NULL; // Defina como NULL após liberar
    }
}

void freeMatrix(Matrix *matrix, ...){
    va_list args;
    va_start(args, matrix);
    Matrix *currentMatrix = matrix;
    while(currentMatrix != NULL){
        if (matrix->matriz != NULL) {
            for (int i = 0; i < matrix->linha; i++) {
                if (matrix->matriz[i] != NULL) {
                    free(matrix->matriz[i]);
                    matrix->matriz[i] = NULL; 
                }
            }
            
            free(matrix->matriz);
            matrix->matriz = NULL; 
        }
        currentMatrix = va_arg(args, Matrix*);
    }
    va_end(args);
}