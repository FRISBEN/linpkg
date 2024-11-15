#include "matrix.h"

void set_mem(matrix *, __uint, __uint);

int mat_set(matrix *a, float value, __uint i, __uint j)
{
    if (a == NULL || a->ele == NULL)
    {
        return NULL_CODE;
    }
    unsigned int index = INDEX(a->col_size, i, j);
    a->ele[index] = value;
    return 1;
}

int mat_add(matrix *a, matrix *b, matrix *add)
{
    ERROR_CHECH(a, b, add);
    __uint length = a->col_size * a->row_size;
    // #pragma omp parallel for
    for (__uint i = 0; i < length; i += 4)
    {
        // Using SIMD
        __m128 vec_a = _mm_load_ps(&a->ele[i]);
        __m128 vec_b = _mm_load_ps(&b->ele[i]);

        // Perform SIMD addition
        __m128 sum_vec = _mm_add_ps(vec_a, vec_b);

        // Update the original array
        _mm_storeu_ps(&add->ele[i], sum_vec);
        // add->ele[i] = a->ele[i] + b->ele[i];
    }
    return 1;
}

int mat_sub(matrix *a, matrix *b, matrix *sub)
{
    ERROR_CHECH(a, b, sub);
    __uint length = a->col_size * a->row_size;
    for (__uint i = 0; i < length; i++)
    {
        sub->ele[i] = a->ele[i] - b->ele[i];
    }
    return 1;
}

int mat_mult(matrix *a, matrix *b, matrix *mult)
{
    if (a->col_size != b->row_size)
        return NULL_CODE;
    if (mult == NULL || mult->ele == NULL)
        return NULL_CODE;

    register double sum;
    register __uint i, j, k, ij, ik, kj;

    // #pragma omp parallel for
    for (i = 0; i < b->col_size; i++)
    {
        for (k = 0; k < a->row_size; k++)
        {
            sum = 0;
            ij = INDEX(a->row_size, i, j);
            for (j = 0; j < a->col_size; j += 4)
            {
                ik = INDEX(a->col_size, i, k);
                kj = INDEX(b->col_size, k, j);
                sum += a->ele[ik] * b->ele[kj];
            }
            mult->ele[ij] = sum;
        }
    }
    return 0;
}

int mat_trans(matrix *a)
{
    register __uint i, j, ij, ji;
    if (a->col_size == a->row_size)
    {
        register double temp = 0;
        for (i = 0; i < a->row_size; i++)
        {
            for (j = i; j < a->col_size; j++)
            {
                ij = INDEX(a->col_size, i, j);
                ji = INDEX(a->col_size, j, i);
                temp = a->ele[ij];
                a->ele[ij] = a->ele[ji];
                a->ele[ji] = temp;
            }
        }
    }
    else
    {
        double *ele = malloc(a->row_size * a->col_size * sizeof(double));
        if (ele == NULL)
        {
            return -1;
        }

        for (j = 0; j < a->col_size; j++)
        {
            for (i = 0; i < a->row_size; i++)
            {
                ij = INDEX(a->col_size, i, j);
                ji = INDEX(a->row_size, j, i);
                ele[ji] = a->ele[ij];
            }
        }
        free(a->ele);
        a->ele = ele;
        // Reset row_size and col_size if 'a' is not a square matrix.
        __uint col_size = a->row_size;
        a->row_size = a->col_size;
        a->col_size = col_size;
    }
    return 0;
}

int mat_smult(matrix a, double scalar)
{
    return 0;
}

matrix *make_dense(__uint row_size, __uint col_size)
{
    matrix *m = (matrix *)malloc(sizeof(matrix));
    if (m == NULL)
    {
        return NULL;
    }
    set_mem(m, row_size, col_size);
    return m;
}

void set_mem(matrix *m, __uint row_size, __uint col_size)
{
    m->row_size = row_size;
    m->col_size = col_size;
    double *ele = malloc(row_size * col_size * sizeof(double));
    if (ele != NULL)
    {
        m->ele = ele;
    }
}

void destroy_matrix(matrix *m)
{
    if (m != NULL)
    {
        if (m->ele != NULL)
        {
            free(m->ele);
        }
        free(m);
    }
}
