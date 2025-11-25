#include <vector>
using namespace std;
#include "matrix_utilities.h"

vector<vector<double>> strassenMatrixMultiplication(const vector<vector<double>>& A, const vector<vector<double>>& B, int size) {
    // Do not remove! for autograd

    vector<vector<double>> C(size, vector<double>(size));
    // Todo: Add Strassen's algorithm codes
    if (size == 1)
    {
        return {{A[0][0] * B[0][0]}};
    }

    // create submatrices
    int newSize = size / 2;
    vector<vector<double>> A11(newSize, vector<double>(newSize)),
    A12(newSize, vector<double>(newSize));
    vector<vector<double>> A21(newSize, vector<double>(newSize)),
    A22(newSize, vector<double>(newSize));
    vector<vector<double>> B11(newSize, vector<double>(newSize)),
    B12(newSize, vector<double>(newSize));
    vector<vector<double>> B21(newSize, vector<double>(newSize)),
    B22(newSize, vector<double>(newSize));
    vector<vector<double>> P1(newSize, vector<double>(newSize)),
    P2(newSize, vector<double>(newSize));
    vector<vector<double>> P3(newSize, vector<double>(newSize)),
    P4(newSize, vector<double>(newSize));
    vector<vector<double>> P5(newSize, vector<double>(newSize)),
    P6(newSize, vector<double>(newSize));
    vector<vector<double>> P7(newSize, vector<double>(newSize));
    

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
    P1 = strassenMatrixMultiplication(A11, subtractMatrix(B12, B22, newSize), newSize);
    P2 = strassenMatrixMultiplication(addMatrix(A11, A12, newSize), B22, newSize);
    P3 = strassenMatrixMultiplication(addMatrix(A21, A22, newSize), B11, newSize);
    P4 = strassenMatrixMultiplication(A22, subtractMatrix(B21, B11, newSize), newSize);
    P5 = strassenMatrixMultiplication(addMatrix(A11, A22, newSize), addMatrix(B11, B22, newSize), newSize);
    P6 = strassenMatrixMultiplication(subtractMatrix(A12, A22, newSize), addMatrix(B21, B22, newSize), newSize);
    P7 = strassenMatrixMultiplication(subtractMatrix(A11, A21, newSize), addMatrix(B11, B12, newSize), newSize);
    
    // Combine results
    for (int i = 0; i < newSize; ++i)
    {
        for (int j = 0; j < newSize; ++j)
        {
            C[i][j] = P4[i][j] + P5[i][j] + P6[i][j] - P2[i][j];
            C[i][j + newSize] = P1[i][j] + P2[i][j];
            C[i + newSize][j] = P3[i][j] + P4[i][j];
            C[i + newSize][j + newSize] = P1[i][j] + P5[i][j] - P3[i][j] - P7[i][j];
        }
    }

    return C;
}
