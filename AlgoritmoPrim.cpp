//
// Created by Santy on 17/05/2023.
//

#include "AlgoritmoPrim.h"


Grafica AlgoritmoPrim::AplicarAlgoritmo(const Grafica &g) {

    Grafica resultado;

    std::vector<std::string> nodosVisitados;
    std::vector<std::pair<std::string, std::string>> aristasElegidas;

    std::vector<Grafica::Nodo *> nodosOriginales = g.ObtenerNodos();

    if (!g.EstaVacia()) nodosVisitados.push_back(g.ObtenerPrimerNodo());
    else return resultado;

    while (nodosVisitados.size() != nodosOriginales.size()) {
        for (Grafica::Nodo * nodo: nodosOriginales) {
            //Elegir arista que incida en un vertice que este en los visitados y uno que no este, de menor peso

        }
    }

    return resultado;
}
