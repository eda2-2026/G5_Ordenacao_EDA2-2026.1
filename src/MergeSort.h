#pragma once
#include <vector>
#include <string>
#include <thread>
 
class ParallelMergeSort {
public:
 
    ParallelMergeSort(int max_threads = 4) : max_threads(max_threads) {}
 
    void Sort(std::vector<std::string>& data) {
        if (data.size() <= 1) return;
        vetor_auxiliar.resize(data.size());
        divisao_paralela(data, 0, (int)data.size() - 1, 0);
    }
 
private:
 
    int max_threads;
    std::vector<std::string> vetor_auxiliar;
 
    void merge(std::vector<std::string>& data, int inicio, int meio, int fim) {
 
        int i = inicio;
        int j = meio + 1;
        int k = inicio;
 
        // Intercala os dois lados em ordem crescente no vetor auxiliar
        while (i <= meio && j <= fim) {
            if (data[i] <= data[j])
                vetor_auxiliar[k++] = data[i++];
            else
                vetor_auxiliar[k++] = data[j++];
        }
 
        // Copia o que sobrou do lado esquerdo
        while (i <= meio)
            vetor_auxiliar[k++] = data[i++];
 
        // Copia o que sobrou do lado direito
        while (j <= fim)
            vetor_auxiliar[k++] = data[j++];
 
        // Devolve os dados ordenados para o vetor original
        for (int x = inicio; x <= fim; x++)
            data[x] = vetor_auxiliar[x];
    }
 
    void divisao_paralela(std::vector<std::string>& data, int inicio, int fim, int profundidade) {
 
        if (inicio >= fim) return;
 
        int meio = inicio + (fim - inicio) / 2;
 
        // Usa threads enquanto não atingir o limite de profundidade
        // Na profundidade d existem 2^d threads simultâneas
        // Paramos de criar threads quando 2^d >= max_threads
        bool usar_thread = (1 << profundidade) < max_threads;
 
        if (usar_thread) {
            // Metade esquerda roda em uma thread separada
            std::thread t([&]() {
                divisao_paralela(data, inicio, meio, profundidade + 1);
            });
 
            // Metade direita roda na thread atual
            divisao_paralela(data, meio + 1, fim, profundidade + 1);
 
            // Aguarda a thread da esquerda terminar antes de fazer o merge
            t.join();
 
        } else {
            // Abaixo do limite: execução sequencial normal
            divisao_paralela(data, inicio, meio, profundidade + 1);
            divisao_paralela(data, meio + 1, fim, profundidade + 1);
        }
 
        merge(data, inicio, meio, fim);
    }
};