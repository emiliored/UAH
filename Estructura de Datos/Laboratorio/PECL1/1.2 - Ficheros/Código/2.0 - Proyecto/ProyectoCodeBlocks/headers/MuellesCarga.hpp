#pragma once
#include "Paquete.hpp"
#include "ProyectoEEDD.hpp" // Para hacerlo mas escalable

// Pila de MuellesCarga

class MuellesCarga // Zona operativa N2
{
private:
	static const int elementos_pila = NELEMENTOSMUELLESCARGA;
	int cima;
	Paquete paquetes[elementos_pila];
public:
	// Constructor
	MuellesCarga();
	// Destructor
	~MuellesCarga();
	//Metodos
	bool vacio();
	bool lleno();
	void introducir(Paquete p);
	Paquete obtener();
	int size();
};

