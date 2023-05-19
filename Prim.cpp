//
// Created by Santiago Robles on 18/05/23.
//

#include "Prim.h"

Grafica Prim::Ejecutar(const Grafica &graficaOriginal) const {
    Grafica resultado;

    if (graficaOriginal.EstaVacia())return resultado;

    std::vector<Grafica::Nodo *> nodosVisitados; //Contiene punteros a los nodos visitados

    std::vector<Grafica::Nodo *> nodosOriginales;

    std::vector<std::pair<std::string, std::string>> aristasElegidas;

    Grafica::Nodo *temp = graficaOriginal.pNodo;
    while (temp != nullptr) {
        resultado.AgregarNodo(temp->etiqueta);
        nodosOriginales.push_back(temp);
        temp = temp->siguiente;
    }

    nodosVisitados.push_back(resultado.pNodo);

    while (nodosVisitados.size() != resultado.ObtenerNumNodos()) {
        //Buscar en los nodos visitados la arista de menor peso que no esté en los nodos visitados
        for (Grafica::Nodo *nodo: nodosOriginales) {
            Grafica::Nodo::Arista *tempArista = nodo->pArista;
            std::cout << tempArista->adyacente->etiqueta;
            int menorPeso = INT_MAX;
            Grafica::Nodo::Arista *mejorArista = nullptr;
            while (tempArista != nullptr) {
                if (std::find(nodosVisitados.begin(), nodosVisitados.end(), tempArista->adyacente) ==
                    nodosVisitados.end()) {
                    //El nodo adyacente no está visitado, checar si el peso es menor
                    if (tempArista->peso < menorPeso) {
                        menorPeso = tempArista->peso;
                        mejorArista = tempArista;
                    }
                } else {
                    //siguiente arista por el adyacente ya se visitó
                    tempArista = tempArista->sigArista;
                }
                //if(mejorArista != nullptr) std::cout << tempArista->adyacente->etiqueta << std::endl;
                //else std::cout << "Arista nula" << std::endl;
                if(mejorArista != nullptr){
                    std::cout << "Agregado";
                    nodosVisitados.push_back(mejorArista->adyacente);
                    aristasElegidas.emplace_back(nodo->etiqueta, mejorArista->adyacente->etiqueta);
                }
            }
            //si el arista es nulo, terminar
        }
    }

    std::cout << aristasElegidas.size() << std::endl;

    return resultado;
}
