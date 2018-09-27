//Ailin Patiño - Estructuras de Datos - Comision 1.

#include <cstdio>
#include "ColaPedidos.h"

/**
 * Invariante de representacion.
 *
 * Los nodos con punteros forman un árbol binario.
 * El campo tam de cada nodo representa el tamaño de dicho subárbol (es decir, la cantidad de nodos).
 * El árbol tiene forma de árbol de Braun. Un árbol vacío es un árbol de Braun.
 *      Un árbol no vacío es un árbol de Braun si tiene las siguientes características:
 *      El hijo izquierdo es del mismo tamaño o a lo sumo un nodo más grande que su hijo derecho.
 *      Más precisamente, si llamamos k1 a la cantidad de nodos del hijo izquierdo y k2 a la cantidad de nodos
 *      del hijo derecho, entonces se cumple que k1 = k2 o que k1 = k2 + 1.
 *      Recursivamente, el hijo izquierdo y el hijo derecho son árboles de Braun.
 * Los nodos del árbol están ordenados con el invariante de heap. Un árbol vacío es un heap.
 *      Un árbol no vacío es un heap si tiene las siguientes características:
 *      La raíz tiene mayor prioridad que el resto de los nodos.
 *      Recursivamente, el hijo izquierdo y el hijo derecho son heaps.
 */

struct Nodo{
	int tam;
	Pedido pedido;
	Nodo* izq;
	Nodo* der;
};

struct ColaPedidosRepr{
	Nodo* raiz;
};

/**
 * @brief Crea una nueva cola.
 * @return ColaPedidos.
 */
ColaPedidos nuevaCP(){
	ColaPedidosRepr* cola = new ColaPedidosRepr;
	cola->raiz = NULL;
	return cola;
}

/**
 * @brief Devuelve la cantidad de pedidos en la cola.
 * @param ColaPedidos cp.
 * @return int.
 */
int tamCP(ColaPedidos cp){
    if (cp->raiz == NULL){
        return 0;
    }else{
        return cp->raiz->tam;
    }
}

/**
 * @brief Devuelve un nuevo nodo con un pedido.
 * @param Pedido p.
 * @return Nodo*.
 */
Nodo* nuevoNodo(Pedido p){
    Nodo* nodo = new Nodo;
    nodo->tam = 1;
    nodo->pedido = p;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

/**
 * @brief Elimina un nodo.
 * @param Nodo* nodo.
 * @return void.
 */
void destruirNodo(Nodo* nodo){
    if (nodo != NULL){
        destruirNodo(nodo->izq);
        destruirNodo(nodo->der);
        delete nodo;
    }
}

/**
 * @brief Devuelve true si p1 tiene mayor prioridad que p2.
 * @param Pedido p1.
 * @param Pedido p2.
 * @return bool.
 */
bool masPrioritario(Pedido p1, Pedido p2){
    return p1.fechaEntrega < p2.fechaEntrega ||
            (p1.fechaEntrega == p2.fechaEntrega && p1.persona < p2.persona);
}

/**
 * @brief Devuelve el pedido menos prioritario.
 * @param Pedido p1.
 * @param Pedido p2.
 * @return Pedido.
 */
Pedido pedidoMenosPrioritario(Pedido p1, Pedido p2){
    if (masPrioritario(p1,p2)){
        return p2;
    }else{
        return p1;
    }
}

/**
 * @brief Devuelve el pedido mas prioritario.
 * @param Pedido p1.
 * @param Pedido p2.
 * @return Pedido.
 */
Pedido pedidoMasPrioritario(Pedido p1, Pedido p2){
    if (masPrioritario(p1,p2)){
        return p1;
    }else{
        return p2;
    }
}

/**
 * @brief Intercambia los hijos de un nodo.
 * @param Nodo* nodo.
 * @return void.
 */
void intercambiarHijos(Nodo* nodo){
    Nodo* tmp = nodo->izq;
    nodo->izq = nodo->der;
    nodo->der = tmp;
}

/**
 * @brief Inserta un pedido en un nodo.
 * @pre nodo es un heap.
 * @param Nodo* nodo.
 * @param Pedido p.
 * @return Nodo*.
 */
Nodo* insertar(Nodo* nodo, Pedido p){
    if (nodo == NULL){
        return nuevoNodo(p);
    }
    Pedido menosPrioritario = pedidoMenosPrioritario(p, nodo->pedido);
    nodo->pedido = pedidoMasPrioritario(p, nodo->pedido);
    nodo->der = insertar(nodo->der, menosPrioritario);
    if (nodo->tam % 2 == 1){
        intercambiarHijos(nodo);
    }
    nodo->tam++;
    return nodo;
}

/**
 * @brief Encola un pedido.
 * @param ColaPedidos cp.
 * @param Pedido p.
 * @return void.
 */
void encolarCP(ColaPedidos cp, Pedido p){
	cp->raiz = insertar(cp->raiz, p);
}

/**
 * @brief Devuelve el pedido de la cola que tiene mayor prioridad.
 * @pre La cola no puede estar vacía (tamCP(cp) > 0).
 * @param ColaPedidos cp.
 * @return Pedido.
 */
Pedido proximoCP(ColaPedidos cp){
	return cp->raiz->pedido;
}

/**
 * @brief Elimina un pedido de un nodo.
 * @pre El nodo no puede estar vacía (es decir, tamCP(cp) > 0).
 *      El arbol cuya raiz es nodo es un arbol de Braun.
 * @param Nodo* nodo.
 * @param Pedido pedidoEliminado.
 * @return Nodo*.
 */
Nodo* eliminar(Nodo* nodo, Pedido& pedidoEliminado){
    if (nodo->tam == 1){
        pedidoEliminado = nodo->pedido;
        delete nodo;
        return NULL;
    }
    nodo->izq = eliminar(nodo->izq, pedidoEliminado);
    if (nodo->tam % 2 == 1){
        intercambiarHijos(nodo);
    }
    nodo->tam--;
    return nodo;
}

/**
 * @brief Devuelve true si el nodo tiene algun hijo con mayor prioridad.
 * @param Nodo* nodo.
 * @return bool.
 */
bool tieneHijoMasPrioritario(Nodo* nodo){
    return (nodo->izq != NULL && masPrioritario(nodo->izq->pedido, nodo->pedido))
        || (nodo->der != NULL && masPrioritario(nodo->der->pedido, nodo->pedido));
}

/**
 * @brief Devuelve el hijo mas prioritario de un nodo.
 * @param Nodo* nodo.
 * @return Nodo*.
 */
Nodo* hijoMasPrioritario(Nodo* nodo){
    if (nodo->der != NULL && masPrioritario(nodo->der->pedido, nodo->izq->pedido)){
        return nodo->der;
    }else{
        return nodo->izq;
    }
}

/**
 * @brief Devuelve el nodo resultante de intercambiarlo con su hijo mas prioritario.
 * @param Nodo* nodo.
 * @return Nodo*.
 */
Nodo* intercambiarConHijoMasPrioritario(Nodo* nodo){
    Nodo* otro = hijoMasPrioritario(nodo);
    Pedido tmp = otro->pedido;
    otro->pedido = nodo->pedido;
    nodo->pedido = tmp;
    return otro;
}

/**
 * @brief Baja la raiz mientras tenga menor prioridad que alguno de sus hijos.
 * @pre El nodo no es nulo.
 * @param Nodo* nodo.
 * @return void.
 */
void bajar(Nodo* nodo){
    Nodo* p = nodo;
    while (tieneHijoMasPrioritario(p)){
        p = intercambiarConHijoMasPrioritario(p);
    }
}

/**
 * @brief Libera toda la memoria reservada para la cola de prioridad.
 * @param ColaPedidos cp.
 * @return void.
 */
void destruirCP(ColaPedidos cp){
	destruirNodo(cp->raiz);
	cp->raiz = NULL;
}

/**
 * @brief Desencola el pedido de mayor prioridad.
 * @pre La cola no puede estar vacía (es decir, tamCP(cp) > 0).
 * @param ColaPedidos cp.
 * @return void.
 */
void desencolarCP(ColaPedidos cp){
    Pedido pedidoEliminado;
    cp->raiz = eliminar(cp->raiz, pedidoEliminado);
    if (tamCP(cp) > 0){
        cp->raiz->pedido = pedidoEliminado;
        bajar(cp->raiz);
    }
}
