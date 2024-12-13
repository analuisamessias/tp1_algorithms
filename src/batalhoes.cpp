#include "batalhoes.hpp"
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <limits>

// Função auxiliar para realizar DFS
void dfs(int v, const Grafo &grafo, std::vector<bool> &visitado, std::stack<int> &pilha) {
    visitado[v] = true;
    for (int vizinho : grafo.obterVizinhos(v)) {
        if (!visitado[vizinho]) {
            dfs(vizinho, grafo, visitado, pilha);
        }
    }
    pilha.push(v);
}

// Função auxiliar para realizar DFS no grafo transposto
void dfsTransposto(int v, const Grafo &grafo, std::vector<bool> &visitado, std::vector<int> &scc) {
    visitado[v] = true;
    scc.push_back(v);
    for (int vizinho : grafo.obterVizinhos(v)) {
        if (!visitado[vizinho]) {
            dfsTransposto(vizinho, grafo, visitado, scc);
        }
    }
}

// Função para calcular a distância da capital para todos os outros vértices usando BFS
std::vector<int> calcularDistancias(const Grafo &grafo, int capital) {
    int numCidades = grafo.obterNumCidades();
    std::vector<int> distancias(numCidades, std::numeric_limits<int>::max());
    std::queue<int> fila;

    distancias[capital] = 0;
    fila.push(capital);

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        for (int vizinho : grafo.obterVizinhos(atual)) {
            if (distancias[vizinho] == std::numeric_limits<int>::max()) {
                distancias[vizinho] = distancias[atual] + 1;
                fila.push(vizinho);
            }
        }
    }

    return distancias;
}

// Função para ordenar os batalhões em ordem alfabética usando Insertion Sort
void ordenarBatalhoes(std::vector<std::string> &batalhoes) {
    auto n = batalhoes.size();
    for (unsigned long int i = 1; i < n; i++) {
        std::string chave = batalhoes[i];
        auto j = i - 1;

        // Mover os elementos maiores que a chave para a direita
         while (j > 0 && batalhoes[j - 1].compare(chave) > 0) {
            batalhoes[j] = batalhoes[j - 1];
            j--;
        }
        batalhoes[j + 1] = chave;
    }
}

// Função para encontrar os batalhões secundários usando busca manual
std::vector<std::string> encontrarBatalhoesSecundarios(const Grafo &grafo, const std::string &capital) {
    auto numCidades = grafo.obterNumCidades();
    std::vector<bool> visitado(numCidades, false);
    std::stack<int> pilha;

    // Passo 1: Realizar DFS e empilhar os vértices
    for (auto i = 0; i < numCidades; i++) {
        if (!visitado[i]) {
            dfs(i, grafo, visitado, pilha);
        }
    }

    // Passo 2: Transpor o grafo
    Grafo grafoTransposto = grafo.transpor();

    // Passo 3: Encontrar os SCCs no grafo transposto
    std::fill(visitado.begin(), visitado.end(), false);
    std::vector<std::string> batalhoes;
    int indiceCapital = grafo.obterIndiceCidade(capital);
    std::vector<int> distancias = calcularDistancias(grafo, indiceCapital);

    while (!pilha.empty()) {
        int v = pilha.top();
        pilha.pop();

        if (!visitado[v]) {
            std::vector<int> scc;
            dfsTransposto(v, grafoTransposto, visitado, scc);

            // Verificar se o SCC inclui a capital
            bool capitalPresente = false;
            for (int indice : scc) {
                if (indice == indiceCapital) {
                    capitalPresente = true;
                    break;
                }
            }

            // Se a capital não estiver presente, adicionar batalhão
            if (!capitalPresente) {
                // Encontrar o vértice mais próximo da capital
                int melhorIndice = scc[0];
                int menorDistancia = distancias[melhorIndice];

                for (int indice : scc) {
                    int distancia = distancias[indice];
                    if (distancia < menorDistancia) {
                        melhorIndice = indice;
                        menorDistancia = distancia;
                    }
                }

                batalhoes.push_back(grafo.obterNomeCidade(melhorIndice));
            }
        }
    }

    // Ordenar os batalhões em ordem alfabética
    ordenarBatalhoes(batalhoes);

    return batalhoes;
}
