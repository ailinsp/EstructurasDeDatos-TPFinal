//Ailin Patiño - Estructuras de Datos - Comision 1.

#include <cstdio>
#include "ColaPedidos.h"

struct Nodo {
	int tam;
	Pedido pedido;
	Nodo* izq;
	Nodo* der;
};

struct ColaPedidosRepr {
	Nodo* raiz;
};

/**
 * Crea una nueva cola.
 * @return ColaPedidos.
 */
ColaPedidos nuevaCP() {
	ColaPedidosRepr* cola = new ColaPedidosRepr;
	cola->raiz = NULL;
	return cola;
}

/**
 * Devuelve la cantidad de pedidos en la cola.
 * @param ColaPedidos cp.
 * @return int.
 */
int tamCP(ColaPedidos cp) {
    if(cp->raiz == NULL){
        return 0;
    }else{
        return cp->raiz->tam;
    }
}

/**
 * Devuelve un nuevo nodo con un pedido.
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
 * Devuelve true si p1 tiene mayor prioridad que p2.
 * @param Pedido p1.
 * @param Pedido p2.
 * @return bool.
 */
bool masPrioritario(Pedido p1, Pedido p2){
    return p1.fechaEntrega < p2.fechaEntrega ||
            (p1.fechaEntrega == p2.fechaEntrega && p1.persona < p2.persona);
}

/**
 * Devuelve el pedido menos prioritario.
 * @param Pedido p1.
 * @param Pedido p2.
 * @return Pedido.
 */
Pedido pedidoMenosPrioritario(Pedido p1, Pedido p2){
        if(masPrioritario(p1,p2)){
            return p2;
        }else{
            return p1;
        }
}

//ACA REPITO CODIGO REVISAR.
/**
 * Devuelve el pedido mas prioritario.
 * @param Pedido p1.
 * @param Pedido p2.
 * @return Pedido.
 */
Pedido pedidoMasPrioritario(Pedido p1, Pedido p2){
    if(masPrioritario(p1,p2)){
            return p1;
        }else{
            return p2;
        }
}

/**
 * Inserta un pedido en un nodo.
 * @pre nodo es un Braun heap.
 * @param Nodo* nodo.
 * @param Pedido p.
 * @return Nodo*.
 */
Nodo* insertar(Nodo* nodo, Pedido p){
    if(nodo == NULL){
        return nuevoNodo(p);
    }else{
        Pedido menosPrioritario = pedidoMenosPrioritario(p, nodo->pedido);
        nodo->pedido = pedidoMasPrioritario(p, nodo->pedido);
        nodo->der = insertar(nodo->der, menosPrioritario);
        if(nodo->tam % 2 == 1){
            Nodo* tmp = nodo->izq;
            nodo->izq = nodo->der;
            nodo->der = tmp;
        }
    nodo->tam++;
    return nodo;
    }
}

/**
 * Encola un pedido.
 * @param ColaPedidos cp.
 * @param Pedido p.
 * @return void.
 */
void encolarCP(ColaPedidos cp, Pedido p) {
	cp->raiz = insertar(cp->raiz, p);
}

/**
 * Devuelve el pedido de la cola que tiene mayor prioridad.
 * @pre La cola no puede estar vacía (tamCP(cp) > 0).
 * @param ColaPedidos cp.
 * @return Pedido.
 */
Pedido proximoCP(ColaPedidos cp) {
	return cp->raiz->pedido;
}


/**
 * Elimina un nodo.
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
 * Libera toda la memoria reservada para la cola de prioridad.
 * @param ColaPedidos cp.
 * @return void.
 */
void destruirCP(ColaPedidos cp) {
	destruirNodo(cp->raiz);
	cp->raiz = NULL;
}

/**
 * Elimina un pedido de un nodo.
 * @pre El nodo no puede estar vacía (es decir, tamCP(cp) > 0).
 *      El arbol cuya raiz es nodo es un arbol de Braun.
 * @param Nodo* nodo.
 * @param Pedido pedidoEliminado.
 * @return Nodo*.
 */
Nodo* eliminarNodo(Nodo* nodo, Pedido& pedidoEliminado){
    if(nodo->tam == 1){
        pedidoEliminado = nodo->pedido;
        delete nodo;
        return NULL;
    }else{
        nodo->izq = eliminarNodo(nodo->izq, pedidoEliminado);
        if(nodo->tam % 2 == 1){
            Nodo* tmp = nodo->izq;
            nodo->izq = nodo->der;
            nodo->der = tmp;
        }
        nodo->tam--;
        return nodo;
    }
}

/**
 * Devuelve true si el nodo tiene algun hijo mayor.
 * @param Nodo* nodo.
 * @return bool.
 */
bool tienePedidoMasPrioritario(Nodo* nodo){
    return (nodo->izq != NULL && masPrioritario(nodo->izq->pedido, nodo->pedido))
        || (nodo->der != NULL && masPrioritario(nodo->der->pedido, nodo->pedido));
}

/**
 * Devuelve el hijo mayor de un nodo.
 * @param Nodo* nodo.
 * @return Nodo*.
 */
Nodo* nodoMasPrioritario(Nodo* nodo){
    if(nodo->der != NULL && masPrioritario(nodo->der->pedido, nodo->izq->pedido)){
        return nodo->der;
    }else{
        return nodo->izq;
    }
}

/**
 * Intercambia un nodo con su hijo mayor.
 * @param Nodo* nodo.
 * @return void.
 */
void intercambiarConPedidoMasPrioritario(Nodo* nodo){
    Nodo* otro = nodoMasPrioritario(nodo);
    Pedido tmp = otro->pedido;
    otro->pedido = nodo->pedido;
    nodo->pedido = tmp;
}

/**
 * Baja la raiz mientras la tenga menor prioridad que alguno de sus hijos.
 * @pre El nodo no es nulo.
 * @param Nodo* nodo.
 * @return void.
 */
void bajar(Nodo* nodo){
    Nodo* n = nodo;
    while(tienePedidoMasPrioritario(n)){
        intercambiarConPedidoMasPrioritario(n);
        n = nodoMasPrioritario(n);
    }
}

/**
 * Desencola el pedido de mayor prioridad.
 * @pre La cola no puede estar vacía (es decir, tamCP(cp) > 0).
 * @param ColaPedidos cp.
 * @return void.
 */
void desencolarCP(ColaPedidos cp){
    Pedido pedidoEliminado;
    cp->raiz = eliminarNodo(cp->raiz, pedidoEliminado);
    if(tamCP(cp) > 0){
        cp->raiz->pedido = pedidoEliminado;
        bajar(cp->raiz);
    }
}

