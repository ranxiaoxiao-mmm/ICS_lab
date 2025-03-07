#include <stdio.h>
#include "cachelab.h"

static inline int kernel(int *w)
{
    // we set alpha to 1 and delta_t to 1.
    // equals to w[0] + alpha * (w[-1] - 2 * w[0] + w[1]);
    // example usage: A[t + 1][x] = kernel(&A[t][x]);
    return (w[-1] - w[0] + w[1]);
}

char heat_sim_desc[] = "Heat Simulate submission";
void heat_sim_example(int T, int N, int A[T][N])
{
    for (int t = 0; t < T - 1; t++)
        for (int x = 1; x < N - 1; x++)
            A[t + 1][x] = kernel(&A[t][x]);
}

void heat_sim(int T, int N, int A[T][N])
{
    int tran[N];
    for(int j = 1; j < N-1; j++){
        tran[j] = A[0][j];
    }
    for(int t = 0;t < T; t++){
        A[t][1] = tran[1];
        for(int i = 1; i < N-1; i++){
            A[t][i+1] = tran[i+1];
            tran[i] = kernel(&A[t][i]);
        }
    }
}
    // TODO: implement your own algorithm
    // heat_sim_example(T, N, A);

void registerHeatFunctions()
{
    // registerHeatFunction(heat_sim_example, heat_sim_desc);
    registerHeatFunction(heat_sim, heat_sim_desc);
}