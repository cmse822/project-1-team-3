#include <iostream>
#include <vector>
#include "get_walltime.c"
using namespace std;

int main() {
    int row_A, col_A, row_B, col_B;

    // Input dimensions of matrices A and B
    cout << "Enter the number of rows first, press enter, and then enter the number of columns for matrix A: ";
    cin >> row_A >> col_A;

    cout << "Enter the number of rows first, press enter, and then enter the number of columns for matrix B: ";
    cin >> row_B >> col_B;

    // Check
    if (col_A != row_B) {
        cout << "Matrix multiplication is not possible. Columns of A must be equal to rows of B." << endl;
        return 1;
    }

    vector<vector<int>> A(row_A, vector<int>(col_A));
    vector<vector<int>> B(row_B, vector<int>(col_B));
    vector<vector<int>> C(row_A, vector<int>(col_B));

    // matrix A
    cout << "Enter elements for matrix A:" << endl;
    for (int i = 0; i < row_A; i++) {
        for (int j = 0; j < col_A; j++) {
            cin >> A[i][j];
        }
    }

    // Input elements for matrix B
    cout << "Enter elements for matrix B:" << endl;
    for (int i = 0; i < row_B; i++) {
        for (int j = 0; j < col_B; j++) {
            cin >> B[i][j];
        }
    }

    // Perform matrix multiplication
    for (int i = 0; i < row_A; i++) {
        for (int j = 0; j < col_B; j++) {
            C[i][j] = 0;
            for (int k = 0; k < col_A; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Output the result matrix C
    cout << "Resultant matrix C:" << endl;
    for (int i = 0; i < row_A; i++) {
        for (int j = 0; j < col_B; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}