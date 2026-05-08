#include <iostream>
#include <vector>
#include <string>
#include "DataManager.h"
#include "PerformerTimer.h"
#include "RadixSort.h"
#include "MergeSort.h"
 
void imprimir_amostra(const std::vector<std::string>& nomes, const std::string& titulo) {
    std::cout << "\n  " << titulo << "\n";
    std::cout << "  " << std::string(40, '-') << "\n";
 
    std::cout << "  Inicio:\n";
    for (int i = 0; i < 10 && i < (int)nomes.size(); i++)
        std::cout << "    [" << i + 1 << "] " << nomes[i] << "\n";
 
    std::cout << "  ...\n";
 
    std::cout << "  Final:\n";
    int inicio_tail = std::max(10, (int)nomes.size() - 10);
    for (int i = inicio_tail; i < (int)nomes.size(); i++)
        std::cout << "    [" << i + 1 << "] " << nomes[i] << "\n";
 
    std::cout << "  " << std::string(40, '-') << "\n";
}
 
int main() {
 
    DataManager       dataManager;
    PerformerTimer    timer;
    RadixSort         radixSort;
    ParallelMergeSort mergeSort;
 
    // ─── Entrada do usuário ───────────────────────────────────────
    int quantidade;
    std::cout << "======================================\n";
    std::cout << "  G5 - Ordenacao de Nomes - EDA2 2026\n";
    std::cout << "======================================\n\n";
    std::cout << "Quantos nomes deseja gerar? ";
    std::cin  >> quantidade;
 
    // ─── Geração do dataset ───────────────────────────────────────
    std::string path = "dataset_nomes.csv";
    std::cout << "\nGerando " << quantidade << " nomes...\n";
    dataManager.gerar_dataset(quantidade, path);
    std::cout << "Dataset salvo em: " << path << "\n";
 
    // ─── Amostra antes da ordenação ───────────────────────────────
    std::vector<std::string> nomes_original = dataManager.carregar_nomes(path);
    imprimir_amostra(nomes_original, "Lista gerada (desordenada)");
 
    // ─── Radix Sort ───────────────────────────────────────────────
    std::cout << "\n======================================\n";
    std::cout << "  Radix Sort\n";
    std::cout << "======================================\n";
 
    std::vector<std::string> nomes_radix = nomes_original;
    std::cout << "\nExecutando...\n";
    timer.start();
    radixSort.Sort(nomes_radix);
    timer.stop();
 
    double tempo_radix = timer.get_time_ms();
    bool   radix_ok    = dataManager.esta_ordenado(nomes_radix);
 
    imprimir_amostra(nomes_radix, "Lista ordenada");
    std::cout << "  Tempo    : " << tempo_radix << " ms\n";
    std::cout << "  Ordenado : " << (radix_ok ? "sim" : "nao") << "\n";
 
    // ─── Merge Sort ───────────────────────────────────────────────
    std::cout << "\n======================================\n";
    std::cout << "  Parallel Merge Sort\n";
    std::cout << "======================================\n";
 
    std::vector<std::string> nomes_merge = nomes_original;
    std::cout << "\nExecutando...\n";
    timer.start();
    mergeSort.Sort(nomes_merge);
    timer.stop();
 
    double tempo_merge = timer.get_time_ms();
    bool   merge_ok    = dataManager.esta_ordenado(nomes_merge);
 
    std::cout << "  Tempo    : " << tempo_merge << " ms\n";
    std::cout << "  Ordenado : " << (merge_ok ? "sim" : "nao") << "\n";
 
    // ─── Comparação final ─────────────────────────────────────────
    std::cout << "\n======================================\n";
    std::cout << "  Resultado Final\n";
    std::cout << "======================================\n";
    std::cout << "  Nomes gerados  : " << quantidade   << "\n";
    std::cout << "  Radix Sort     : " << tempo_radix  << " ms\n";
    std::cout << "  Merge Sort     : " << tempo_merge  << " ms\n";
 
    if (tempo_radix < tempo_merge)
        std::cout << "\n  Radix Sort foi mais rapido por "
                  << (tempo_merge - tempo_radix) << " ms\n";
    else
        std::cout << "\n  Merge Sort foi mais rapido por "
                  << (tempo_radix - tempo_merge) << " ms\n";
 
    std::cout << "======================================\n";
 
    return 0;
}