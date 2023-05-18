#include <queue>
#include <set>
#include <vector>
#include "Grafica.h"

struct NodoDistancia {
    std::string etiqueta;
    int distancia;

    NodoDistancia(const std::string& etiq, int dist) : etiqueta(etiq), distancia(dist) {}

    bool operator<(const NodoDistancia& otro) const {
        return distancia > otro.distancia;
    }
};

Grafica obtenerGrafoResultado(const Grafica& graficaOriginal) {
    Grafica resultado;

    std::string primerNodo = graficaOriginal.ObtenerPrimerNodo();
    if (primerNodo.empty()) {
        return resultado;
    }

    std::set<std::string> visitados;
    std::priority_queue<NodoDistancia> colaPrioridad;
    colaPrioridad.push(NodoDistancia(primerNodo, 0));

    while (!colaPrioridad.empty()) {
        NodoDistancia nodoActual = colaPrioridad.top();
        colaPrioridad.pop();

        if (visitados.count(nodoActual.etiqueta) > 0) {
            continue;
        }

        visitados.insert(nodoActual.etiqueta);
        resultado.AgregarNodo(nodoActual.etiqueta);

        const Grafica::Nodo* nodo = graficaOriginal.ObtenerNodo(nodoActual.etiqueta);
        if (nodo != nullptr) {
            Grafica::Nodo::Arista* arista = nodo->pArista;
            while (arista != nullptr) {
                if (!visitados.count(arista->adyacente->etiqueta)) {
                    colaPrioridad.push(NodoDistancia(arista->adyacente->etiqueta, arista->peso));
                }
                arista = arista->sigArista;
            }
        }
    }

    for (const std::string& nodo : visitados) {
        const Grafica::Nodo* nodoOriginal = graficaOriginal.ObtenerNodo(nodo);
        if (nodoOriginal != nullptr) {
            Grafica::Nodo::Arista* arista = nodoOriginal->pArista;
            while (arista != nullptr) {
                if (visitados.count(arista->adyacente->etiqueta) > 0) {
                    resultado.AgregarArista(nodo, arista->adyacente->etiqueta, arista->peso);
                }
                arista = arista->sigArista;
            }
        }
    }

    return resultado;
}




int main() {
    Grafica grafica;
    // Agrega los nodos y aristas a tu gráfica aquí
    grafica.AgregarNodo("A");
    grafica.AgregarNodo("B");
    grafica.AgregarNodo("C");
    grafica.AgregarNodo("D");
    grafica.AgregarArista("A","B",7);
    grafica.AgregarArista("A","C", 2);
    grafica.AgregarArista("A","D", 1);
    grafica.AgregarArista("B","D", 3);
    grafica.AgregarArista("C","D", 14);

    Grafica resultado = obtenerGrafoResultado(grafica);

    resultado.Imprimir();

    return 0;
}
