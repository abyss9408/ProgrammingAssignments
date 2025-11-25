#include "matrix_utilities.h"

#include <iomanip>
#include <cmath>
#include <cassert>

// Function to print a matrix
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto &row : matrix) {
        for (const auto &elem : row) {
            std::cout << std::setw(10) << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Function to read a matrix from a file
void readMatrix(std::ifstream &file, std::vector<std::vector<double>> &matrix, int n) {
    matrix.resize(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matrix[i][j];
        }
    }
}

// Function to add two matrices
vector<vector<double>> addMatrix(const vector<vector<double>>& A, const vector<vector<double>>& B, int n) {
    vector<vector<double>> result(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

// Function to subtract two matrices
vector<vector<double>> subtractMatrix(const vector<vector<double>>& A, const vector<vector<double>>& B, int n) {
    vector<vector<double>> result(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}

// Function to subtract two matrices
bool isEqualMatrix(const vector<vector<double>>& A, const vector<vector<double>>& B, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (fabs(A[i][j] - B[i][j])>1e-8) // quick fix to mitigate small variations in double type.
                return false;
    return true;
}

// Function to randomize a matrix, please initialize matrix with enough space first.
void randomizeMatrix(vector<vector<double>>& matrix, int n, double minVal, double maxVal) {
    // Initialize random number generator
    random_device rd; // Seed
    mt19937 gen(rd()); // Random number generator
    uniform_real_distribution<> dis(minVal, maxVal); // Distribution range

    // Fill the matrix with random values
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
}
