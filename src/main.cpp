#include <iostream>
#include "grafo.hpp"
#include "capital.hpp"
#include "batalhoes.hpp"
#include "patrulhamento.hpp"

using namespace std;

int main() {
    int numCidades, numEstradas;
    cin >> numCidades >> numEstradas;

    //Gerando os grafos a partir das entradas 
    Grafo grafo(numCidades, numEstradas);

    for (int i = 0; i < numEstradas; i++) {
        string cidade1, cidade2;
        cin >> cidade1 >> cidade2;
        grafo.adicionarEstrada(cidade1, cidade2);
    }

    //Encontrando a Capital
    string capital = encontrarCapital(grafo);
    cout << "\n" << capital << endl;

    //Encontrando os batalhões secundários
    vector<string> batalhoes = encontrarBatalhoesSecundarios(grafo, capital);
    cout << batalhoes.size() << endl;
    for (const string &cidade : batalhoes) {
        cout << cidade << endl;
    }
    
    //Encontrando as rotas de patrulhamento  
    vector<vector<string>> rotas = encontrarRotasDePatrulhamento(grafo);
    cout << rotas.size() << endl;
    for (const auto &rota : rotas) {
        for (const string &cidade : rota) {
            cout << cidade << " ";
        }
        cout << endl;
    }

    return 0;
}
