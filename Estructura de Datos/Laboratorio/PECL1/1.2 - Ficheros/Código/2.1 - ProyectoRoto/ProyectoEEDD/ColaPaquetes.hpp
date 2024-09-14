#pragma once
#include "Paquete.hpp"

class ColaPaquetes
{
private:
	class Nodo // Clase Nodo para controlar los elementos de la cola
	{
	public:
		Nodo();
		Nodo(Paquete p, Nodo* sig = NULL);
		~Nodo();
		Paquete paquete;
		Nodo* siguiente;
	};
	// Atributos ColaPaquetes
	Nodo* frente_;
	Nodo* final_;
public:
	// Constructor
	ColaPaquetes();
	~ColaPaquetes();
	// Metodos
	void encolar(Paquete p);
	Paquete desencolar();
	Paquete vaciar();
	bool es_vacia();
};

