#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;

int main(){
    long long num_steps = 999999;
    long double step = 1.0 / num_steps;
    long double pi = 0.0;
    cout << "Calculando o valor de PI para " << num_steps << " passos usando OpenMP... " << endl;
    
    auto t1 = chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        long double sum = 0.0;
        #pragma omp for
        for (long long i = 0; i < num_steps; i++){
            long double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp critical
        {
            pi += sum;
        }
    }
    
    pi *= step;
    
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    
    cout << "Valor aproximado = " << setprecision(50) << pi << endl;
    cout << "Tempo de execução do algoritmo (ms) = " << duration << endl;
    
    return 0;
}
