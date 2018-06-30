#ifndef PAPA_NOEL_H
#define PAPA_NOEL_H

#include "Tipos.h"

struct PapaNoelRepr;
typedef PapaNoelRepr* PapaNoel;

PapaNoel iniciarPN();

Fecha fechaActualPN(PapaNoel p);

void registrarPedidoPN(PapaNoel p, Fecha f, Id x);

Estado estadoPedidoPN(PapaNoel p, Id x);

void entregarPedidoPN(PapaNoel p, Id x);

void registrarMalComportamientoPN(PapaNoel p, Id x);

void avanzarDiaPN(PapaNoel p);

void finalizarPN(PapaNoel p);

#endif
