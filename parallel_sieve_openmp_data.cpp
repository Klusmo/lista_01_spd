#include <omp.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

#define LIMIT 1000000000

using namespace std;

int main() {
    std::vector<bool> isPrime(LIMIT + 1, true);
    isPrime[0] = isPrime[1] = false;

    
    for(int numThreads = 2; numThreads <= 6; numThreads++){
        omp_set_num_threads(numThreads);
        
        auto start = chrono::high_resolution_clock::now();

        int sqrtLimit = static_cast<int>(std::sqrt(LIMIT));

        #pragma omp parallel for schedule(dynamic)
        for (int i = 2; i <= sqrtLimit; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= LIMIT; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Number of Threads: " << numThreads << " | Elapsed time: " << elapsed.count() << " seconds\n";
        // Print prime numbers (optional)
        // for (int i = 2; i <= LIMIT; i++) {
        //     if (isPrime[i]) {
        //         std::cout << i << " ";
        //     }
        // }
    }

    return 0;
}
