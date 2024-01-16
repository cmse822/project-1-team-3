#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include "get_walltime.h"


typedef std::vector<std::vector<double> > Matrix;

// Function to generate a random N x N matrix
Matrix generateRandomMatrix(int N) {
    Matrix matrix(N, std::vector<double>(N));
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = dis(gen); // Generate random double between 0.0 and 1.0
        }
    }

    return matrix;
}


Matrix multiplyMatrices(const Matrix& A, const Matrix& B, int &flops) {
    int rowsA = A.size();
    int colsA = A[0].size();
    // int rowsB = B.size();
    int colsB = B[0].size();

    int flopCount = 0;

    Matrix result(rowsA, std::vector<double>(colsB, 0.0));

    // colsA must equal rowsB
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
                flopCount += 2;
            }
        }
    }

    std::cout << "FLOP count: " << flopCount << std::endl;

    flops = flopCount;

    return result;
}

// Function to print the matrix
void printMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <MatrixSize>" << std::endl;
        return 1;
    }

    int N = std::atoi(argv[1]);
    if (N <= 0) {
        std::cerr << "Matrix size must be a positive integer." << std::endl;
        return 1;
    }

    Matrix matrixA = generateRandomMatrix(N);

    Matrix matrixB = generateRandomMatrix(N);

    std::cout << "Randomly generated " << N << "x" << N << " matrix:" << std::endl;
    // printMatrix(matrixA);

    std::cout << "Randomly generated " << N << "x" << N << " matrix:" << std::endl;
    // printMatrix(matrixB);

    double *timeCount = new double;

    get_walltime(timeCount);

    const double startTime = *timeCount;

    int flops = 0;

    Matrix product = multiplyMatrices(matrixA, matrixB, flops);
    // std::cout << "Product of A and B:" << std::endl;
    // printMatrix(product);

    get_walltime(timeCount);

    const double endTime = *timeCount;

    std::cout << "Time elapsed: " << endTime - startTime << " seconds." << std::endl;

    std::cout << "Mflops/s: " << (flops / (endTime - startTime)) / 1000000 << std::endl;

    delete timeCount;

    return 0;
}
