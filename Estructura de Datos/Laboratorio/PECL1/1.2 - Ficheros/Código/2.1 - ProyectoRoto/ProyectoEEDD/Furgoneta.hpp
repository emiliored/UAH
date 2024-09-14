#pragma once
#include "Paquete.hpp"

class Furgoneta
{
public:
	// Atributos
	int muelle_salida;
	int zona_entrega;
	Paquete* paquetes;
	bool repartiendo;

	// Constructor
	Furgoneta();
	Furgoneta(int muelle_salida_, int zona_entrega_, Paquete* paquetes_);
	Furgoneta(int muelle_salida_, int zona_entrega_, Paquete* paquetes_, bool repartiendo_);
	// Métodos
	bool estado();
	void reparte();
	void espera();
};

