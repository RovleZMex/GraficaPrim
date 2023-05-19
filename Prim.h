//
// Created by Santiago Robles on 18/05/23.
//

#ifndef PRIM_PRIM_H
#define PRIM_PRIM_H

#include "Grafica.h"
#include <vector>

class Prim{
public:
    Prim()= default;

    Grafica Ejecutar(const Grafica& graficaOriginal) const;

};

#endif //PRIM_PRIM_H
