#include "grafo.hpp"

Grafo::Grafo(int numCidades, int numEstradas)
    : numCidades(numCidades), numEstradas(numEstradas), proximoIndice(0) {
    adjacencia.resize(numCidades);
}

void Grafo::adicionarEstrada(const std::string &cidade1, const std::string &cidade2) {
    if (mapaCidades.find(cidade1) == mapaCidades.end()) {
        mapaCidades[cidade1] = proximoIndice;
        indiceCidades[proximoIndice] = cidade1;
        proximoIndice++;
    }
    if (mapaCidades.find(cidade2) == mapaCidades.end()) {
        mapaCidades[cidade2] = proximoIndice;
        indiceCidades[proximoIndice] = cidade2;
        proximoIndice++;
    }

    int indice1 = mapaCidades[cidade1];
    int indice2 = mapaCidades[cidade2];

    adjacencia[indice1].push_back(indice2);
}

int Grafo::obterNumCidades() const {
    return numCidades;
}

const std::vector<int>& Grafo::obterVizinhos(int indice) const {
    return adjacencia[indice];
}

std::string Grafo::obterNomeCidade(int indice) const {
    if (indiceCidades.find(indice) != indiceCidades.end()) {
        return indiceCidades.at(indice);
    } else {
        throw std::out_of_range("Índice de cidade inválido");
    }
}


int Grafo::obterIndiceCidade(const std::string &nomeCidade) const {
    return mapaCidades.at(nomeCidade);
}

//Função para transpor que será usado no SCC
Grafo Grafo::transpor() const {
    Grafo grafoTransposto(numCidades, numEstradas);
    for (int i = 0; i < numCidades; i++) {
        for (int vizinho : adjacencia[i]) {
            grafoTransposto.adjacencia[vizinho].push_back(i);
        }
    }
    return grafoTransposto;
}
