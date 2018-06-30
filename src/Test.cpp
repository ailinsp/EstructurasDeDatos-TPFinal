#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

#define TEST(NOMBRE, CUERPO) \
	void NOMBRE() { \
		string test = #NOMBRE; \
		cout << "[ TEST   ] " << test << endl; \
		{ CUERPO } \
		cout << "[     OK ] " << test << endl; \
	}

#define ASSERT_EQ(EXPR, EXPECTED) { \
	__typeof__(EXPECTED) expected = (EXPECTED); \
	__typeof__(EXPR) obtained = (EXPR); \
	if (expected != obtained) { \
		cout << "[    MAL ] " << test << endl; \
		cout << endl; \
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl; \
		cout << "FALLA EL TEST \"" << test << "\"" << endl; \
		cout << "Al evaluar:" << endl; \
		cout << "    " << #EXPR << endl; \
		cout << "Se esperaba obtener el valor:" << endl; \
		cout << "    " << expected << endl; \
		cout << "Pero se obtuvo:" << endl; \
		cout << "    " << obtained << endl; \
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl; \
		exit(1); \
	} \
}

/* Tests de ColaPedidos */

#include "ColaPedidos.h"

TEST(testColaVacia, {
	ColaPedidos cp = nuevaCP();
	ASSERT_EQ(tamCP(cp), 0);
	destruirCP(cp);
})

TEST(testColaInsertar1, {
	ColaPedidos cp = nuevaCP();

	Pedido p;
	p.persona = 1000;
	p.fechaEntrega = 99;
	p.estado = Entregado;

	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p);
	ASSERT_EQ(tamCP(cp), 1);

	Pedido q = proximoCP(cp);
	ASSERT_EQ(q.persona, 1000);
	ASSERT_EQ(q.fechaEntrega, 99);
	ASSERT_EQ(q.estado, Entregado);

	destruirCP(cp);
})

TEST(testColaInsertarFechaMayor, {
	ColaPedidos cp = nuevaCP();

	Pedido p1;
	p1.persona = 9876;
	p1.fechaEntrega = 45;
	p1.estado = Entregado;

	Pedido p2;
	p2.persona = 1234;
	p2.fechaEntrega = 46;
	p2.estado = MalComportamiento;

	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 2);

	Pedido q = proximoCP(cp);
	ASSERT_EQ(q.persona, 9876);
	ASSERT_EQ(q.fechaEntrega, 45);
	ASSERT_EQ(q.estado, Entregado);

	destruirCP(cp);
})

TEST(testColaInsertarFechaMenor, {
	ColaPedidos cp = nuevaCP();

	Pedido p1;
	p1.persona = 9876;
	p1.fechaEntrega = 45;
	p1.estado = Entregado;

	Pedido p2;
	p2.persona = 1234;
	p2.fechaEntrega = 46;
	p2.estado = MalComportamiento;

	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 2);

	Pedido q = proximoCP(cp);
	ASSERT_EQ(q.persona, 9876);
	ASSERT_EQ(q.fechaEntrega, 45);
	ASSERT_EQ(q.estado, Entregado);

	destruirCP(cp);
})

TEST(testColaInsertarFechaIgualPersonaMayor, {
	ColaPedidos cp = nuevaCP();

	Pedido p1;
	p1.persona = 1234;
	p1.fechaEntrega = 11;
	p1.estado = Pendiente;

	Pedido p2;
	p2.persona = 9876;
	p2.fechaEntrega = 11;
	p2.estado = MalComportamiento;

	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 2);

	Pedido q = proximoCP(cp);
	ASSERT_EQ(q.persona, 1234);
	ASSERT_EQ(q.fechaEntrega, 11);
	ASSERT_EQ(q.estado, Pendiente);

	destruirCP(cp);
})

TEST(testColaInsertarFechaIgualPersonaMenor, {
	ColaPedidos cp = nuevaCP();

	Pedido p1;
	p1.persona = 1234;
	p1.fechaEntrega = 11;
	p1.estado = MalComportamiento;

	Pedido p2;
	p2.persona = 9876;
	p2.fechaEntrega = 11;
	p2.estado = Entregado;

	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 2);

	Pedido q = proximoCP(cp);
	ASSERT_EQ(q.persona, 1234);
	ASSERT_EQ(q.fechaEntrega, 11);
	ASSERT_EQ(q.estado, MalComportamiento);

	destruirCP(cp);
})

TEST(testColaInsertarBorrar1, {
	ColaPedidos cp = nuevaCP();

	Pedido p;
	p.persona = 1000;
	p.fechaEntrega = 99;
	p.estado = Entregado;

	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p);
	ASSERT_EQ(tamCP(cp), 1);

	Pedido q = proximoCP(cp);
	ASSERT_EQ(q.persona, 1000);
	ASSERT_EQ(q.fechaEntrega, 99);
	ASSERT_EQ(q.estado, Entregado);

	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 0);

	destruirCP(cp);
})

TEST(testColaInsertarBorrar123, {
	Pedido p1;
	p1.persona = 111;
	p1.fechaEntrega = 11;
	p1.estado = Entregado;

	Pedido p2;
	p2.persona = 222;
	p2.fechaEntrega = 22;
	p2.estado = Entregado;

	Pedido p3;
	p3.persona = 333;
	p3.fechaEntrega = 33;
	p3.estado = MalComportamiento;

	ColaPedidos cp = nuevaCP();
	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 2);
	encolarCP(cp, p3);
	ASSERT_EQ(tamCP(cp), 3);
	ASSERT_EQ(proximoCP(cp).persona, 111);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 2);
	ASSERT_EQ(proximoCP(cp).persona, 222);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 1);
	ASSERT_EQ(proximoCP(cp).persona, 333);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 0);
	destruirCP(cp);
})

TEST(testColaInsertarBorrar132, {
	Pedido p1;
	p1.persona = 111;
	p1.fechaEntrega = 11;
	p1.estado = Entregado;

	Pedido p2;
	p2.persona = 222;
	p2.fechaEntrega = 22;
	p2.estado = Entregado;

	Pedido p3;
	p3.persona = 333;
	p3.fechaEntrega = 33;
	p3.estado = MalComportamiento;

	ColaPedidos cp = nuevaCP();
	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p3);
	ASSERT_EQ(tamCP(cp), 2);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 3);
	ASSERT_EQ(proximoCP(cp).persona, 111);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 2);
	ASSERT_EQ(proximoCP(cp).persona, 222);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 1);
	ASSERT_EQ(proximoCP(cp).persona, 333);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 0);
	destruirCP(cp);
})

TEST(testColaInsertarBorrar213, {
	Pedido p1;
	p1.persona = 111;
	p1.fechaEntrega = 11;
	p1.estado = Entregado;

	Pedido p2;
	p2.persona = 222;
	p2.fechaEntrega = 22;
	p2.estado = Entregado;

	Pedido p3;
	p3.persona = 333;
	p3.fechaEntrega = 33;
	p3.estado = MalComportamiento;

	ColaPedidos cp = nuevaCP();
	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 2);
	encolarCP(cp, p3);
	ASSERT_EQ(tamCP(cp), 3);
	ASSERT_EQ(proximoCP(cp).persona, 111);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 2);
	ASSERT_EQ(proximoCP(cp).persona, 222);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 1);
	ASSERT_EQ(proximoCP(cp).persona, 333);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 0);
	destruirCP(cp);
})

TEST(testColaInsertarBorrar231, {
	Pedido p1;
	p1.persona = 111;
	p1.fechaEntrega = 11;
	p1.estado = Entregado;

	Pedido p2;
	p2.persona = 222;
	p2.fechaEntrega = 22;
	p2.estado = Entregado;

	Pedido p3;
	p3.persona = 333;
	p3.fechaEntrega = 33;
	p3.estado = MalComportamiento;

	ColaPedidos cp = nuevaCP();
	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p3);
	ASSERT_EQ(tamCP(cp), 2);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 3);
	ASSERT_EQ(proximoCP(cp).persona, 111);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 2);
	ASSERT_EQ(proximoCP(cp).persona, 222);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 1);
	ASSERT_EQ(proximoCP(cp).persona, 333);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 0);
	destruirCP(cp);
})

TEST(testColaInsertarBorrar312, {
	Pedido p1;
	p1.persona = 111;
	p1.fechaEntrega = 11;
	p1.estado = Entregado;

	Pedido p2;
	p2.persona = 222;
	p2.fechaEntrega = 22;
	p2.estado = Entregado;

	Pedido p3;
	p3.persona = 333;
	p3.fechaEntrega = 33;
	p3.estado = MalComportamiento;

	ColaPedidos cp = nuevaCP();
	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p3);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 2);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 3);
	ASSERT_EQ(proximoCP(cp).persona, 111);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 2);
	ASSERT_EQ(proximoCP(cp).persona, 222);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 1);
	ASSERT_EQ(proximoCP(cp).persona, 333);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 0);
	destruirCP(cp);
})

TEST(testColaInsertarBorrar321, {
	Pedido p1;
	p1.persona = 111;
	p1.fechaEntrega = 11;
	p1.estado = Entregado;

	Pedido p2;
	p2.persona = 222;
	p2.fechaEntrega = 22;
	p2.estado = Entregado;

	Pedido p3;
	p3.persona = 333;
	p3.fechaEntrega = 33;
	p3.estado = MalComportamiento;

	ColaPedidos cp = nuevaCP();
	ASSERT_EQ(tamCP(cp), 0);
	encolarCP(cp, p3);
	ASSERT_EQ(tamCP(cp), 1);
	encolarCP(cp, p2);
	ASSERT_EQ(tamCP(cp), 2);
	encolarCP(cp, p1);
	ASSERT_EQ(tamCP(cp), 3);
	ASSERT_EQ(proximoCP(cp).persona, 111);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 2);
	ASSERT_EQ(proximoCP(cp).persona, 222);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 1);
	ASSERT_EQ(proximoCP(cp).persona, 333);
	desencolarCP(cp);
	ASSERT_EQ(tamCP(cp), 0);
	destruirCP(cp);
})

void siguientePermutacion(vector<Pedido>& vec, int i) {
	int p = 1;
	while (i > 0 && i % (p + 1) == 0) {
        	p++;
        	i /= p;
	}
	swap(vec.at(0), vec.at(p));
}

const int MAX_T = 8;

TEST(testColaInsertarBorrarPermutaciones, {
	// Encola y desencola probando todas las permutaciones
	// posibles de t elementos para t = 1..MAX_T.
	for (int t = 1; t <= MAX_T; t++) {
		vector<Pedido> v;
		int t_factorial = 1;
		for (int i = 1; i <= t; i++) {
			Pedido p;
			p.fechaEntrega = i / 2;
			p.persona = i % 2;
			p.estado = i % 4;
			v.push_back(p);
			t_factorial *= i;
		}
		for (int i = 0; i < t_factorial; i++) {
			if (i > 0) {
				siguientePermutacion(v, i);
			}
			ColaPedidos cp = nuevaCP();
			for (int j = 0; j < t; j++) {
				ASSERT_EQ(tamCP(cp), j);
				encolarCP(cp, v[j]);
				ASSERT_EQ(tamCP(cp), j + 1);
			}
			for (int j = 1; j <= t; j++) {
				Pedido q = proximoCP(cp);
				ASSERT_EQ(q.fechaEntrega, j / 2);
				ASSERT_EQ(q.persona, j % 2);
				ASSERT_EQ(q.estado, j % 4);
				ASSERT_EQ(tamCP(cp), t - j + 1);
				desencolarCP(cp);
				ASSERT_EQ(tamCP(cp), t - j);
			}
			destruirCP(cp);
		}
	}
})

void correrTestsColaPedidos() {
	cout << "[========] Testeando el tipo ColaPedidos." << endl;
	testColaVacia();
	testColaInsertar1();
	testColaInsertarFechaMayor();
	testColaInsertarFechaMenor();
	testColaInsertarFechaIgualPersonaMayor();
	testColaInsertarFechaIgualPersonaMenor();
	testColaInsertarBorrar1();
	testColaInsertarBorrar123();
	testColaInsertarBorrar132();
	testColaInsertarBorrar213();
	testColaInsertarBorrar231();
	testColaInsertarBorrar312();
	testColaInsertarBorrar321();
	testColaInsertarBorrarPermutaciones();
	cout << "[========] Todos los tests de ColaPedidos OK." << endl;
}

/* Tests de PapaNoel */

#include "PapaNoel.h"

TEST(testPapaNoelIniciar, {
	PapaNoel p = iniciarPN();
	ASSERT_EQ(fechaActualPN(p), 0);
	finalizarPN(p);
})

TEST(testPapaNoelBuscarPersonaEnFecha0, {
	PapaNoel p = iniciarPN();
	ASSERT_EQ(estadoPedidoPN(p, 11), Inexistente);
	finalizarPN(p);
})

TEST(testPapaNoelBuscarPersonaEnFecha1, {
	PapaNoel p = iniciarPN();
	registrarPedidoPN(p, 1, 15);
	registrarPedidoPN(p, 2, 25);
	registrarPedidoPN(p, 1, 19);
	registrarPedidoPN(p, 2, 29);
	registrarPedidoPN(p, 1, 11);
	registrarPedidoPN(p, 2, 21);
	ASSERT_EQ(estadoPedidoPN(p, 11), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 21), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 25), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Inexistente);
	ASSERT_EQ(fechaActualPN(p), 0);
	avanzarDiaPN(p);
	ASSERT_EQ(fechaActualPN(p), 1);
	ASSERT_EQ(estadoPedidoPN(p, 11), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 21), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 25), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Inexistente);
	finalizarPN(p);
})

TEST(testPapaNoelPedidos, {
	PapaNoel p = iniciarPN();
	registrarPedidoPN(p, 1, 15);
	registrarPedidoPN(p, 2, 25);
	registrarPedidoPN(p, 1, 19);
	registrarPedidoPN(p, 2, 29);
	registrarPedidoPN(p, 1, 11);
	registrarPedidoPN(p, 2, 21);
	ASSERT_EQ(estadoPedidoPN(p, 11), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 21), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 25), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Inexistente);
	ASSERT_EQ(fechaActualPN(p), 0);
	avanzarDiaPN(p);
	ASSERT_EQ(fechaActualPN(p), 1);
	ASSERT_EQ(estadoPedidoPN(p, 11), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 21), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 25), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Inexistente);
	entregarPedidoPN(p, 19);
	ASSERT_EQ(estadoPedidoPN(p, 11), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Entregado);
	ASSERT_EQ(estadoPedidoPN(p, 21), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 25), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Inexistente);
	entregarPedidoPN(p, 11);
	ASSERT_EQ(estadoPedidoPN(p, 11), Entregado);
	ASSERT_EQ(estadoPedidoPN(p, 15), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Entregado);
	ASSERT_EQ(estadoPedidoPN(p, 21), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 25), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Inexistente);
	registrarMalComportamientoPN(p, 15);
	ASSERT_EQ(estadoPedidoPN(p, 11), Entregado);
	ASSERT_EQ(estadoPedidoPN(p, 15), MalComportamiento);
	ASSERT_EQ(estadoPedidoPN(p, 19), Entregado);
	ASSERT_EQ(estadoPedidoPN(p, 21), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 25), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Inexistente);
	ASSERT_EQ(fechaActualPN(p), 1);
	avanzarDiaPN(p);
	ASSERT_EQ(fechaActualPN(p), 2);
	ASSERT_EQ(estadoPedidoPN(p, 11), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 21), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 25), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Pendiente);
	registrarMalComportamientoPN(p, 21);
	ASSERT_EQ(estadoPedidoPN(p, 11), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 21), MalComportamiento);
	ASSERT_EQ(estadoPedidoPN(p, 25), Pendiente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Pendiente);
	registrarMalComportamientoPN(p, 25);
	ASSERT_EQ(estadoPedidoPN(p, 11), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 21), MalComportamiento);
	ASSERT_EQ(estadoPedidoPN(p, 25), MalComportamiento);
	ASSERT_EQ(estadoPedidoPN(p, 29), Pendiente);
	entregarPedidoPN(p, 29);
	ASSERT_EQ(estadoPedidoPN(p, 11), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 21), MalComportamiento);
	ASSERT_EQ(estadoPedidoPN(p, 25), MalComportamiento);
	ASSERT_EQ(estadoPedidoPN(p, 29), Entregado);
	ASSERT_EQ(fechaActualPN(p), 2);
	avanzarDiaPN(p);
	ASSERT_EQ(fechaActualPN(p), 3);
	ASSERT_EQ(estadoPedidoPN(p, 11), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 15), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 19), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 21), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 25), Inexistente);
	ASSERT_EQ(estadoPedidoPN(p, 29), Inexistente);
	finalizarPN(p);
})

TEST(testPapaNoelPedidosSaltearFechas, {
	PapaNoel p = iniciarPN();
	for (int i = 1; i <= 1000; i++) {
		if (i % 2 == 0) {
			registrarPedidoPN(p, i, 99);
		}
	}
	for (int i = 1; i <= 1000; i++) {
		ASSERT_EQ(fechaActualPN(p), i - 1);
		avanzarDiaPN(p);
		ASSERT_EQ(fechaActualPN(p), i);
		if (i % 2 == 0) {
			ASSERT_EQ(estadoPedidoPN(p, 99), Pendiente);
			entregarPedidoPN(p, 99);
			ASSERT_EQ(estadoPedidoPN(p, 99), Entregado);
		} else {
			ASSERT_EQ(estadoPedidoPN(p, 99), Inexistente);
		}
	}
	finalizarPN(p);
})

TEST(testPapaNoel10000Pedidos, {
	const int CANT = 10000;
	PapaNoel p = iniciarPN();
	for (int i = 1; i <= CANT; i++) {
		registrarPedidoPN(p, 1, i);
	}
	avanzarDiaPN(p);
	ASSERT_EQ(fechaActualPN(p), 1);
	for (int i = 1; i <= CANT; i++) {
		ASSERT_EQ(estadoPedidoPN(p, i), Pendiente);
	}
	for (int i = 1; i <= CANT; i++) {
		ASSERT_EQ(estadoPedidoPN(p, i), Pendiente);
		if (i % 3 == 0) {
			entregarPedidoPN(p, i);
		} else {
			registrarMalComportamientoPN(p, i);
		}
	}
	for (int i = 1; i <= CANT; i++) {
		if (i % 3 == 0) {
			ASSERT_EQ(estadoPedidoPN(p, i), Entregado);
		} else {
			ASSERT_EQ(estadoPedidoPN(p, i), MalComportamiento);
		}
	}
	avanzarDiaPN(p);
	ASSERT_EQ(fechaActualPN(p), 2);
	finalizarPN(p);
})

TEST(testPapaNoel100x100Pedidos, {
	const int CANT_PERSONAS = 100;
	const int CANT_FECHAS = 100;
	PapaNoel p = iniciarPN();
	for (int j = 1; j <= CANT_PERSONAS; j++) {
		for (int i = 1; i <= CANT_FECHAS; i++) {
			registrarPedidoPN(p, i, j);
		}
	}
	for (int j = 1; j <= CANT_PERSONAS; j++) {
		ASSERT_EQ(estadoPedidoPN(p, j), Inexistente);
	}
	for (int i = 1; i <= CANT_FECHAS; i++) {
		avanzarDiaPN(p);
		ASSERT_EQ(fechaActualPN(p), i);
		for (int j = 1; j <= CANT_PERSONAS; j++) {
			ASSERT_EQ(estadoPedidoPN(p, j), Pendiente);
		}
		for (int j = 1; j <= CANT_PERSONAS; j++) {
			if ((i + j) % 3 == 1) {
				entregarPedidoPN(p, j);
			} else {
				registrarMalComportamientoPN(p, j);
			}
		}
		for (int j = 1; j <= CANT_PERSONAS; j++) {
			if ((i + j) % 3 == 1) {
				ASSERT_EQ(estadoPedidoPN(p, j), Entregado);
			} else {
				ASSERT_EQ(estadoPedidoPN(p, j), MalComportamiento);
			}
		}
	}
	finalizarPN(p);
})

void correrTestsPapaNoel() {
	cout << "[========] Testeando el tipo PapaNoel." << endl;
	testPapaNoelIniciar();
	testPapaNoelBuscarPersonaEnFecha0();
	testPapaNoelBuscarPersonaEnFecha1();
	testPapaNoelPedidos();
	testPapaNoelPedidosSaltearFechas();
	testPapaNoel10000Pedidos();
	testPapaNoel100x100Pedidos();
	cout << "[========] Todos los tests de PapaNoel OK." << endl;
}

