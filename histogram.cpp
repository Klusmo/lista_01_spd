#include <omp.h>
#include <iostream>
#include <vector>

#define WIDTH 3840
#define HEIGHT 2160
#define NUM_CLASSES 16
#define MAX_GRAY_LEVEL 256

void calculateHistogram(const std::vector<std::vector<int>>& image, std::vector<int>& histogram) {
    // Inicialize o histograma com zeros
    std::fill(histogram.begin(), histogram.end(), 0);

    // Paralelize o cálculo do histograma
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int grayLevel = image[i][j];
            int classIndex = grayLevel / (MAX_GRAY_LEVEL / NUM_CLASSES);

            #pragma omp atomic
            histogram[classIndex]++;
        }
    }
}

int main() {
    // Exemplo de uma imagem em escala de cinza com resolução 4K (3840 x 2160)
    std::vector<std::vector<int>> image(HEIGHT, std::vector<int>(WIDTH));

    // Preenchendo a imagem com valores de níveis de cinza aleatórios para demonstração
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            image[i][j] = rand() % MAX_GRAY_LEVEL;
        }
    }

    // Inicialize o histograma com o número de classes
    std::vector<int> histogram(NUM_CLASSES);

    // Calcule o histograma usando OpenMP
    calculateHistogram(image, histogram);

    // Exibir o histograma
    for (int i = 0; i < NUM_CLASSES; ++i) {
        std::cout << "Class " << i << ": " << histogram[i] << std::endl;
    }

    return 0;
}
