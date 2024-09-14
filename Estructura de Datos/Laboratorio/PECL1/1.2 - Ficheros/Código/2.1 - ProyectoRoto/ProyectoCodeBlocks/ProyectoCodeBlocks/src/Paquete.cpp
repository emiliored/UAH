#include "../headers/Paquete.hpp"

Paquete::Latitud::Latitud()
{
	grados = 40;
	minutos = 32 + rand() % (42 - 32);
	segundos = 5 + rand() % (7 - 5);
}

Paquete::Latitud::Latitud(int grados_, int minutos_, int segundos_)
{
	grados = grados_;
	minutos = minutos_;
	segundos = segundos_;
}

Paquete::Longitud::Longitud()
{
	grados = -3;
	minutos = 46 + rand() % (52 - 46);
	segundos = 5 + rand() % (7 - 5);
}

Paquete::Longitud::Longitud(int grados_, int minutos_, int segundos_)
{
	grados = grados_;
	minutos = minutos_;
	segundos = segundos_;
}

Paquete::Gps::Gps()
{
	latitud = Latitud();
	longitud = Longitud();
}

Paquete::Gps::Gps(Latitud latitud_, Longitud longitud_)
{
	latitud = latitud_;
	longitud = longitud_;
}

Paquete::Gps::Gps(int grados_lat, int minutos_lat, int segundos_lat, int grados_lon, int minutos_lon, int segundos_lon)
{
	latitud.grados = grados_lat;
	latitud.minutos = minutos_lat;
	latitud.segundos = segundos_lat;
	longitud.grados = grados_lon;
	longitud.minutos = minutos_lon;
	longitud.segundos = segundos_lon;
}

Paquete::ID::ID()
{
	apellido = "Macias";
	numeros_restantes = "0000";
}

Paquete::ID::ID(std::string numeros_restantes_)
{
	char letras[24] = "TRWAGMYFPDXBNJZSQVHLCKE";

	apellido = "Macias";
	numeros_restantes = numeros_restantes_;
}

Paquete::ID::ID(std::string apellido_, std::string numeros_restantes_)
{
	apellido = apellido_;
	numeros_restantes = numeros_restantes_;
}

Paquete::Etiqueta::Etiqueta()
{
	id = ID();
	gps = Gps();
	nif = "";
}

Paquete::Etiqueta::Etiqueta(ID id_, Gps gps_, std::string nif_)
{
	id = id_;
	gps = gps_;
	nif = nif_;
}


Paquete::Paquete()
{
	tipo = 0;
	etiqueta = Etiqueta();
	urgente = false;
}

Paquete::Paquete(std::string id_)
{
	tipo = 0;
	etiqueta.id = ID(id_.c_str());
	etiqueta.gps.latitud = Latitud();
	etiqueta.gps.longitud = Longitud();
	etiqueta.nif = generarNIF();
	urgente = false;
}

Paquete::Paquete(std::string id_, std::string nif_)
{
	tipo = 0;
	etiqueta.id = ID(id_.c_str());
	etiqueta.gps.latitud = Latitud();
	etiqueta.gps.longitud = Longitud();
	etiqueta.nif = nif_;
	urgente = false;
}

Paquete::Paquete(std::string id_, int grados_lat_, int minutos_lat_, int segundos_lat_, int grados_lon_, int minutos_lon_, int segundos_lon_, bool urgente_)
{
	tipo = 0;
	etiqueta.id = ID(id_);
	etiqueta.gps.latitud.grados = grados_lat_;
	etiqueta.gps.latitud.minutos = minutos_lat_;
	etiqueta.gps.latitud.segundos = segundos_lat_;
	etiqueta.gps.longitud.grados = grados_lon_;
	etiqueta.gps.longitud.minutos = minutos_lon_;
	etiqueta.gps.longitud.segundos = segundos_lon_;
	etiqueta.nif = generarNIF();
	urgente = urgente_;
}

Paquete::Paquete(std::string id_, int grados_lat_, int minutos_lat_, int segundos_lat_, int grados_lon_, int minutos_lon_, int segundos_lon_, std::string nif_, bool urgente_)
{
	tipo = 0;
	etiqueta.id = ID(id_);
	etiqueta.gps.latitud.grados = grados_lat_;
	etiqueta.gps.latitud.minutos = minutos_lat_;
	etiqueta.gps.latitud.segundos = segundos_lat_;
	etiqueta.gps.longitud.grados = grados_lon_;
	etiqueta.gps.longitud.minutos = minutos_lon_;
	etiqueta.gps.longitud.segundos = segundos_lon_;
	etiqueta.nif = nif_;
	urgente = urgente_;
}



std::string Paquete::generarNIF()
{
	std::string s = "";
	for (int i = 0; i < 8; i++)
	{
		char num = "06021665"[rand() % 8];
		s += num;
	}
	s += "N";
	return  s;
}



