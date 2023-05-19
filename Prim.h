//
// Created by Santiago Robles on 18/05/23.
//

#ifndef PRIM_PRIM_H
#define PRIM_PRIM_H

#include "Grafica.h"
#include <vector>
#include <algorithm>
#include <queue>

class Prim {
public:
    /**
     * @brief Constructor default
     */
    Prim() = default;

    /**
     * @brief Aplica el algoritmo Prim a una grafica y regresa la subgrafica de menor peso
     * @param graficaOriginal Grafica a la que se le aplicará el algoritmo Prim
     * @return Grafica de recubrimiento minimo
     */
    static Grafica Ejecutar(const Grafica &graficaOriginal);

private:
    /**
     * @brief Verifica si una grafica es conexa
     * @param grafica Grafica a verificar
     * @return true si la grafica es conexa, false de lo contrario
     */
    static bool EsConexa(const Grafica &grafica);
};

#endif //PRIM_PRIM_H
