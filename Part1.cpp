/*

Started 1/15/2024: Mackenzie Scott, Create inital matrices
Modified 1/15/2024: Sunia Tanweer, Added code for multiplication of matrices


Compile with: g++ -o Part1.exe Part1.cpp 
Execute with: ./Part1.exe

*/

#include <iostream>
#include "get_walltime.c"

using namespace std;

const int N = 100;  //Size of the Matricies
double sum; //Placeholder for dot product of A[i][] with B[][j]
double startTime, endTime, elapsedTime;  //Used for timing the matrix calculation

void populate_matrix(double matrix[][N], int Num); //For randomly populating the matrices

int main(){
    
    //Ask about static???
    static double matrix_A[N][N];
    static double matrix_B[N][N];
    static double matrix_C[N][N];

    populate_matrix(matrix_A, N);
    populate_matrix(matrix_B, N);

    get_walltime(&startTime);

    // Multiplying matrix_A and matrix_B to get matrix_C
	for(int i = 0; i < N; ++i)
		{
            for(int j = 0;  j < N; ++j)
			{
				for(int m = 0; m < N; ++m)
				{
					sum = sum + matrix_A[i][m]*matrix_B[m][j];
				}
				matrix_C[i][j] = sum;
				sum = 0;
			}
		}
    get_walltime(&endTime);
    elapsedTime = endTime - startTime;
    cout << "elapsedTime: " << elapsedTime << " seconds." << endl;

    return 0;
}

void populate_matrix(double matrix[][N], int Num){
    for(int i = 0; i < Num; ++i){
        for(int j = 0; j < Num; ++j){
            matrix[i][j] = rand()%10; //Assigning random number between 0-9
        }
    }
}


