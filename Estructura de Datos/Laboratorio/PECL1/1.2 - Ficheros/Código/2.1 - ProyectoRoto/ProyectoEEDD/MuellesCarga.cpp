#include "MuellesCarga.hpp"

MuellesCarga::MuellesCarga()
{
	cima = -1;
}

MuellesCarga::~MuellesCarga()
{
}

bool MuellesCarga::vacio()
{
	if (cima == -1)
		return true;
	else
		return false;
}

bool MuellesCarga::lleno()
{
	if (cima == elementos_pila - 1)
		return true;
	else
		return false;
}

void MuellesCarga::introducir(Paquete p)
{
	if (!lleno()) {
		paquetes[++cima] = p;
	}
	else {
		throw "ERROR -- No se puede añadir el paquete.";
	}
}

Paquete MuellesCarga::obtener()
{
	if (!vacio()) {
		return paquetes[cima--];
	}
	else {
		throw "ERROR -- No se pueden extraer valores.";
	}
}

int MuellesCarga::size()
{
	return cima+1;
}
