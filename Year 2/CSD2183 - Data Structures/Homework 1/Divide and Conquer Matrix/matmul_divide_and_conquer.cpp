#include "matmul_divide_and_conquer.h"

// Naive matrix multiplication
vector<vector<double>> divideAndConquerMultiply(const vector<vector<double>>& A, const vector<vector<double>>& B, int n) {
    // Do not remove! for autograd

    vector<vector<double>> C(n, vector<double>(n));

    // ---- Add your codes here ---
    // recursion termination condition
    if (n == 1)
    {
        return {{A[0][0] * B[0][0]}};
    }

    // create submatrices
    int newSize = n / 2;
    vector<vector<double>> A11(newSize, vector<double>(newSize)),
    A12(newSize, vector<double>(newSize));
    vector<vector<double>> A21(newSize, vector<double>(newSize)),
    A22(newSize, vector<double>(newSize));
    vector<vector<double>> B11(newSize, vector<double>(newSize)),
    B12(newSize, vector<double>(newSize));
    vector<vector<double>> B21(newSize, vector<double>(newSize)),
    B22(newSize, vector<double>(newSize));
    vector<vector<double>> C11(newSize, vector<double>(newSize)),
    C12(newSize, vector<double>(newSize));
    vector<vector<double>> C21(newSize, vector<double>(newSize)),
    C22(newSize, vector<double>(newSize));

    // Divide matrices into 4 submatrices
    for (int i = 0; i < newSize; ++i)
    {
        for (int j = 0; j < newSize; ++j)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    
    // Recursive calls
    C11 = addMatrix(divideAndConquerMultiply(A11, B11, newSize), 
    divideAndConquerMultiply(A12, B21, newSize), newSize);
    C12 = addMatrix(divideAndConquerMultiply(A11, B12, newSize), 
    divideAndConquerMultiply(A12, B22, newSize), newSize);
    C21 = addMatrix(divideAndConquerMultiply(A21, B11, newSize), 
    divideAndConquerMultiply(A22, B21, newSize), newSize);
    C22 = addMatrix(divideAndConquerMultiply(A21, B12, newSize), 
    divideAndConquerMultiply(A22, B22, newSize), newSize);

    // Combine results
    for (int i = 0; i < newSize; ++i)
    {
        for (int j = 0; j < newSize; ++j)
        {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
 
    return C;
}

