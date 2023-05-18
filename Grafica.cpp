//
// Created by Santy on 19/04/2023.
//

#include "Grafica.h"

#include <utility>

//****************************************************************

Grafica::Grafica() {
    pNodo = nullptr;
    uNodo = nullptr;
    numAristas = 0;
    numNodos = 0;
    pesoAristas = 0;
}

//****************************************************************

Grafica::~Grafica() {
    Vaciar();
}

//****************************************************************

Grafica &Grafica::operator=(const Grafica &otra) {
    if (this == &otra) {
        return *this;
    }

    Vaciar();

    if (otra.EstaVacia()) {
        return *this;
    }

    Nodo *aux = otra.pNodo;

    while (aux != nullptr) {
        AgregarNodo(aux->etiqueta);
        aux = aux->siguiente;
    }

    return *this;
}

//****************************************************************

Grafica::Grafica(const Grafica &otra) {
    numNodos = 0;
    numAristas = 0;
    pNodo = nullptr;
    uNodo = nullptr;
    *this = otra;
}

//****************************************************************

void Grafica::AgregarNodo(std::string etiqueta) {
    Nodo *nuevo = new Nodo(std::move(etiqueta));
    if (numNodos == 0) {
        pNodo = uNodo = nuevo;
    } else {
        uNodo->siguiente = nuevo;
        uNodo = nuevo;
    }
    ++numNodos;
    OrdenarNodos();
}

//****************************************************************

void Grafica::EliminarNodo(const std::string &etiqueta) {
    // Buscar el nodo a eliminar
    Nodo *nodoAEliminar = ObtenerNodo(etiqueta);

    if (nodoAEliminar == nullptr) {
        // El nodo no existe, no hay nada que eliminar
        return;
    }
    numAristas = numAristas - nodoAEliminar->grado;

    // Eliminar las aristas que conectan al nodo
    Nodo *nodoActual = pNodo;
    while (nodoActual != nullptr) {
        nodoActual->EliminarArista(nodoAEliminar);
        nodoActual = nodoActual->siguiente;
    }

    // Eliminar el nodo de la lista de nodos
    if (pNodo == nodoAEliminar) {
        pNodo = nodoAEliminar->siguiente;
    } else {
        Nodo *nodoAnterior = pNodo;
        while (nodoAnterior->siguiente != nodoAEliminar) {
            nodoAnterior = nodoAnterior->siguiente;
        }
        nodoAnterior->siguiente = nodoAEliminar->siguiente;
    }

    // Liberar la memoria del nodo eliminado
    delete nodoAEliminar;

    // Actualizar el contador de nodos
    --numNodos;
}

//****************************************************************

unsigned Grafica::ObtenerNumNodos() const {
    return numNodos;
}

//****************************************************************

void Grafica::Imprimir() const {
    Nodo *aux = pNodo;
    while (aux != nullptr) {
        std::cout << aux->etiqueta << " -> ";
        aux->ImprimirAristas();
        std::cout << std::endl;
        aux = aux->siguiente;
    }
}

//****************************************************************

void Grafica::AgregarArista(const std::string &inicio, const std::string &fin, int peso) {
    Nodo *NodoI = ObtenerNodo(inicio);
    Nodo *NodoF = ObtenerNodo(fin);
    pesoAristas += peso;
    if (BuscarArista(NodoI, NodoF)) return;
    if (NodoI != nullptr && NodoF != nullptr) {
        NodoI->AgregarArista(NodoF, peso);
        if (NodoI != NodoF) {
            NodoF->AgregarArista(NodoI, peso);
        }
        ++numAristas;
        return;
    }
    std::cout << "Nodo no encontrado" << std::endl;
    throw NodoNoEncontrado();
}

//****************************************************************

Grafica::Nodo *Grafica::ObtenerNodo(const std::string &etiqueta) const {
    Nodo *actual = pNodo;
    while (actual != nullptr) {
        if (actual->etiqueta == etiqueta) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

//****************************************************************

void Grafica::Nodo::AgregarArista(Nodo *ady, int peso) {
    auto *nueva = new Arista(ady);
    nueva->peso = peso;
    if (grado == 0) {
        pArista = nueva;
    } else {
        Arista *actual = pArista;
        while (actual->sigArista != nullptr) {
            actual = actual->sigArista;
        }
        actual->sigArista = nueva;
    }
    ++grado;
}

//****************************************************************

void Grafica::Nodo::ImprimirAristas() const {
    Arista *actual = pArista;
    while (actual != nullptr) {
        std::cout << actual->adyacente->etiqueta << "(" << actual->peso << ")" << ", ";
        actual = actual->sigArista;
    }
    if (pArista != nullptr) std::cout << "\b\b";
}

//****************************************************************

void Grafica::Nodo::EliminarArista(Nodo *ady) {
    if (pArista == nullptr) {
        // No hay aristas que eliminar
        return;
    }

    if (pArista->adyacente == ady) {
        // La primera arista es la que se quiere eliminar
        Arista *temp = pArista;
        pArista = pArista->sigArista;
        delete temp;
        --grado;
        return;
    }

    Arista *aristaActual = pArista;
    // Checar si la siguiente arista es nula o si el adyacente de la siguiente es diferente
    // al nodo adyacente
    while (aristaActual->sigArista != nullptr && aristaActual->sigArista->adyacente != ady) {
        aristaActual = aristaActual->sigArista;
    }

    if (aristaActual->sigArista == nullptr) {
        // No se encontró la arista a eliminar
        return;
    }

    // Eliminar la arista encontrada
    Arista *temp = aristaActual->sigArista;
    aristaActual->sigArista = aristaActual->sigArista->sigArista;
    delete temp;
    --grado;
}

std::string Grafica::Nodo::ObtenerMenorArista() {
    Nodo::Arista *aux = pArista;
    int menorPeso = aux->peso;
    std::string etiquetaMenor = aux->adyacente->etiqueta;
    while(aux != nullptr){
        if(aux->peso < menorPeso){
            menorPeso = aux->peso;
            etiquetaMenor = aux->adyacente->etiqueta;
        }
        aux = aux->sigArista;
    }
    return etiquetaMenor;
}

//****************************************************************

unsigned Grafica::ObtenerGrado(const std::string &etiqueta) {
    Nodo *nodo = ObtenerNodo(etiqueta);
    if (nodo != nullptr) return nodo->grado;
    throw NodoNoEncontrado();
}

//****************************************************************

void Grafica::Vaciar() {
    Nodo *actual = pNodo;
    Nodo *aux;
    while (actual != nullptr) {
        aux = actual->siguiente;
        EliminarNodo(actual->etiqueta);
        actual = aux;
    }
}

//****************************************************************

void Grafica::EliminarArista(const std::string &inicio, const std::string &fin) {
    Nodo *inicial = ObtenerNodo(inicio);
    Nodo *ady = ObtenerNodo(fin);
    if (inicial != nullptr && ady != nullptr) {
        inicial->EliminarArista(ady);
        ady->EliminarArista(inicial);
        --numAristas;
        return;
    }
    throw NodoNoEncontrado();
}

//****************************************************************

bool Grafica::EstaVacia() const {
    return numNodos == 0;
}

//****************************************************************

void Grafica::OrdenarNodos() {
    Nodo *actual = pNodo;
    while (actual != nullptr) {
        Nodo *min = actual;
        Nodo *temp = actual->siguiente;
        while (temp != nullptr) {
            if (temp->etiqueta < min->etiqueta) {
                min = temp;
            }
            temp = temp->siguiente;
        }
        // Intercambiar el nodo actual con el nodo con la etiqueta más pequeña
        std::string tempEtiqueta = actual->etiqueta;
        actual->etiqueta = min->etiqueta;
        min->etiqueta = tempEtiqueta;
        actual = actual->siguiente;
    }
}

//****************************************************************

unsigned Grafica::ObtenerAristas() const {
    return numAristas;
}

//****************************************************************

bool Grafica::BuscarArista(Grafica::Nodo *a, Grafica::Nodo *b) const {
    Nodo *nInicial = pNodo;
    Nodo::Arista *aInicial;

    while (nInicial != nullptr) {
        aInicial = nInicial->pArista;
        while (aInicial != nullptr) {
            if (nInicial == a && aInicial->adyacente == b || nInicial == b && aInicial->adyacente == a) {
                return true;
            }
            aInicial = aInicial->sigArista;
        }
        nInicial = nInicial->siguiente;
    }

    return false;
}

//****************************************************************

bool Grafica::BuscarArista(const std::string &inicio, const std::string &fin) const {
    Nodo *a = ObtenerNodo(inicio);
    Nodo *b = ObtenerNodo(fin);
    if (a != nullptr && b != nullptr) {
        return BuscarArista(a, b);
    }
    throw NodoNoEncontrado();
}

//****************************************************************

bool Grafica::BuscarNodo(const std::string &etiqueta) const {
    return ObtenerNodo(etiqueta) != nullptr;
}

std::string Grafica::ObtenerMenorArista(const std::string& etiqueta) const{
    Nodo *temp = ObtenerNodo(etiqueta);
    return temp->ObtenerMenorArista();
}

std::string Grafica::ObtenerPrimerNodo() const{
    if(pNodo == nullptr) return "";
    return pNodo->etiqueta;
}

//****************************************************************

int Grafica::Nodo::Arista::ObtenerPeso() const {
    return peso;
}

//****************************************************************


