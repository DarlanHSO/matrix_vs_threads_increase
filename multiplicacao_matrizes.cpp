#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int num_threads) {
    int n = A.size();
    int m = A[0].size();
    int p = B[0].size();

    #pragma omp parallel for collapse(2) num_threads(num_threads)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < m; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int n = 500; // Tamanho da matriz
    vector<vector<int>> A(n, vector<int>(n, 1));
    vector<vector<int>> B(n, vector<int>(n, 1));
    vector<vector<int>> C(n, vector<int>(n, 0));

    vector<int> thread_counts = {1, 2, 4, 8, 16}; // Definindo o número de threads para testar

    for (int num_threads : thread_counts) {
        auto start = high_resolution_clock::now();
        
        multiplyMatrices(A, B, C, num_threads);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        
        cout << "Tempo de execução com " << num_threads << " threads: " << duration.count() << " ms" << endl;
    }

    return 0;
}

