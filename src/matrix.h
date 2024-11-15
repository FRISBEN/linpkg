#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <omp.h>
#include <xmmintrin.h>

#define NULL_CODE -1
#define INDEX(col_size, i, j) col_size *i + j

#define ERROR_CHECH(matrix_a, matrix_b, result)                                               \
    if (matrix_a->col_size != matrix_b->col_size || matrix_a->row_size != matrix_b->row_size) \
        return NULL_CODE;                                                                     \
    if (result == NULL || result->ele == NULL)                                                \
        return NULL_CODE;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef unsigned int __uint;
typedef struct matrix_dense
{
    double *ele;
    __uint row_size;
    __uint col_size;
} matrix;

int mat_set(matrix *a, float value, __uint i, __uint j);
matrix *make_dense(__uint row_size, __uint col_size);
void destroy_matrix(matrix *m);
int mat_add(matrix *a, matrix *b, matrix *add);
int mat_sub(matrix *a, matrix *b, matrix *sub);
int mat_mult(matrix *a, matrix *b, matrix *mult);
int mat_trans(matrix *a);
// int mat_smult(matrix a, double scalar);
#endif