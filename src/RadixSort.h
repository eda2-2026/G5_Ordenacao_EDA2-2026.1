#pragma once
#include <vector>
#include <string>

class RadixSort {
public:

    void Sort(std::vector<std::string> &data) {

        if (data.empty()) return;

        int maxLength = GetMaxLength(data);

        // Aplicamos o Radix LSD
        for (int char_index = maxLength - 1; char_index >= 0; char_index--) {
            CountingSort(data, char_index);
        }
    }

private:

    int GetMaxLength(std::vector<std::string> &data) {

        int maxLength = 0;

        // Percorre todas as strings dentro do vetor de dados
        for (int i = 0; i < data.size(); i++) {
            // Atualiza o tamanho maximo de uma string se encontrar uma string com tamanho maior
            // que maxLenght
            if (data[i].length() > maxLength) {
                maxLength = data[i].length();
            }
        }
        return maxLength;
    }

    void CountingSort(std::vector<std::string> &data, int char_index) {

        int data_length = data.size();
        if (data_length <= 1) return;

        // Primeiro passo: encontramos os maiores e o menores
        // valores do vetor

        int min_val = 256;
        int max_val = -1;

        // Vetor para armazenar os caracteres extraídos e evitar acessos repetidos
        std::vector<int> caracteres_extraidos(data_length);

        for (int i = 0; i < data_length; i++) {
            // Se o índice for maior que a string, tratamos como 0
            int c = 0;
            if (char_index < data[i].length()) {
                c = static_cast<unsigned char>(data[i][char_index]);
            }

            caracteres_extraidos[i] = c;

            if (c < min_val) min_val = c;
            if (c > max_val) max_val = c;
        }

        // Segundo passo: criamos o vetor auxiliar C de contagem
        // utilizando os valores min_val e max_val como base

        int range = max_val - min_val + 1;
        std::vector<int> contador(range, 0);
        std::vector<std::string> output(data_length);

        // Terceiro passo: preenchemos o vetor contador com as
        // ocorrências de cada um dos caracteres

        for (int i = 0; i < data_length; i++) {
            contador[caracteres_extraidos[i]-min_val]++;
        }

        // Quarto passo: atualizamos o vetor contador
        // com as posições finais de cada um dos
        // caracteres

        for (int i = 1; i < range; i++) {
            contador[i] += contador[i - 1];
        }

        // Quinto passo: construímos o vetor de saída

        for (int i = data_length - 1; i >= 0; i--) {
            int c = caracteres_extraidos[i];
            int pos = contador[c - min_val] - 1;
            output[pos] = data[i];
            contador[c - min_val]--;
        }

        // Sexto passo: copiamos os dados ordenados para o vetor original

        for (int i = 0; i < data_length; i++) {
            data[i] = output[i];
        }

    }

};