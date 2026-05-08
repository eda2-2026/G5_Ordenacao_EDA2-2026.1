#include <iostream>
#include <vector>
#include <string>
#include <fstream> // Necessário para manipular arquivos de saída

#include "src/DataManager.h"
#include "src/MergeSort.h"
#include "src/PerformerTimer.h"

int TestMergeSort() {

    DataManager dataManager;
    ParallelMergeSort mergeSort; 
    PerformerTimer timer;

    // Quantidades de elementos testados na ordenação
    std::vector<int> tamanhos_teste = {
        1000,       // 1 mil
        5000,       // 5 mil
        10000,      // 10 mil
        25000,      // 25 mil
        50000,      // 50 mil
        75000,      // 75 mil
        100000,     // 100 mil
        250000,     // 250 mil
        500000,     // 500 mil
        750000,     // 750 mil
        1000000,    // 1 milhoes
        1500000,    // 1.5 milhoes
        2000000,    // 2 milhoes
        3000000,    // 3 milhoes
        4000000,    // 4 milhoes
        5000000     // 5 milhoes
    };

    // Cria o arquivo CSV para salvar os resultados do benchmark
    std::ofstream arquivo_csv("../benchmarks/benchmark-merge-sort.csv");
    if (!arquivo_csv.is_open()) {
        std::cerr << "Erro ao criar o arquivo CSV para salvar os resultados!\n";
        return 1;
    }

    // Escreve o cabeçalho no arquivo CSV
    arquivo_csv << "quantidade de nomes a ordenar,tempo total de ordenacao\n";

    std::cout << "\nIniciando testes de desempenho do Parallel Merge Sort...\n\n";

    for (int quantidade : tamanhos_teste) {
        std::string nome_arquivo = "dataset_nomes_" + std::to_string(quantidade) + ".csv";

        // Gera o banco de num arquivo CSV com a
        // quantidade especificada de nomes
        dataManager.gerar_dataset(quantidade, nome_arquivo);

        // Carrega os nomes do arquivo gerado para um vetor na memória
        std::vector<std::string> nomes_para_ordenar = dataManager.carregar_nomes(nome_arquivo);

        // Inicia o cronômetro utilizando a classe PerformerTimer
        timer.start();

        // Executa o MergeSort
        mergeSort.Sort(nomes_para_ordenar);

        // Para o cronômetro
        timer.stop();

        // Obtem o tempo gasto
        double tempo_ms = timer.get_time_ms();

        // Salva a quantidade de nomes e tempo gasto no
        // arquivo csv
        arquivo_csv << quantidade << "," << tempo_ms << "\n";

        // Usa a DataMager para verificar se o vetor esta
        // realmente ordenado
        bool sucesso_ordenacao = dataManager.esta_ordenado(nomes_para_ordenar);

        // Imprime o resultado no terminal
        std::cout << "Quantidade de nomes a ordenar: " << quantidade << "\n"
                  << "Tempo total de ordenacao: " << tempo_ms << " milissegundos\n"
                  << "Status final: " << (sucesso_ordenacao ? "Sucesso (Vetor Ordenado)" : "FALHA (Vetor Desordenado)") << "\n"
                  << "--------------------------------------------------\n";
    }

    // Fecha o arquivo csv
    arquivo_csv.close();

    std::cout << "Testes finalizados.\n";
    std::cout << "Os dados foram salvos no arquivo 'benchmark-merge-sort.csv'.\n";

    return 0;
}

int main() {
    return TestMergeSort();
}