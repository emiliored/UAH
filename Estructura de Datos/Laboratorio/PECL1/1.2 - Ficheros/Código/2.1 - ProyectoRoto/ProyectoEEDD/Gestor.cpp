#include "Gestor.hpp"

Gestor::Gestor()
{
	central = ColaPaquetes();
	max_furgonetas = -1;
}

Gestor::Gestor(int nmuelles_carga,int nfurgonetas, int nzona_entregas)
{
	central = ColaPaquetes();
	max_furgonetas = nfurgonetas;
	for (int i = 0; i < nmuelles_carga; i++) {
		muelles_carga.push_back(MuellesCarga());
	}
	for (int i = 0; i < nzona_entregas; i++) {
		zona_entregas.push_back(ColaPaquetes());
	}
}

void Gestor::generarPaquetesZona(int n1, int clientesporzona) 
{
	//NZONAENTREGA
	Paquete p = Paquete();
	//Generamos los clientes por zona
	int secuencia = 0;
	std::string ssecuencia;
	
	for (int i = 0; i < NZONAENTREGA; i++) {
		for (int u = 0; u < clientesporzona; u++) {
			std::string nif = p.generarNIF();
			clientes.push_back(Cliente(nif, i));

			ssecuencia = std::to_string(secuencia);

			if (ssecuencia.size() < 4) {
				int temp = ssecuencia.size();
				for (int u = 0; u < (4 - temp); u++) {
					ssecuencia.insert(0, "0");
				}
			}
			central.encolar(Paquete(ssecuencia,nif));
			//central.encolar(Paquete(ssecuencia));
			secuencia++;
		}
	}
}

void Gestor::generarPaquetes(int n1)
{
	int secuencia = 0;
	std::string ssecuencia;
	for (int i = 0; i < n1; i++) {
		ssecuencia = std::to_string(secuencia);
		if (ssecuencia.size() < 4) {
			int temp = ssecuencia.size();
			for (int u = 0; u < (4 - temp); u++) {
				ssecuencia.insert(0, "0");
			}
		}
		central.encolar(Paquete(ssecuencia));
		secuencia++;
	}
}
void Gestor::transportarPaquetesMuellesClientes(int n1, int clientesporzona)
{
	Paquete p; // Variable auxiliar paquete.
	MuellesCarga muelle; // Variable auxiliar muelle.
	int index = -1;
	for (int i = 0; i < n1; i++) {
		p = central.desencolar();
		for (int u = 0; u < clientes.size(); u++) {
			if (clientes[u].getNif() == p.etiqueta.nif) {
				// Inserto el paquete de la central en los muelles de carga segun su latitud.
				index = clientes[u].zona;
				break;
			}
		}
		muelle = muelles_carga.at(index);
		muelle.introducir(p);
		muelles_carga.at(index) = muelle;
		std::cout << "\tSacando paquete " << p.etiqueta.id.apellido
			<< p.etiqueta.id.numeros_restantes << " para introducirlo en el muelle de carga "
			<< index
			<< std::endl;
		
	}
}
void Gestor::transportarPaquetesMuelles(int n2)
{
	Paquete p; // Variable auxiliar paquete.
	MuellesCarga muelle; // Variable auxiliar muelle.
	for (int i = 0; i < n2; i++) {
		p = central.desencolar();
		// Inserto el paquete de la central en los muelles de carga segun su latitud.
		int index = p.etiqueta.gps.latitud.minutos % muelles_carga.size();
		muelle = muelles_carga.at(index);
		muelle.introducir(p);
		muelles_carga.at(index) = muelle;
		std::cout << "\tSacando paquete " << p.etiqueta.id.apellido 
			<< p.etiqueta.id.numeros_restantes << " para introducirlo en el muelle de carga "
			<< index
			<< std::endl;
	}
}

void Gestor::transportarMuelleFurgoneta(int n3)
{
	Paquete* paquetes;
	Paquete aux; // Variable auxiliar de paquete
	for (int i = 0; i < muelles_carga.size(); i++) { // Recorro cada muelle de carga
		paquetes = new Paquete[n3]();
		// Comprobamos si los paquetes almacenados en el muelle caben en una furgoneta
		if (muelles_carga.at(i).size() >= n3) {
			for (int u = 0; u < n3; u++) {
				// Preparamos los paquetes para ser almacenados en la furgoneta
				aux = muelles_carga.at(i).obtener();
				paquetes[u] = aux;
			}
			if (furgonetas.size() == NFURGONETAS) {
				reutilizarFurgoneta(i, i, paquetes);
			}
			else
			{
				crearFurgoneta(i, i, paquetes);
			}
		}
	}
}

void Gestor::transportarFurgonetaEntrega(int n3)
{
	ColaPaquetes* aux; // var auxiliar de Zona_Entrega
	Furgoneta f;
	for (int i = 0; i < furgonetas.size(); i++) {
		f = furgonetas.at(i);
		if (f.estado()) {
			aux = &zona_entregas.at(f.zona_entrega);
			for (int i = 0; i < n3; i++) {
				aux->encolar(f.paquetes[i]);
			}
			zona_entregas.at(f.zona_entrega) = *aux;
			f.espera(); // Cerramos la furgoneta
			furgonetas.at(i) = f;
			std::cout << "\tFurgoneta " << i << " a la espera."
				<< std::endl;
		}
	}
}

void Gestor::crearFurgoneta(int muelle_, int zona_entrega_, Paquete* paquetes)
{
	if (furgonetas.size() <= max_furgonetas) {
		furgonetas.push_back(Furgoneta(muelle_,zona_entrega_, paquetes, true));
		std::cout << "\tFurgoneta creada " << muelle_ << " - " << zona_entrega_
			<< " - " << paquetes
			<< std::endl;
	}
}

void Gestor::reutilizarFurgoneta(int muelle_, int zona_entrega_, Paquete* paquetes)
{
	Furgoneta f;
	for (int i = 0; i < furgonetas.size(); i++) {
		f = furgonetas.at(i);
		// Suponemos que las furgonetas vuelven al muelle de donde salieron cuando finalizan su trayecto.
		if (f.estado() == false) {
			f.muelle_salida == muelle_;
			f.paquetes = paquetes;
			f.zona_entrega = zona_entrega_;
			f.reparte();
			furgonetas.at(i) = f;
			std::cout << "\tFurgoneta reutilizada " << muelle_ << " - " << zona_entrega_
				<< " - " << paquetes
				<< std::endl;
			break;
		}
	}
}

void Gestor::mostrarEntregas()
{
	Paquete p;
	int z0 = 0, z1 = 0, z2 = 0, z3 = 0, aux = 0; // Contadores para sacar estadisticas de las zonas.
	std::cout << "Mostrando los paquetes entregados...\n";
	for (int i = 0; i < zona_entregas.size(); i++) {
		while (!zona_entregas.at(i).es_vacia()) {
			p = zona_entregas.at(i).desencolar();
			std::cout << "\tZona de Entrega " << i << " -- Paquete: ID: " 
				<< p.etiqueta.id.apellido << p.etiqueta.id.numeros_restantes
				<< ", GPS: " << p.etiqueta.gps.latitud.grados << " " << p.etiqueta.gps.latitud.minutos
				<< " " << p.etiqueta.gps.latitud.segundos << " _ " << p.etiqueta.gps.longitud.grados
				<< " " << p.etiqueta.gps.longitud.minutos << " " << p.etiqueta.gps.longitud.segundos
				<< ", NIF: " << p.etiqueta.nif <<  std::endl;
			if (i == 0) {
				z0++;
				continue;
			}
			if (i == 1)
			{
				z1++;
				continue;
			}
			if (i == 2)
			{
				z2++;
				continue;
			}
			if (i == 3)
			{
				z3++;
				continue;
			}
		}
	}
	std::vector<int> v{z0,z1,z2,z3};
	std::string s = "";
	for (int i = 0; i < v.size(); i++) {
		if (aux < v[i]) {
			aux = v[i];
			s = "Z" + std::to_string(i);
		}
	}

	std::cout << "\tSe han entregado  " << z0+z1+z2+z3 << " paquetes. Z0 = "
		<< z0 << ", Z1 = " << z1 << ", Z2 = "<<z2 << ", Z3 = " << z3
		<< "\n\t La zona con mas paquetes es: " << s << " con " << aux << " paquetes recibidos."
		<< std::endl;
}
