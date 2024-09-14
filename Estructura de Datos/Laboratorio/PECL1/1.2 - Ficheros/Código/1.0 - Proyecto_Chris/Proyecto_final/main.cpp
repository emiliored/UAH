#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip> // para usar stw
#include "Paquetes.h"

using namespace std;


int main()
{

    cout<<"\t\t\t\tFuncionamiento De Servicio De Paquetes"<<endl<<endl<<endl;
    cout<<"Presione enter para continuar"<<endl<<endl<<endl;
    getch();
    cout<<"\t\t\t\tCola De Central De Paqueteria"<<endl<<endl<<endl;
    cola_paquetes();
    cout<<"Presione enter para continuar"<<endl<<endl<<endl;
    getch();
    cout<<"\t\t\t\tFurgonetas Situadas En El Muelle"<<endl<<endl<<endl;
    Colass();
    paquetes();
    cout<<"Presione enter para continuar"<<endl<<endl<<endl;
    getch();
    cout<<"\t\t\t\tPaquetes Enviados A Cada Zona De Reparto"<<endl<<endl<<endl;
    camiones();
    cout<<"La simulación ha terminado"<<endl<<endl<<endl;

    return 0;
}

