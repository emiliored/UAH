#pragma once
#include <string>

class Cliente
{
public:
	// Atributos
	struct {
		std::string nif;
	} datos;

	// Constructor
	Cliente();
	Cliente(std::string nif_);
	// Metodos
	std::string getNif();
};

