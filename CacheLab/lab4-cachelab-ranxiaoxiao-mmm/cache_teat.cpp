#include<iostream>
using namespace std;
int main(){
    int t[12] = {1};
    int A[48][48] = {1};
    int B[48][48] = {2};
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