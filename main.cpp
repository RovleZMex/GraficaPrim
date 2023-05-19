#include <iostream>
#include "Grafica.h"
#include "Prim.h"

int main() {
    // Crear una instancia de la gráfica
    Grafica grafica;

    // Agregar nodos a la gráfica
    grafica.AgregarNodo("A");
    grafica.AgregarNodo("B");
    grafica.AgregarNodo("C");
    grafica.AgregarNodo("D");
    grafica.AgregarNodo("E");

    // Agregar aristas a la gráfica
    grafica.AgregarArista("A", "B", 5);
    grafica.AgregarArista("A", "C", 3);
    grafica.AgregarArista("B", "C", 2);
    grafica.AgregarArista("B", "D", 4);
    grafica.AgregarArista("C", "D", 6);
    grafica.AgregarArista("C", "E", 7);
    grafica.AgregarArista("D", "E", 1);

    grafica.Imprimir();

    Prim prim;
    prim.Ejecutar(grafica);

    return 0;
}
