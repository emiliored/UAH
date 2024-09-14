#pragma once
#include <string>

class Paquete
{
public:
	// Estructuras
	struct Latitud {
		int grados;
		int minutos;
		int segundos;
		Latitud();
		Latitud(int grados_, int minutos_, int segundos_);
	};
	struct Longitud {
		int grados;
		int minutos;
		int segundos;
		Longitud();
		Longitud(int grados_, int minutos_, int segundos_);
	};
	struct Gps {
		Latitud latitud;
		Longitud longitud;
		Gps();
		Gps(Latitud latitud_, Longitud longitud_);
		Gps(int grados_lat, int minutos_lat, int segundos_lat, int grados_lon, int minutos_lon, int segundos_lon);
	};
	struct ID
	{
		std::string apellido;
		std::string numeros_restantes; // 4 elementos
		ID();
		ID(std::string numeros_restantes_);
		ID(std::string apellido_, std::string numeros_restantes_);
	};

	struct Etiqueta {
		ID id; // 7 elementos
		Gps gps;
		std::string nif; // 9 elementos
		Etiqueta();
		Etiqueta(ID id_, Gps gps_, std::string nif_);
	};

	// Atributos
	int tipo;
	Etiqueta etiqueta;
	bool urgente;

	//Constructor
	Paquete();
	Paquete(std::string id_);
	Paquete(std::string id_, std::string nif_);
	Paquete(std::string id_, int grados_lat_, int minutos_lat_, int segundos_lat_, int grados_lon_, int minutos_lon_,
		int segundos_lon_, bool urgente_);
	Paquete(std::string id_, int grados_lat_, int minutos_lat_, int segundos_lat_, int grados_lon_, int minutos_lon_,
		int segundos_lon_, std::string nif_, bool urgente_);
	//Métodos
	std::string generarNIF();
};

