#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <time.h>

void mat_display(matrix *a);
void example_matrix_transpose();
void example_matrix_mult();

int main()
{
    example_matrix_transpose();
    // example_matrix_mult();

    return 0;
}

void example_matrix_transpose()
{
    clock_t start, end;
    double cpu_elapse_time;
    srand(time(0));

    while (1)
    {
        int N, M;
        printf("\nEnter N:\n");
        scanf("%d", &N);

        printf("\nEnter M:\n");
        scanf("%d", &M);

        if (N < 2 || M < 2)
            break;
        matrix *a = make_dense(N, M);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                mat_set(a, rand() % 10 + 1, i, j);
            }
        }
        if (N <= 20 && M <= 20)
            mat_display(a); // Original matrix

        start = clock();
        mat_trans(a);
        end = clock();
        cpu_elapse_time = ((double)(end - start));

        if (N <= 20 && M <= 20)
            mat_display(a); // Transposed matrix

        printf("Elapse time: %f (ms)\n", cpu_elapse_time);
    }
}

void example_matrix_mult()
{
    clock_t start, end;
    double cpu_elapse_time;
    srand(time(0));

    while (1)
    {
        int N, M;
        printf("\nEnter N:\n");
        scanf("%d", &N);

        printf("\nEnter M:\n");
        scanf("%d", &M);
        if (M < 2 || N < 2)
            break;

        matrix *a = make_dense(N, M);
        matrix *b = make_dense(M, N);
        matrix *c = make_dense(N, N);

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                mat_set(a, rand() % 10 + 1, i, j);
            }
        }

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                mat_set(b, rand() % 10 + 1, i, j);
            }
        }

        if (N <= 20 && M <= 20)
        {
            mat_display(a);
            mat_display(b);
        }

        start = clock();
        mat_mult(a, b, c);
        end = clock();
        cpu_elapse_time = ((double)(end - start));

        if (N <= 20 && M <= 20)
            mat_display(c);

        printf("Elapse time: %f (ms)\n", cpu_elapse_time);
    }
}

void mat_display(matrix *a)
{
    printf("\n");
    for (int i = 0; i < a->row_size; i++)
    {
        printf("\n");
        for (int j = 0; j < a->col_size; j++)
        {
            printf("%.1f    ", a->ele[INDEX(a->col_size, i, j)]);
        }
    }
    printf("\n\n");
}