#ifndef COLA_PEDIDOS_H
#define COLA_PEDIDOS_H

#include "Tipos.h"

struct ColaPedidosRepr;
typedef ColaPedidosRepr* ColaPedidos;

ColaPedidos nuevaCP();

int tamCP(ColaPedidos cp);

void encolarCP(ColaPedidos cp, Pedido p);

Pedido proximoCP(ColaPedidos cp);

void desencolarCP(ColaPedidos cp);

void destruirCP(ColaPedidos cp);

#endif
