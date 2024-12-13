#ifndef PATRULHAMENTO_HPP
#define PATRULHAMENTO_HPP

#include <vector>
#include <string>
#include "grafo.hpp"

bool verificarPatrulhamento(const Grafo &grafo);
std::vector<std::vector<std::string>> encontrarRotasDePatrulhamento(const Grafo &grafo);

#endif
