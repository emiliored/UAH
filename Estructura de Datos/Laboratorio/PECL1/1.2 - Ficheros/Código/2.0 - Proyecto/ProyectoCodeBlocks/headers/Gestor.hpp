#pragma once
#include "Paquete.hpp"
#include "Furgoneta.hpp"
#include "MuellesCarga.hpp"
#include "ColaPaquetes.hpp"
#include <vector>
#include <iostream>

class Gestor
{
public:
	// Atributos
	ColaPaquetes central;
	std::vector<MuellesCarga> muelles_carga;
	std::vector<Furgoneta> furgonetas;
	std::vector<ColaPaquetes> zona_entregas;
	int max_furgonetas;
	//Constructor
	Gestor();
	Gestor(int nmuelles_carga, int nfurgonetas, int nzona_entregas);
	// Metodos
	void generarPaquetes(int n1); // El parametro es N1
	void transportarPaquetesMuelles(int n2);
	void transportarMuelleFurgoneta(int n3);
	void transportarFurgonetaEntrega(int n3);
	void mostrarEntregas();
	void crearFurgoneta(int muelle_, int zona_entrega_, Paquete* paquetes);
	void reutilizarFurgoneta(int muelle_, int zona_entrega_, Paquete* paquetes);
};

