#include "capital.hpp"
#include <queue>
#include <vector>
#include <limits>

//Função para verificar se a cidade consegue alcançar todas as outras usando BFS
bool verificarConectividade(const Grafo &grafo, int cidadeInicial) {
    int numCidades = grafo.obterNumCidades();
    std::vector<bool> visitado(numCidades, false);
    std::queue<int> fila;

    visitado[cidadeInicial] = true;
    fila.push(cidadeInicial);
    int visitados = 1;

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        for (int vizinho : grafo.obterVizinhos(atual)) {
            if (!visitado[vizinho]) {
                visitado[vizinho] = true;
                fila.push(vizinho);
                visitados++;
            }
        }
    }

    //Verifica se todas as cidades foram visitadas
    return (visitados == numCidades);
}

//Realiza BFS e calcula a soma das distâncias a partir de uma cidade
int calcularDistanciaTotal(const Grafo &grafo, int cidadeInicial) {
    int numCidades = grafo.obterNumCidades();
    std::vector<int> distancia(numCidades, std::numeric_limits<int>::max());
    std::queue<int> fila;

    distancia[cidadeInicial] = 0;
    fila.push(cidadeInicial);

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        for (int vizinho : grafo.obterVizinhos(atual)) {
            if (distancia[vizinho] == std::numeric_limits<int>::max()) {
                distancia[vizinho] = distancia[atual] + 1;
                fila.push(vizinho);
            }
        }
    }

    //Soma as distâncias para todas as cidades
    int somaDistancias = 0;
    for (int d : distancia) {
        somaDistancias += d;
    }

    return somaDistancias;
}

//Função para encontrar a capital
std::string encontrarCapital(const Grafo &grafo) {
    int numCidades = grafo.obterNumCidades();
    int menorSoma = std::numeric_limits<int>::max();
    int indiceCapital = -1;

    //Loop que testa cada cidade do grafo
    for (int i = 0; i < numCidades; i++) {
        //Verifica se a cidade atende os critérios de capital
        if (verificarConectividade(grafo, i)) {
            int somaDistancias = calcularDistanciaTotal(grafo, i);
            if (somaDistancias < menorSoma) {
                menorSoma = somaDistancias;
                indiceCapital = i;
            }
        }
    }

    //Retorna a cidade que será a capital, ou uma mensagem de erro se não encontrar
    if (indiceCapital != -1) {
        return grafo.obterNomeCidade(indiceCapital);
    } else {
        return "Nenhuma cidade atende os critérios de capital";
    }
}
