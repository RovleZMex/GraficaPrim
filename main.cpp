#include <iostream>
#include "Grafica.h"
#include "Prim.h"

int main() {
    // Crear una instancia de la gráfica
    Grafica grafica;

    // Agregar nodos a la gráfica
    grafica.AgregarNodo("0");
    grafica.AgregarNodo("1");
    grafica.AgregarNodo("2");
    grafica.AgregarNodo("3");
    grafica.AgregarNodo("4");


    // Agregar aristas a la gráfica
    grafica.AgregarArista("0", "1", 2);
    grafica.AgregarArista("0", "2", 5);
    grafica.AgregarArista("0", "4", 6);
    grafica.AgregarArista("1", "2", 5);
    grafica.AgregarArista("1", "3", 3);
    grafica.AgregarArista("1", "4", 2);
    grafica.AgregarArista("2", "4", 4);
    grafica.AgregarArista("3", "4", 4);


    grafica.Imprimir();
    std::cout << "Peso de la gr\240fica original: " << grafica.ObtenerPesoAristas() << std::endl;
    std::cout << "======================================================================="<< std::endl;
    Grafica resultado = Prim::Ejecutar(grafica);
    resultado.Imprimir();
    std::cout <<"Peso de la subgr\240fica de recubrimiento m\241nimo: " << resultado.ObtenerPesoAristas() << std::endl;

    return 0;
}
