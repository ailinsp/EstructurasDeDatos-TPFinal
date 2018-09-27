//Ailin Patiño - Estructuras de Datos - Comision 1.

#include <cstdio>
#include "ColaPedidos.h"
#include "PapaNoel.h"

/**
 * Invariante de representacion.
 *
 * La fecha de hoy es un entero no negativo (fechaDeHoy >= 0).
 * Todos los pedidos en la cola pedidosFuturos tienen fecha de entrega posterior a fechaDeHoy.
 * Todos los pedidos en la cola pedidosFuturos tienen estado Pendiente.
 * En la cola pedidosFuturos no puede haber dos pedidos para la misma persona con la misma fecha de entrega.
 * El puntero pedidosDeHoy apunta a un arreglo con capacidad para almacenar al menos cantPedidosDeHoy elementos.
 * Todos los pedidos del arreglo pedidosDeHoy tienen fecha de entrega igual a fechaDeHoy.
 * Todos los pedidos del arreglo pedidosDeHoy tienen estado Pendiente, Entregado o MalComportamiento (pero no pueden tener estado Inexistente).
 * Los pedidos del arreglo pedidosDeHoy se encuentran ordenados de menor a mayor por el identificador de la persona correspondiente.
 */

struct PapaNoelRepr{
	int fechaDeHoy;
	ColaPedidos pedidosFuturos;
	int cantPedidosDeHoy;
	Pedido* pedidosDeHoy;
};

/**
 * @brief Devuelve un sistema nuevo.
 * @return PapaNoel.
 */
PapaNoel iniciarPN(){
    PapaNoel papaNoel = new PapaNoelRepr();
    papaNoel->fechaDeHoy = 0;
    papaNoel->pedidosFuturos = nuevaCP();
    papaNoel->cantPedidosDeHoy = 0;
    papaNoel->pedidosDeHoy = new Pedido[1];
    return papaNoel;
}

/**
 * @brief Devuelve la fecha actual (la “fecha de hoy”) del sistema.
 * @param PapaNoel p.
 * @return Fecha.
 */
Fecha fechaActualPN(PapaNoel p){
	return p->fechaDeHoy;
}

/**
 * @brief Registra la solicitud de entregarle un regalo a la persona x cuando llegue la fecha f indicada.
 * @pre La fecha debe ser posterior a la fecha de hoy, es decir, f > fechaActualPN(p).
 *      La persona x no puede pedir más de un regalo para la misma fecha.
 * @param PapaNoel p.
 * @param Fecha f.
 * @param Id x.
 * @return void.
 */
void registrarPedidoPN(PapaNoel p, Fecha f, Id x){
	Pedido pedido;
	pedido.persona = x;
	pedido.fechaEntrega = f;
	pedido.estado = Pendiente;
	encolarCP(p->pedidosFuturos, pedido);
}

/**
 * @brief Devuelve el estado del pedido de la persona x en la fecha de hoy.
 * @param PapaNoel p.
 * @param Id x.
 * @return Estado.
 */
Estado estadoPedidoPN(PapaNoel p, Id x){
    if (p->cantPedidosDeHoy == 0){
        return Inexistente;
    }
    Pedido* a =  p->pedidosDeHoy;
    int first = 0;
    int middle;
    int last = p->cantPedidosDeHoy - 1;

    while (first <= last){
        middle = (first + last) / 2;
        if (x == a[middle].persona){
            return a[middle].estado;
        }else{
            if (a[middle].persona > x){
                last = middle - 1;
            }else{
                first = middle + 1;
            }
        }
    }
    return Inexistente;
}

/**
 * @brief Cambia el estado de un pedido al pasado por parametro.
 * @param Pedido p.
 * @param Estado e.
 * @return Pedido.
 */
Pedido cambiarEstadoDePedido(Pedido p, Estado e){
    p.estado = e;
    return p;
}

/**
 * @brief Cambia el estado de un pedido asociado a una id.
 * @param PapaNoel p.
 * @param Estado e.
 * @param Id x.
 * @return void.
 */
void cambiarEstadoDePedidoPorId(PapaNoel p, Estado e, Id x){
    Pedido* a = p->pedidosDeHoy;
    int first = 0;
    int middle;
    int last = p->cantPedidosDeHoy - 1;

    while (first <= last){
        middle = (first + last) / 2;
        if (x == a[middle].persona){
            a[middle] = cambiarEstadoDePedido(a[middle], e);
            break;
        }else{
            if (a[middle].persona > x){
                last = middle - 1;
            }else{
                first = middle + 1;
            }
        }
    }
}

/**
 * @brief Entrega un regalo a la persona x, cambiando su estado a Entregado.
 * @pre La persona tiene que tener un regalo pendiente para la fecha de hoy (estadoPedidoPN(p, x) == Pendiente).
 * @param PapaNoel p.
 * @param Id x.
 * @return void.
 */
void entregarPedidoPN(PapaNoel p, Id x) {
    cambiarEstadoDePedidoPorId(p, Entregado, x);
}

/**
 * @brief Registra el mal comportamiento de la persona x, cambiando su estado a MalComportamiento.
 * @pre La persona tiene que tener un regalo pendiente para la fecha de hoy (estadoPedidoPN(p, x) == Pendiente).
 * @param PapaNoel p.
 * @param Id x.
 * @return void.
 */
void registrarMalComportamientoPN(PapaNoel p, Id x) {
    cambiarEstadoDePedidoPorId(p, MalComportamiento, x);
}

/**
 * @brief Duplica el tamaño de un arreglo.
 * @param Pedido*& arreglo.
 * @param int capacidad.
 * @return void.
 */
void duplicarLongitud(Pedido*& arreglo, int capacidad){
    Pedido* arregloTemporal = new Pedido[2*capacidad];
    for (int i = 0; i < capacidad; i++){
        arregloTemporal[i] = arreglo[i];
    }
    delete [] arreglo;
    arreglo = arregloTemporal;
}

/**
 * @brief Finaliza el dia actual, incrementando la fecha de hoy en 1.
 * @pre No debe haber ninguna persona en estado Pendiente.
 * @param PapaNoel p.
 * @return void.
 */
void avanzarDiaPN(PapaNoel p){
    delete [] p->pedidosDeHoy;
    p->cantPedidosDeHoy = 0;
    p->fechaDeHoy++;
    int maxCapacidad = 16;
    Pedido* nuevoArreglo = new Pedido[maxCapacidad];
    int contador = 0;

    while (tamCP(p->pedidosFuturos) > 0 &&
                proximoCP(p->pedidosFuturos).fechaEntrega == p->fechaDeHoy){
        Pedido pedido = proximoCP(p->pedidosFuturos);
        nuevoArreglo[contador] = cambiarEstadoDePedido(pedido, Pendiente);
        desencolarCP(p->pedidosFuturos);
        contador++;
        if (contador == maxCapacidad){
            duplicarLongitud(nuevoArreglo, maxCapacidad);
            maxCapacidad = 2*maxCapacidad;
        }
    }
    p->pedidosDeHoy = nuevoArreglo;
    p->cantPedidosDeHoy = contador;
}

/**
 * @brief Libera toda la memoria reservada para el sistema.
 * @param PapaNoel p.
 * @return void.
 */
void finalizarPN(PapaNoel p){
    delete[] p->pedidosDeHoy;
    destruirCP(p->pedidosFuturos);
    delete p;
}
