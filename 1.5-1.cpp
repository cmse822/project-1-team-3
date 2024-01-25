#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>
#include "get_walltime.c" // Include the get_walltime function

using namespace std;
using namespace chrono;

// multiply two matrices
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int row_A = A.size();
    int col_A = A[0].size();
    int row_B = B.size();
    int col_B = B[0].size();

    // Check
    if (col_A != row_B) {
        throw invalid_argument("Matrix multiplication failed.");
    }

    vector<vector<double>> C(row_A, vector<double>(col_B, 0.0));

    // matrix multiplication
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
    const int maxN = 10000000; 
    const int step = 10000;    
    const int numRepeats = 10; 

    // Create a file
    ofstream resultsFile("performance_results.txt", ios::app);

    int N = 1;
    while (N <= maxN) {
        double totalTime = 0.0;
        vector<vector<double>> A(N, vector<double>(N, 1.0));
        vector<vector<double>> B(N, vector<double>(N, 2.0));

        for (int repeat = 0; repeat < numRepeats; repeat++) {
            double start_time, end_time;

        
            get_walltime(&start_time);
            vector<vector<double>> result = multiplyMatrices(A, B);
            get_walltime(&end_time);
            double elapsed_time = end_time - start_time;
            totalTime += elapsed_time;
        }

        
        double averageTime = totalTime / numRepeats;
        double totalFlops = 2.0 * pow(N, 3) * numRepeats; 
        double performance = (totalFlops / 1e9) / averageTime; //G

        // Store results in the file
        resultsFile << N << " " << performance << endl;

        N += step;
    }


    resultsFile.close();

    return 0;
}