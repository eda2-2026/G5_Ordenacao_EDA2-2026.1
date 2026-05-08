#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
#include <stdexcept>

class DataManager {
public:

    void gerar_dataset(int quantidade, const std::string& path) {

        if (quantidade <= 0)
            throw std::invalid_argument("Quantidade deve ser maior que zero.");

        std::ofstream arquivo(path);
        if (!arquivo.is_open())
            throw std::runtime_error("Nao foi possivel criar o arquivo: " + path);

        arquivo << "nome\n";

        std::mt19937 rng(std::random_device{}());

        auto sortear = [&](const std::vector<std::string>& lista) -> const std::string& {
            std::uniform_int_distribution<int> dist(0, lista.size() - 1);
            return lista[dist(rng)];
        };

        const std::vector<std::string> primeiros_nomes = {
            "Miguel", "Arthur", "Heitor", "Theo", "Davi", "Gabriel", "Pedro",
            "Matheus", "Rafael", "Guilherme", "Lucas", "Enzo", "Nicolas", "Cauã",
            "Felipe", "Joao", "Bernardo", "Samuel", "Daniel", "Vitor", "Eduardo",
            "Henrique", "Gustavo", "Leonardo", "Rodrigo", "Marcos", "Bruno",
            "Carlos", "Diego", "Fabio", "Sofia", "Alice", "Laura", "Isabella",
            "Manuela", "Julia", "Heloisa", "Valentina", "Maria", "Giovanna",
            "Beatriz", "Lara", "Natalia", "Camila", "Fernanda", "Ana", "Leticia",
            "Gabriela", "Mariana", "Larissa", "Bianca", "Livia", "Clara",
            "Carolina", "Amanda", "Bruna", "Vitoria", "Yasmin", "Rebeca",
            "Melissa", "Luana", "Vanessa", "Priscila", "Renata", "Aline",
            "Patricia", "Juliana", "Luciana", "Adriana", "Simone", "Cristina",
            "Andre", "Alexandre", "Antonio", "Caio", "Cesar", "Claudio",
            "Cristiano", "Danilo", "Edson", "Emerson", "Evandro", "Flavio",
            "Francisco", "Ivan", "Jorge", "Jose", "Junior", "Leandro", "Luiz",
            "Marcelo", "Mauricio", "Paulo", "Ricardo", "Roberto", "Sergio",
            "Thiago", "Wagner", "Wilson"
        };

        const std::vector<std::string> nomes_do_meio = {
            "Augusto", "Henrique", "Felipe", "Miguel", "Gabriel", "Rafael",
            "Luiz", "Carlos", "Eduardo", "Antonio", "Jose", "Pedro", "Paulo",
            "Roberto", "Alexandre", "Andre", "Bruno", "Daniel", "Fernando",
            "Gustavo", "Maria", "das Gracas", "Aparecida", "de Fatima",
            "Cristina", "Helena", "Beatriz", "Clara", "Fernanda", "Juliana",
            "Lucia", "Regina", "Rita", "Rosa", "Tereza", "Vitoria",
            "dos Santos", "Oliveira", "Rodrigues", "Ferreira", "Lima"
        };

        const std::vector<std::string> sobrenomes = {
            "Silva", "Santos", "Oliveira", "Souza", "Rodrigues", "Ferreira",
            "Alves", "Pereira", "Lima", "Gomes", "Costa", "Ribeiro", "Martins",
            "Carvalho", "Almeida", "Lopes", "Soares", "Fernandes", "Vieira",
            "Barbosa", "Rocha", "Dias", "Nascimento", "Andrade", "Moreira",
            "Nunes", "Marques", "Machado", "Mendes", "Freitas", "Cardoso",
            "Ramos", "Goncalves", "Santana", "Teixeira", "Araujo", "Azevedo",
            "Cavalcanti", "Cruz", "Fonseca", "Guimaraes", "Miranda", "Monteiro",
            "Moraes", "Melo", "Pinto", "Pires", "Queiroz", "Rezende", "Sales",
            "Sampaio", "Siqueira", "Tavares", "Torres", "Vasconcelos", "Correia",
            "Campos", "Castro", "Cunha", "Duarte", "Figueiredo", "Franco",
            "Leite", "Macedo", "Magalhaes", "Maia", "Medeiros", "Nogueira",
            "Neves", "Pacheco", "Paiva", "Peixoto", "Pessoa", "Pinheiro",
            "Rego", "Sa", "Valente", "Xavier", "Amaral", "Assis", "Barros",
            "Bastos", "Borges"
        };

        for (int i = 0; i < quantidade; i++) {
            std::string nome = sortear(primeiros_nomes) + " "
                             + sortear(nomes_do_meio)   + " "
                             + sortear(sobrenomes);
            arquivo << nome << "\n";
        }

        arquivo.close();
    }

    std::vector<std::string> carregar_nomes(const std::string& path) {

        std::ifstream arquivo(path);
        if (!arquivo.is_open())
            throw std::runtime_error("Nao foi possivel abrir o arquivo: " + path);

        std::vector<std::string> nomes;
        std::string linha;

        std::getline(arquivo, linha); // pula o cabeçalho "nome"

        while (std::getline(arquivo, linha)) {
            if (!linha.empty())
                nomes.push_back(linha);
        }

        arquivo.close();
        return nomes;
    }

    bool esta_ordenado(const std::vector<std::string>& data) {

        for (int i = 0; i + 1 < (int)data.size(); i++) {
            if (data[i] > data[i + 1])
                return false;
        }
        return true;
    }
};
