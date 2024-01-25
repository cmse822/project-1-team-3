#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>
#include "get_walltime.c" // Include the get_walltime function

using namespace std;
using namespace chrono;

// Function to multiply two matrices
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int row_A = A.size();
    int col_A = A[0].size();
    int row_B = B.size();
    int col_B = B[0].size();

    // Check if multiplication is possible
    if (col_A != row_B) {
        throw invalid_argument("Matrix multiplication is not possible. Columns of A must be equal to rows of B.");
    }

    // Initialize the result matrix C with zeros
    vector<vector<double>> C(row_A, vector<double>(col_B, 0.0));

    // Perform matrix multiplication
    for (int i = 0; i < row_A; i++) {
        for (int j = 0; j < col_B; j++) {
            for (int k = 0; k < col_A; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main() {
    const int maxN = 10000000; // Maximum matrix size
    const int step = 10000;    // Step size for matrix size

    // Create a file for storing measurement results in append mode
    ofstream resultsFile("performance_results.txt", ios::app);

    int N = 1;
    while (N <= maxN) {
        double totalTime = 0.0;
        vector<vector<double>> A(N, vector<double>(N, 1.0));
        vector<vector<double>> B(N, vector<double>(N, 2.0));

        double start_time, end_time;

        // Measure start time
        get_walltime(&start_time);

        // Multiply matrices A and B
        vector<vector<double>> result = multiplyMatrices(A, B);

        // Measure end time
        get_walltime(&end_time);

        // Calculate elapsed time
        double elapsed_time = end_time - start_time;
        totalTime += elapsed_time;

        // Calculate Gflop/s for the current matrix size
        double totalFlops = 2.0 * pow(N, 3); // Total FLOPs
        double performance = (totalFlops / 1e9) / totalTime; // Gflop/s

        // Store results in the file
        resultsFile << N << " " << performance << endl;

        // Increment N by the specified step size
        N += step;
    }

    // Close the results file
    resultsFile.close();

    return 0;
}