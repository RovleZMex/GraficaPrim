//
// Created by Santiago Robles on 18/05/23.
//

#include "Prim.h"

Grafica Prim::Ejecutar(const Grafica &graficaOriginal) {
    Grafica resultado;

    if (graficaOriginal.EstaVacia()) return resultado;

    std::vector<Grafica::Nodo *> nodosVisitados;
    std::vector<std::pair<std::string, std::string>> aristasElegidas;
    std::vector<int> pesosAristas;

    // Agregar el primer nodo a la gráfica resultado y a nodosVisitados
    Grafica::Nodo *primerNodo = graficaOriginal.pNodo;
    resultado.AgregarNodo(primerNodo->etiqueta);
    nodosVisitados.push_back(primerNodo);

    // Verificar si la graficaOriginal es conexa
    if (!EsConexa(graficaOriginal)) {
        throw std::runtime_error("Grafica no conexa");
    }

    while (nodosVisitados.size() < graficaOriginal.ObtenerNumNodos()) {
        int menorPeso = INT_MAX;
        Grafica::Nodo *nodoOrigen = nullptr;
        Grafica::Nodo *nodoDestino = nullptr;

        // Buscar la arista de menor peso que conecte con un nodo no visitado
        for (Grafica::Nodo *nodo: nodosVisitados) {
            Grafica::Nodo::Arista *tempArista = nodo->pArista;

            while (tempArista != nullptr) {
                if (std::find(nodosVisitados.begin(), nodosVisitados.end(), tempArista->adyacente) ==
                    nodosVisitados.end()) {
                    // El nodo adyacente no está visitado, checar si el peso es menor
                    if (tempArista->peso < menorPeso) {
                        menorPeso = tempArista->peso;
                        nodoOrigen = nodo;
                        nodoDestino = tempArista->adyacente;
                    }
                }
                tempArista = tempArista->sigArista;
            }
        }

        if (nodoOrigen != nullptr && nodoDestino != nullptr) {
            // Agregar el nodo destino a la gráfica resultado y a nodosVisitados
            resultado.AgregarNodo(nodoDestino->etiqueta);
            nodosVisitados.push_back(nodoDestino);

            // Agregar la arista elegida a las estructuras correspondientes
            aristasElegidas.emplace_back(nodoOrigen->etiqueta, nodoDestino->etiqueta);
            pesosAristas.push_back(menorPeso);
        }
    }

    // Agregar las aristas elegidas a la gráfica resultado
    for (int i = 0; i < aristasElegidas.size(); ++i) {
        resultado.AgregarArista(aristasElegidas[i].first, aristasElegidas[i].second, pesosAristas[i]);
    }

    return resultado;
}

bool Prim::EsConexa(const Grafica &grafica) {
    if (grafica.EstaVacia()) return true;

    std::vector<Grafica::Nodo *> nodosVisitados;
    std::queue<Grafica::Nodo *> nodosPorVisitar;

    Grafica::Nodo *primerNodo = grafica.pNodo;
    nodosVisitados.push_back(primerNodo);
    nodosPorVisitar.push(primerNodo);


    while (!nodosPorVisitar.empty()) {
        Grafica::Nodo *nodoActual = nodosPorVisitar.front();
        nodosPorVisitar.pop();

        Grafica::Nodo::Arista *aristaActual = nodoActual->pArista;
        while (aristaActual != nullptr) {
            if (std::find(nodosVisitados.begin(), nodosVisitados.end(), aristaActual->adyacente) ==
                nodosVisitados.end()) {
                nodosVisitados.push_back(aristaActual->adyacente);
                nodosPorVisitar.push(aristaActual->adyacente);
            }
            aristaActual = aristaActual->sigArista;
        }
    }

    return nodosVisitados.size() == grafica.ObtenerNumNodos();
}



