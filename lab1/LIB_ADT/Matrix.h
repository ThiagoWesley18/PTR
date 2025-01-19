#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix Matrix;
struct matrix{
    int linha;
    int coluna;
    double **matriz;
};

Matrix newMatrix(int linha, int coluna);
Matrix sumMatrix(Matrix matrix1, Matrix matrix2);
Matrix subMatrix(Matrix matrix1, Matrix matrix2);
Matrix multMatrix(Matrix matrix1, Matrix matrix2);
Matrix scalarMultMatrix(Matrix matrix, double scalar);
Matrix scalarSomaMatrix(Matrix matrix, double scalar);
Matrix scalarSubMatrix(Matrix matrix, double scalar);
Matrix transpostaMatrix(Matrix matrix);
Matrix inversaMatrix(Matrix matrix);
double detMatrix(Matrix matrix);
void freeMatrix(Matrix matrix, ...);

#endif
