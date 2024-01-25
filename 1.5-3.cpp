#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "get_walltime.c" // Include the get_walltime.c file

using namespace std;

// Function to multiply two matrices
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (cols1 != rows2) {
        cout << "Matrix multiplication does not work." << endl;
        return vector<vector<double>>();
    }

    vector<vector<double>> result(rows1, vector<double>(cols2, 0.0));

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Function to measure performance
double measurePerformance(int N) {
    vector<vector<double>> matrix1(N, vector<double>(N));
    vector<vector<double>> matrix2(N, vector<double>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix1[i][j] = static_cast<double>(rand()) / RAND_MAX;
            matrix2[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    double start_time, end_time;
    get_walltime(&start_time); // Start timing

    // Replace the following line with your matrix multiplication code
    vector<vector<double>> result = multiplyMatrices(matrix1, matrix2);

    get_walltime(&end_time); // End timing

    double execution_time = end_time - start_time;
    double total_flops = 2.0 * pow(N, 3); // 2N^3 FLOPs for matrix multiplication
    double gflops = total_flops / execution_time / 1e9; // Convert to GFLOP/s

    return gflops;
}

int main() {
    double system_clock_speed = 2595.009; //actual clock speed by typing lscpu, CPU MHz

    vector<int> matrix_sizes;
    for (int N = 1; N <= 10000000; N *= 10) {
        matrix_sizes.push_back(N);
    }

    // Measure performance
    ofstream outFile("performance_data.csv");
    outFile << "Matrix Size (N),Measured GFLOP/s,Theoretical Peak GFLOP/s" << endl;

    for (int N : matrix_sizes) {
        double measured_gflops = measurePerformance(N);
        double theoretical_peak_gflops = system_clock_speed * N / 1e9; // GFLOP/s

        outFile << N << "," << measured_gflops << "," << theoretical_peak_gflops << endl;
        cout << "N = " << N << ": Measured GFLOP/s = " << measured_gflops << ", Theoretical Peak GFLOP/s = " << theoretical_peak_gflops << endl;
    }

    outFile.close();

    cout << "Performance data has been saved to performance_data.csv." << endl;

    return 0;
}