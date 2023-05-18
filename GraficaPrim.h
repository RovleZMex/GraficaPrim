//
// Created by Santiago Robles on 16/05/23.
//

#ifndef PRIM_GRAFICAPRIM_H
#define PRIM_GRAFICAPRIM_H

#include <iostream>
#include "Grafica.h"
#include <vector>

/*
 * INICIAR DE UN VÉRTICE ALEATORIO Y AÑADIRLO
 * BUSCAR EN LAS ARISTAS DE LOS VERTICES AÑADIDOS, LA ARISTA DE MENOR PESO
 * CHECAR QUE EL VÉRTICE CON LA ARISTA NO CREE UN CICLO
 * AÑADIR ESA ARISTA JUNTO CON EL VÉRTICE AL NUEVO ÁRBOL
 * TERMINAR SI TODOS LOS VERTICES HAN SIDO AÑADIDOS
 */

class Prim{
public:
    Prim(){};

    Grafica HacerAlgoritmo(const Grafica& g);

private:
};

#endif //PRIM_GRAFICAPRIM_H
