#include "Furgoneta.hpp"

Furgoneta::Furgoneta()
{
	muelle_salida = 0;
	zona_entrega = 0;
	paquetes = new Paquete[5]();
	repartiendo = false;
}

Furgoneta::Furgoneta(int muelle_salida_, int zona_entrega_, Paquete* paquetes_)
{
	muelle_salida = muelle_salida_;
	zona_entrega = zona_entrega_;
	paquetes = paquetes_;
	repartiendo = false;
}

Furgoneta::Furgoneta(int muelle_salida_, int zona_entrega_, Paquete* paquetes_, bool repartiendo_)
{
	muelle_salida = muelle_salida_;
	zona_entrega = zona_entrega_;
	paquetes = paquetes_;
	repartiendo = repartiendo_;
}

void Furgoneta::reparte()
{
	repartiendo = true;
}

void Furgoneta::espera()
{
	repartiendo = false;
}

bool Furgoneta::estado()
{
	return repartiendo;
}
