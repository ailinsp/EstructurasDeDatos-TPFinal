//Ailin Patiño - Estructuras de Datos - Comision 1.

#include <cstdio>
#include "ColaPedidos.h"
#include "PapaNoel.h"

struct PapaNoelRepr {
	int fechaDeHoy;
	ColaPedidos pedidosFuturos;
	int cantPedidosDeHoy;
	Pedido* pedidosDeHoy;
};

/**
 * Devuelve un sistema nuevo.
 * @return PapaNoel.
 */
PapaNoel iniciarPN() {
    PapaNoel papaNoel = new PapaNoelRepr();
    papaNoel->fechaDeHoy = 0;
    papaNoel->pedidosFuturos = nuevaCP();
    papaNoel->cantPedidosDeHoy = 0;
    papaNoel->pedidosDeHoy = new Pedido[papaNoel->cantPedidosDeHoy];
    return papaNoel;
}

/**
 * Devuelve la fecha actual (la “fecha de hoy”) del sistema.
 * @param PapaNoel p.
 * @return Fecha.
 */
Fecha fechaActualPN(PapaNoel p) {
	return p->fechaDeHoy;
}

/**
 * Registra la solicitud de entregarle un regalo a la persona x cuando llegue la fecha f indicada.
 * @pre La fecha debe ser posterior a la fecha de hoy, es decir, f > fechaActualPN(p).
        La persona x no puede pedir más de un regalo para la misma fecha.
 * @param PapaNoel p.
 * @param Fecha f.
 * @param Id x.
 * @return void.
 */
void registrarPedidoPN(PapaNoel p, Fecha f, Id x) {
	Pedido pedido;
	pedido.persona = x;
	pedido.fechaEntrega = f;
	pedido.estado = Pendiente;
	encolarCP(p->pedidosFuturos, pedido);
}

/**
 * Devuelve el estado del pedido de la persona x en la fecha de hoy.
 * @param PapaNoel p
 * @param Id x,
 * @return Estado.
 */
Estado estadoPedidoPN(PapaNoel p, Id x) {
	// COMPLETAR
}

/**
 * Entrega un regalo a la persona x, con motivo de su buen comportamiento, cambiando su estado a Entregado.
 * @pre La persona tiene que tener un regalo pendiente para la fecha de hoy (estadoPedidoPN(p, x) == Pendiente).
 * @param PapaNoel p.
 * @param Id x.
 * @return void.
 */
void entregarPedidoPN(PapaNoel p, Id x) {
	// COMPLETAR
}

/**
 * Registra el mal comportamiento de la persona x, cambiando su estado a MalComportamiento.
 * @pre La persona tiene que tener un regalo pendiente para la fecha de hoy (estadoPedidoPN(p, x) == Pendiente).
 * @param PapaNoel p.
 * @param Id x.
 * @return void.
 */
void registrarMalComportamientoPN(PapaNoel p, Id x) {
	// COMPLETAR
}

/**
 * Cambia el estado de un pedido a Pendiente.
 * @param Pedido p.
 * @return Pedido.
 */
//cambia el estado de un pedido a Pendiente
Pedido pedidoConEstadoPendiente(Pedido p){
    p.estado = Pendiente;
    return p;
}

/**
 * Finaliza el día actual, incrementando la fecha de hoy en 1.
 * @pre No debe haber ninguna persona en estado Pendiente.
 * @param PapaNoel p.
 * @return void.
 */
void avanzarDiaPN(PapaNoel p) {
	int maxCapacidad = 16;
	delete [] p->pedidosDeHoy;
	p->fechaDeHoy++;

	Pedido pedido = proximoCP(p->pedidosFuturos);

	Pedido* arregloTemporal = new Pedido [maxCapacidad];
	int contador = 0;
	while(pedido.fechaEntrega == p->fechaDeHoy){
		if(contador == maxCapacidad){
			Pedido* nuevoArreglo = new Pedido[2*maxCapacidad];
			for(int i = 0; i < maxCapacidad; i++){
				nuevoArreglo[i] = arregloTemporal[i];
			}
		delete [] arregloTemporal;
		maxCapacidad = 2*maxCapacidad;
		}
	nuevoArreglo[contador] = pedidoConEstadoPendiente(pedido);
	pedido = proximoCP(p->pedidosFuturos);
	contador++;
	}
	p->pedidosDeHoy = nuevoArreglo;
	p->cantPedidosDeHoy = contador;
}

/**
 * Libera toda la memoria reservada para el sistema.
 * @param PapaNoel p.
 * @return void.
 */
void finalizarPN(PapaNoel p) {
	// COMPLETAR
}

