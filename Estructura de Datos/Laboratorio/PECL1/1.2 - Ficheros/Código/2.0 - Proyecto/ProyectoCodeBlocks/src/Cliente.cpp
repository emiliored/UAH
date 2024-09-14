#include "../headers/Cliente.hpp"

Cliente::Cliente()
{
	datos.nif = "";
}

Cliente::Cliente(std::string nif_)
{
	datos.nif = nif_;
}

std::string Cliente::getNif()
{
	return datos.nif;
}
