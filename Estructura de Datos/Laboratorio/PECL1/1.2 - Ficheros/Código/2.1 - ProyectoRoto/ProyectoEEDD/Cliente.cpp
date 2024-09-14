#include "Cliente.hpp"

Cliente::Cliente()
{
	datos.nif = "";
}

Cliente::Cliente(std::string nif_)
{
	datos.nif = nif_;
}

Cliente::Cliente(std::string nif_, int zona_)
{
	datos.nif = nif_;
	zona = zona_;
}

std::string Cliente::getNif()
{
	return datos.nif;
}
