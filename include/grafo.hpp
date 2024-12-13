#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>

class Grafo {
public:
    Grafo(int numCidades, int numEstradas);
    void adicionarEstrada(const std::string &cidade1, const std::string &cidade2);
    int obterNumCidades() const;
    const std::vector<int>& obterVizinhos(int indice) const;
    std::string obterNomeCidade(int indice) const;
    int obterIndiceCidade(const std::string &nomeCidade) const;
    Grafo transpor() const;

private:
    int numCidades;
    int numEstradas;
    std::map<std::string, int> mapaCidades;
    std::map<int, std::string> indiceCidades;
    std::vector<std::vector<int>> adjacencia;
    int proximoIndice;
};

#endif
