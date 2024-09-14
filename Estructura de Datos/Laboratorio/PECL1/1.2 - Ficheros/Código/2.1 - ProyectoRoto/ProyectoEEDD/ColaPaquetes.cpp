#include "ColaPaquetes.hpp"

ColaPaquetes::Nodo::Nodo()
{
	paquete = Paquete();
	siguiente = nullptr;
}

ColaPaquetes::Nodo::Nodo(Paquete p, Nodo* sig)
{
	paquete = p;
	siguiente = sig;
}



ColaPaquetes::Nodo::~Nodo()
{
}

ColaPaquetes::ColaPaquetes()
{
	frente_ = NULL;
	final_ = NULL;
}

ColaPaquetes::~ColaPaquetes()
{
	while (frente_) {
		desencolar();
	}
}

void ColaPaquetes::encolar(Paquete p)
{
	Nodo* nuevo = new Nodo(p); // Se crea un nodo nuevo
	// Si cola no vacia, se annade el nuevo a continuacion del ultimo
	if (final_) {
		final_->siguiente = nuevo;
	}
	// El ultimo elemento de la cola es el nuevo nodo
	final_ = nuevo;
	// Si frente es NULL, la cola esta vacia y el nuevo nodo pasa a ser el primero
	if (!frente_) {
		frente_ = nuevo;
	}
}

Paquete ColaPaquetes::desencolar()
{
	Nodo* nodo; // Variable auxiliar para manipular nodo
	Paquete p; // Variable auxiliar para retorno del valor
	// Nodo apunta al primer elemento de la cola
	nodo = frente_;
	if (!nodo) {
		throw "ERROR -- No hay elementos en la cola."; // Si no hay nodos en la cola se devuelve 0
	}
	// Se asigna a frente la direccion del segundo nodo
	frente_ = nodo->siguiente;
	// Se guarda el valor de retorno
	p = nodo->paquete;
	delete nodo;
	// Si cola vacia, el ultimo debe ser NULL tambien
	if (!frente_) {
		final_ = NULL;
	}
	return p;
}

Paquete ColaPaquetes::vaciar()
{
	Nodo* nodo; // var aux para manipular nodo
	Paquete p; // var aux para retorno del valor
	nodo = frente_;
	// Se guarda el valor de retorno
	p = nodo->paquete;
	while (frente_) {
		desencolar();
	}
	return p;
}

bool ColaPaquetes::es_vacia()
{
	return ((frente_ == NULL) && (final_ == NULL));
}
