/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int t[12] = {0};
    if(M == 48){
        for(int i = 0; i < 48; i += 12){
            for(int j = 0; j < 48; j += 12){
                for(int k = i; k < i + 12; k++){
                    t[0] = A[k][j];
                    t[1] = A[k][j + 1];
                    t[2] = A[k][j + 2];
                    t[3] = A[k][j + 3];
                    t[4] = A[k][j + 4];
                    t[5] = A[k][j + 5];
                    t[6] = A[k][j + 6];
                    t[7] = A[k][j + 7];
                    t[8] = A[k][j + 8];
                    t[9] = A[k][j + 9];
                    t[10] = A[k][j + 10];
                    t[11] = A[k][j + 11];
                    B[j][k] = t[0];
                    B[j + 1][k] = t[1];
                    B[j + 2][k] = t[2];
                    B[j + 3][k] = t[3];
                    B[j + 4][k] = t[4];
                    B[j + 5][k] = t[5];
                    B[j + 6][k] = t[6];
                    B[j + 7][k] = t[7];
                    B[j + 8][k] = t[8];
                    B[j + 9][k] = t[9];
                    B[j + 10][k] = t[10];
                    B[j + 11][k] = t[11];
                }
            }
        }
    }
    if(M == 96){
        for (int i = 0; i < 96; i += 12) {
            for (int j = 0; j < 96; j += 12) {  
                for (int k = 0; k < 6; i++, k++) {
                    t[0] = A[i][j];
                    t[1] = A[i][j+1];
                    t[2] = A[i][j+2];
                    t[3] = A[i][j+3];
                    t[4] = A[i][j+4];
                    t[5] = A[i][j+5];
                    t[6] = A[i][j+6];
                    t[7] = A[i][j+7];
                    t[8] = A[i][j+8];
                    t[9] = A[i][j+9];
                    t[10] = A[i][j+10];
                    t[11] = A[i][j+11];

                    B[j][i] = t[0];
                    B[j+1][i] = t[1];
                    B[j+2][i] = t[2];
                    B[j+3][i] = t[3];
                    B[j+4][i] = t[4];
                    B[j+5][i] = t[5];
                    B[j][i+6] = t[6];
                    B[j+1][i+6] = t[7];
                    B[j+2][i+6] = t[8];
                    B[j+3][i+6] = t[9];
                    B[j+4][i+6] = t[10];
                    B[j+5][i+6] = t[11];
                }
                
                i -= 6;

                for (int k = 0; k < 6; j++, k++) {
                    t[0] = A[i+6][j];
                    t[1] = A[i+7][j];
                    t[2] = A[i+8][j];
                    t[3] = A[i+9][j];
                    t[4] = A[i+10][j];
                    t[5] = A[i+11][j];
                    t[6] = B[j][i+6];
                    t[7] = B[j][i+7];
                    t[8] = B[j][i+8];
                    t[9] = B[j][i+9];
                    t[10] = B[j][i+10];
                    t[11] = B[j][i+11];

                    B[j][i+6] = t[0]; 
                    B[j][i+7] = t[1];
                    B[j][i+8] = t[2];
                    B[j][i+9] = t[3];
                    B[j][i+10] = t[4];
                    B[j][i+11] = t[5];
                    B[j+6][i] = t[6];
                    B[j+6][i+1] = t[7];
                    B[j+6][i+2] = t[8];
                    B[j+6][i+3] = t[9];
                    B[j+6][i+4] = t[10];
                    B[j+6][i+5] = t[11];
                }

                i += 6;

                for (int k = 0; k < 6; i++, k++) {
                    t[0] = A[i][j];
                    t[1] = A[i][j+1];
                    t[2] = A[i][j+2];
                    t[3] = A[i][j+3];
                    t[4] = A[i][j+4];
                    t[5] = A[i][j+5];

                    B[j][i] = t[0];
                    B[j+1][i] = t[1];
                    B[j+2][i] = t[2];
                    B[j+3][i] = t[3];
                    B[j+4][i] = t[4];
                    B[j+5][i] = t[5];
                }
                i -= 12;
                j -= 6;
            }
        }
    }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    // registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
