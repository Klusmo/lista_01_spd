#include <iostream>
#include <chrono>

using namespace std;

const int MATRIX_SIZE = 5;


void fillMatrixRandom(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]){
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            matrix[i][j] = rand() % 10;
}


void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]){
    for (int i = 0; i < MATRIX_SIZE; i++){
        for (int j = 0; j < MATRIX_SIZE; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}


int main(int argc, char *argv[]){
    int a[MATRIX_SIZE][MATRIX_SIZE], b[MATRIX_SIZE][MATRIX_SIZE], c[MATRIX_SIZE][MATRIX_SIZE];
    auto t1 = chrono::high_resolution_clock::now();
    fillMatrixRandom(a);
    fillMatrixRandom(b);
    #pragma omp parallel num_threads(2)
    {
        #pragma omp for
        for (int i = 0; i < MATRIX_SIZE; i++){
            for (int j = 0; j < MATRIX_SIZE; j++){
                int sum = 0;
                
                for (int k = 0; k < MATRIX_SIZE; k++)
                    sum += a[i][k] * b[k][j];
                
                c[i][j] = sum;
            }
        }
    }
    
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
    
    printMatrix(a);
    printMatrix(b);
    printMatrix(c);
}