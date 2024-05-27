#include <omp.h>
#include <iostream>
#include <vector>

void parallelFibonacci(int n, std::vector<long long>& fib) {
    fib[0] = 0;
    fib[1] = 1;

    #pragma omp parallel for
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

int main() {
    int n = 50; // Número de termos da sequência de Fibonacci
    std::vector<long long> fib(n + 1);

    parallelFibonacci(n, fib);

    // Exibir os resultados
    for (int i = 0; i <= n; i++) {
        std::cout << "Fib(" << i << ") = " << fib[i] << std::endl;
    }

    return 0;
}
