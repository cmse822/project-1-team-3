/*

Started 1/15/2024: Mackenzie Scott, Create inital matricies 


Compile with: g++ -o Part1.exe Part1.cpp 
Execute with: ./Part1.exe

*/

#include <iostream>

using namespace std;

const int N = 10;  //Size of the Matricies

void populate_matrix(double matrix[][N], int Num);

int main(){

    //cout << "Hello" << endl;

    double matrix_A[N][N];
    double matrix_B[N][N];
    double matrix_C[N][N];

    populate_matrix(matrix_A, N);
    populate_matrix(matrix_B, N);

    return 0;
}

void populate_matrix(double matrix[][N], int Num ) {
    for(int i = 0; i < Num; ++i){
        for(int j = 0; j < Num; ++j){
            matrix[i][j] = i*j;
        }
    }
    //cout << "element at index 1,1 is " << matrix[3][3] << endl;
}


