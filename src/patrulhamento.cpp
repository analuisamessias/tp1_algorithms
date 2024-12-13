#include "patrulhamento.hpp"
#include "batalhoes.hpp"
#include "capital.hpp"
#include <vector>
#include <stack>
#include <map>
#include <iostream>

using namespace std;

// Função auxiliar para realizar DFS e construir a rota de patrulhamento com base nas arestas
void dfsPatrulha(int v, vector<vector<pair<int, int>>> &adj, vector<bool> &visitadoAresta, vector<int> &rota, int batalhao, const vector<bool> &temBatalhao) {
    for (auto &vizinho : adj[v]) {
        int u = vizinho.first;
        int idAresta = vizinho.second;

        // Se a aresta não foi visitada, percorra-a
        if (!visitadoAresta[idAresta]) {
            visitadoAresta[idAresta] = true;
            rota.push_back(v);
            dfsPatrulha(u, adj, visitadoAresta, rota, batalhao, temBatalhao);
        }
    }
}

// Função para encontrar rotas de patrulhamento para os batalhões auxiliares ou capital
vector<vector<string>> encontrarRotasDePatrulhamento(const Grafo &grafo) {
    vector<vector<string>> rotas;
    unsigned long int numCidades = grafo.obterNumCidades();
    int numeCidades = grafo.obterNumCidades();
    vector<vector<pair<int, int>>> adj(numCidades);
    vector<bool> visitadoAresta;
    auto numArestas = 0;

    // Construir a lista de adjacências com identificadores de arestas
    for (auto i = 0; i < numeCidades; i++) {
       for (auto vizinho : grafo.obterVizinhos(i)) { { 
            adj[i].emplace_back(vizinho, numArestas++);
            visitadoAresta.push_back(false);
        }
    }
    }

    // Encontrar a capital e os batalhões auxiliares
    string capital = encontrarCapital(grafo);
    vector<string> batalhoes = encontrarBatalhoesSecundarios(grafo, capital);
    unsigned long int n = batalhoes.size();
    // Caso todas as cidades além da capital tenham batalhões extras, não há necessidade de patrulhamento
    if (n == numCidades - 1) {
        return rotas;
    }

    // Caso não haja batalhões auxiliares, usar a capital para o patrulhamento
    if (batalhoes.empty()) {
        batalhoes.push_back(capital);
    }

    // Marcar as cidades que têm batalhões
    vector<bool> temBatalhao(numCidades, false);
    for (const string &batalhao : batalhoes) {
        temBatalhao[grafo.obterIndiceCidade(batalhao)] = true;
    }

    // Construir rotas de patrulhamento para cada batalhão auxiliar
    for (const string &batalhao : batalhoes) {
        int indiceBatalhao = grafo.obterIndiceCidade(batalhao);
        vector<int> rota;
        fill(visitadoAresta.begin(), visitadoAresta.end(), false);

        dfsPatrulha(indiceBatalhao, adj, visitadoAresta, rota, indiceBatalhao, temBatalhao);

        // Converter a rota para nomes de cidades, ignorando duplicações
        vector<string> rotaNomes;
        for (size_t i = 0; i < rota.size(); i++) {
            if (i == 0 || rota[i] != rota[i - 1]) {
                rotaNomes.push_back(grafo.obterNomeCidade(rota[i]));
            }
        }

        if (!rotaNomes.empty()) {
            rotas.push_back(rotaNomes);
        }
    }

    return rotas;
}
