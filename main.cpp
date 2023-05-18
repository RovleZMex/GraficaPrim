#include <iostream>
#include <climits>
#include <unordered_set>
#include <queue>
#include <vector>
#include "Grafica.h"

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

    return 0;
}
