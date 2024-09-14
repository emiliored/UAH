#pragma once
#include <string>

class Cliente
{
public:
	// Atributos
	struct {
		std::string nif;
	} datos;

	int zona;

	// Constructor
	Cliente();
	Cliente(std::string nif_);
	Cliente(std::string nif_, int zona_);
	// Metodos
	std::string getNif();
};

