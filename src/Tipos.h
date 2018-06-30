#ifndef TIPOS_H
#define TIPOS_H

typedef int Fecha;
typedef int Id;

typedef int Estado;

const Estado Inexistente       = 0;
const Estado Pendiente         = 1;
const Estado Entregado         = 2;
const Estado MalComportamiento = 3;

struct Pedido {
	Id persona;
	Fecha fechaEntrega;
	Estado estado;
};

#endif
