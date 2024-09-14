// ProyectoEEDD.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "../headers/Gestor.hpp"

using namespace std;

int main()
{
    cout << "Funcionamiento De Servicio De Paquetes" << endl;
    cout << "\tPresione enter para continuar" << endl;
    getchar();
    cout << "\t\tCola De Central De Paqueteria" << endl;
    cout << "\t\t\tGenerando paquetes..." << endl;
    Gestor* g = new Gestor(NMUELLESCARGA, NFURGONETAS, NZONAENTREGA);
    g->generarPaquetes(N1);
    cout << "\t\t\tPaquetes generados correctamente... " << endl;
    cout << "\tPresione enter para continuar" << endl;
    getchar();

    for (int contador = 0; contador < (N2 % N1); contador++) {
        cout << "\t\tTransportando paquetes a los muelles..." << endl;
        g->transportarPaquetesMuelles(N2);
        cout << "\t\t\tPaquetes transportados correctamente... " << endl;
        cout << "\t\tTransportando paquetes de los muelles a las furgonetas..." << endl;
        g->transportarMuelleFurgoneta(N3);
        cout << "\t\t\tPaquetes transportados correctamente... " << endl;
        cout << "\t\tEntregando los paquetes de las furgonetas a las zonas entrega..." << endl;
        g->transportarFurgonetaEntrega(N3);
        cout << "\t\t\tPaquetes entregados correctamente... " << endl;
        cout << "\tPresione enter para continuar" << endl;
        getchar();
    }
    cout << "\t\tMostrando entregas realizadas..." << endl;
    g->mostrarEntregas();
    cout << "Fin de la ejecucion.\n";
    cout << "\tPresione enter para salir" << endl;
    getchar();

}
