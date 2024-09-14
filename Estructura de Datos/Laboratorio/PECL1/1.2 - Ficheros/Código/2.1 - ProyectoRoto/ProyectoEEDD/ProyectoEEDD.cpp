// ProyectoEEDD.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Gestor.hpp"

using namespace std;

int main()
{
    cout << "Funcionamiento De Servicio De Paquetes" << endl;
    cout << "\tPresione enter para continuar" << endl;
    getchar();
    cout << "\t\tCola De Central De Paqueteria" << endl;
    cout << "\t\t\tGenerando paquetes..." << endl;
    Gestor* g = new Gestor(NMUELLESCARGA, NFURGONETAS, NZONAENTREGA);
    g->generarPaquetesZona(N1,8);
    cout << "\t\t\tPaquetes generados correctamente... " << endl;
    cout << "\tPresione enter para continuar" << endl;
    getchar();

    cout << "\t\tTransportando paquetes a los muelles..." << endl;
    g->transportarPaquetesMuellesClientes(N1,8);
    cout << "\t\t\tPaquetes transportados correctamente... " << endl;
    cout << "\t\tTransportando paquetes de los muelles a las furgonetas..." << endl;
    g->transportarMuelleFurgoneta(N3);
    cout << "\t\t\tPaquetes transportados correctamente... " << endl;
    cout << "\t\tEntregando los paquetes de las furgonetas a las zonas entrega..." << endl;
    g->transportarFurgonetaEntrega(N3);
    cout << "\t\t\tPaquetes entregados correctamente... " << endl;
    cout << "\tPresione enter para continuar" << endl;
    getchar();

    cout << "\t\tMostrando entregas realizadas..." << endl;
    g->mostrarEntregas();
    cout << "Fin de la ejecucion.\n";
    cout << "\tPresione enter para salir" << endl;
    getchar();
    
}