#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
const int NUM_THREADS = 4;

using namespace std;

long double calculatePartialSum(long long start, long long end, long double step){
    long double sum = 0.0;
    for (long long i = start; i < end; i++){
        long double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    return sum;
}

int main(){
    long long num_steps = 9999999;
    long double step = 1.0 / num_steps;
    long double pi = 0.0;
    
    cout << "Calculando o valor de PI para " << num_steps << " passos com " << NUM_THREADS << " threads..." << endl;
    
    auto t1 = chrono::high_resolution_clock::now();
    
    vector<thread> threads;
    vector<long double> partial_sums(NUM_THREADS, 0.0);
    
    for (int i = 0; i < NUM_THREADS; i++){
        long long start = (i * num_steps) / NUM_THREADS;
        long long end = ((i + 1) * num_steps) / NUM_THREADS;
        threads.emplace_back([start, end, step, &partial_sums, i]()
                             { partial_sums[i] = calculatePartialSum(start, end, step); });
    }
    for (auto &thread : threads)
        thread.join();
    
    for (int i = 0; i < NUM_THREADS; i++)
        pi += partial_sums[i];
    
    pi *= step;
    
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    
    cout << "Valor aproximado = " << setprecision(50) << pi << endl;
    cout << "Tempo de execução do algoritmo (ms) = " << duration << endl;
    
    return 0;
}