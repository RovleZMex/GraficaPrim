//
// Created by Santy on 19/04/2023.
//

#ifndef GRAFICA_GRAFICA_H
#define GRAFICA_GRAFICA_H

#include <iostream>
#include <utility>

/**
 * @brief Clase que representa una gráfica no dirigida.
 * Esta clase implementa una gráfica no dirigida utilizando una lista de adyacencia.
 * Los nodos están representados por la estructura Nodo y las aristas por la estructura Arista dentro de cada Nodo.
 */
class Grafica {
    friend class AlgoritmoPrim;

public:
    /**
     * @brief Constructor de la clase grafica
     * Crea una grafica vacia
     */
    Grafica();

    /**
     * @brief Destructor de la clase grafica
     * Libera la memoria utilizada por los nodos y las aristas
     */
    ~Grafica();

    /**
     * @brief Agrega un nodo a la grafica
     * @param etiqueta La etiqueta que identifica al nuevo nodo
     */
    void AgregarNodo(std::string etiqueta);

    /**
     * @brief Elimina un nodo de la grafica
     * @param etiqueta La etiqueta del nodo a eliminar
     */
    void EliminarNodo(const std::string &etiqueta);


    /**
     * @brief Agrega una arista a la grafica entre dos nodos existentes
     * @param inicio La etiqueta del nodo inicial de la arista
     * @param fin La etiqueta del nodo final de la arista
     */
    void AgregarArista(const std::string &inicio, const std::string &fin, int peso = 0);

    /**
     * @brief Obtiene el numero de nodos de la grafica
     * @return El numero de nodos de la grafica
     */
    unsigned ObtenerNumNodos() const;

    /**
     * @brief Regresa el peso de las aristas en la gráfica
     * @return El peso de las aristas en la gráfica
     */
    int ObtenerPesoAristas() const;


    /**
     * @brief Obtiene el grado de un nodo de la grafica
     * @throws NodoNoEncotrado
     * @param etiqueta La etiqueta del nodo
     * @return El grado del nodo
     */
    unsigned ObtenerGrado(const std::string &etiqueta);

    /**
     * @brief Imprime los nodos de la grafica con sus aristas
     */
    void Imprimir() const;

    /**
     * @brief Elimina una arista existente
     * @throws NodoNoEncontrado
     * @param inicio La etiqueta del nodo inicial
     * @param fin La etiqueta del nodo final
     */
    void EliminarArista(const std::string &inicio, const std::string &fin);

    /**
     * @brief Sobrecarga del operador de asignacion
     * @param otra La grafica a asignar
     * @return Una referencia a la grafica actual
     */
    Grafica &operator=(const Grafica &otra);

    /**
     * @brief Constructor de copias
     * @param otra La grafica a copiar
     */
    Grafica(const Grafica &otra);

    /**
     * @brief Vacia la grafica
     */
    void Vaciar();

    /**
     * @brief Obtiene el numero de aristas de la grafica
     * @return El numero de aristas de la grafica
     */
    unsigned ObtenerAristas() const;

    /**
     * @brief Busca si un nodo existe en la grafica
     * @param etiqueta La etiqueta del nodo a buscar
     * @return true si el nodo existe, false de lo contrario
     */
    bool BuscarNodo(const std::string &etiqueta) const;

    /**
     * @brief Busca si una arista existe en la grafica
     * @throws NodoNoEncontrado
     * @param inicio La etiqueta del nodo inicial
     * @param fin La etiqueta del nodo final
     * @return true si existe la arista, false de lo contrario
     */
    bool BuscarArista(const std::string &inicio, const std::string &fin) const;

    /**
     * @brief Verifica si la grafica esta vacia
     * @return true si esta vacia, false de lo contrario
     */
    bool EstaVacia() const;

    struct Nodo {
        unsigned grado; /**<Grado del nodo */
        std::string etiqueta; /**<Etiqueta del nodo */
        Nodo *siguiente; /**<Puntero al siguiente nodo */

        struct Arista {
            Nodo *adyacente; /**<Puntero al nodo adyacente de la arista */
            Arista *sigArista; /**<Puntero a la siguiente arista del nodo */
            int peso; /**<Entero que representa el peso de la arista*/

            /**
             * @brief Constructor de Arista
             * @param ady Puntero al nodo adyacente de la arista
             * @param sigA Puntero a la siguiente arista del nodo
             */
            explicit Arista(Nodo *ady, Arista *sigA = nullptr, int p = 0) : adyacente(ady), sigArista(sigA), peso(p) {};

        } *pArista /**<Puntero a la primera arista del nodo */;

        /**
         * @brief Constructor de nodo
         * @param et La etiqueta que identifica al nodo
         * @param gr Grado del nodo
         * @param sigN Puntero al siguiente nodo de la grafica
         * @param pA Puntero a la primera arista del nodo
         */
        explicit Nodo(std::string et, int gr = 0, Nodo *sigN = nullptr, Arista *pA = nullptr) : grado(gr),
                                                                                                siguiente(sigN),
                                                                                                pArista(pA),
                                                                                                etiqueta(std::move(
                                                                                                        et)) {};

        /**
         * @brief Agrega una arista al nodo
         * @throws NodoNoEncontrado
         * @param ady Puntero al nodo adyacente de la arista
         */
        void AgregarArista(Nodo *ady, int peso);

        /**
         * @brief Imprime las aristas del nodo
         */
        void ImprimirAristas() const;

        /**
         * @brief Elimina una arista del nodo
         * @param ady Puntero al nodo adyacente de la arista que se quiere eliminar
         */
        void EliminarArista(Nodo *ady);

    } *pNodo, *uNodo; /**<Puntero al primer y ultimo nodo de la grafica */
    /**
 * @brief Regresa un puntero al nodo buscado
 * @param etiqueta La etiqueta del nodo a buscar
 * @return Puntero al nodo buscado, nullptr si no se encuentra
 */
    Nodo *ObtenerNodo(const std::string &etiqueta) const;


private:
    unsigned numNodos; /**<Numero de nodos en la grafica */
    unsigned numAristas; /**<Numero de aristas en la grafica */
    int pesoAristas; /**<Peso de las aristas en la grafica*/


    /**
     * @brief Ordena los nodos en orden ascendente
     */
    void OrdenarNodos();

    /**
     * @brief Verifica si un arista existe entre dos nodos
     * @param a Puntero al nodo inicial de la arista
     * @param b Puntero al nodo final de la arista
     * @return true si la arista existe, false de lo contrario
     */
    bool BuscarArista(Nodo *a, Nodo *b) const;
};

class NodoNoEncontrado : public std::exception {
public:
    const char *what() const noexcept override {
        return "Nodo no encontrado";
    }
};


#endif //GRAFICA_GRAFICA_H
