#ifndef __MATRIX_UTILITIES_H__
#define __MATRIX_UTILITIES_H__

#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <numeric> // for std::accumulate
using namespace std;

// Function to print a matrix
void printMatrix(const vector<vector<double>>& mat);

// Function to read a matrix from a file
void readMatrix(std::ifstream &file, std::vector<std::vector<double>> &matrix, int n);

// Function to read a matrix from a file
bool isEqualMatrix(const vector<vector<double>>& A, const vector<vector<double>>& B, int n);

// Function to add two matrices
vector<vector<double>> addMatrix(const vector<vector<double>>& A, const vector<vector<double>>& B, int n);

// Function to subtract two matrices
vector<vector<double>> subtractMatrix(const vector<vector<double>>& A, const vector<vector<double>>& B, int n);

// Function to randomize a matrix, please initialize matrix with enough space first.
void randomizeMatrix(vector<vector<double>>& matrix, int n, double minVal, double maxVal);

#endif//__MATRIX_UTILITIES_H__

