#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <math.h>
#include "Tipos.h"
#define N1 8
#define N2 100
#define N3 12
#define N5 6
#define N4 N5*N3

using namespace std;

string localidades[] = {"Ajalvir","Daganzo","Alcala", "Mejorada", "Nuevo Baztan", "Arganda", "Carabanna", "Chinchon", "Villarejo",
                        "Camarma de Esteruelas", "Meco", "Cobeña", "Torres de la Alameda", "Los Santos de la Humosa"
                       };

string padTo(string &str, const size_t num, const char paddingChar = '0')
{
    if(num > str.size())
        str.insert(0, num - str.size(), paddingChar);
    return str;
}

string generarIdPaquete()
{
    string id;
    char abecedario[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    string parte1 = to_string(rand()%99);
    string parte2 = to_string(rand()%9999);
    id= padTo(parte1,2)+  abecedario[rand()%26] + padTo(parte2,4);
//    id = padTo(to_string(rand()%99),2) +  abecedario[rand()%26] + padTo(to_string(rand()%9999),4);

    return id;
}
int generarNumCP()
{
    return rand()%9999;
}
string AsignarLocalidades()//Revisar
{
    int size= 13;
    int aleatorio=rand()%size;
    return localidades[aleatorio];
}
string generarNIF()
{
    int numero;
    string NIF;
    char letras[] = {'T','R','w','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};

    for (int i=0; i<6; i++)
    {
        numero = numero*10 + rand()%10;
    }
    NIF = to_string(numero) + letras[numero%23];

    return NIF;
}

CoordenadasGPS generarCoordenadas()
{
    CoordenadasGPS c;
    int gradLat, minLat, segLat, gradLong, minLong, segLong;

    gradLat = 40;
    minLat = 6 + rand()%28;
    segLat = rand()%60;
    gradLong = -3;
    minLong = 5 + rand()%29;
    segLong = rand()%60;

    c.latitud[0] = gradLat;
    c.latitud[1] = minLat;
    c.latitud[2] = segLat;
    c.longitud[0] = gradLong;
    c.longitud[1] = minLong;
    c.longitud[2] = segLong;

    return c;
}

Paquete generarPaquete(int numCp)
{
    Paquete p;

    p.idPaquete = generarIdPaquete();
    p.coordenadas = generarCoordenadas();
    p.NIF = generarNIF();
    p.numCP = numCp;

    return p;
}
CP generarCpPredeterminado()
{
    CP cp;
    cp.numCP=generarNumCP();
    cp.localidad=AsignarLocalidades();
    cp.listaPaq=new Lista();

    return cp;
}

void sigInstruccion() //Método para ir paso a paso con la ejecución del programa
{
    cout << '\n' << "Presiona Enter para realizar la siguiente instruccion..." << '\n' << endl;
    getchar();

}

Arbol *arbolCP=NULL;
Lista *CAE=NULL;


void inicializaSistema()
{
    // Inicializamos árbol de búsqueda y lista maestra de paquetes
    arbolCP = new Arbol();
    CAE = new Lista();
    int aux[N1];
    Paquete p;

    for (int i=0; i<N1; i++)//Crea las 8 centrales de paqueteria y las muestra por pantalla
    {
        CP cp=generarCpPredeterminado();
        aux[i]=cp.numCP;
        arbolCP->insertar(cp);
        cout<<setw(3)<<i+1<<" "<< setw(8) << cp.numCP << " " <<"   "<< setw(12) << cp.localidad << endl;//Ver como se hace con abb y no con array
    }

    cout << string(27, '=') << "LISTADO DE PAQUETES" << string(27,'=') << endl;
    cout << setw(4) << " No." << "|" << setw(7) << "ID Paq " << "|" << setw(9) << "   NIF   " << "|" << setw(21) << "     Coordenadas     " << "|" << endl;
    cout << string(22, ' ') << "|" << setw(10) << " Latitud  " << "|"<< setw(10) << " Longitud " << "|" << endl;
    cout << string(45, '-') << endl;
    //Crea los 100 paquetes y los muestra por pantalla
    for (int j=0; j<N2; j++)
    {
        // Seleccionamos aleatoriamente uno de los numCp generados en el paso anterior
        p=generarPaquete(aux[rand()%N1]);
        CAE->insertarNodo(p,'p');
        cout << setw(4)<< j+1 << " " << setw(7) << p.idPaquete << " " << setw(9) << p.NIF << " " << setw(2) << p.coordenadas.latitud[0] << "*" << setw(2) << p.coordenadas.latitud[1] << "'" << setw(2) << p.coordenadas.latitud[2] << "''" << " " << setw(2) << p.coordenadas.longitud[0] << "*"<< setw(2) << p.coordenadas.longitud[1] << "'" << setw(2) << p.coordenadas.longitud[2] << "''" << endl;
    }
}

void muestraNodoArbol(int &valor)
{
    cout << valor << ";" << endl;
}

void muestraCP(CP &valor)
{
    cout << valor.numCP << ";" << valor.localidad << ";" << endl;
    valor.listaPaq->mostrarLista();
}



void muestraEstadisticaCP(CP &valor)
{
    double frec_abs = valor.listaPaq->numNodos();
    double nCae = CAE->numNodos();
    double frec_rel = frec_abs / (100 - nCae);
    cout << setw(4) << valor.numCP << setw(12) << " " << setw(2) << frec_abs << setw(20) << " " << setw(2) << round(frec_rel*100) <<'%'<< endl;
}

bool encuentraNodo(CP &valor, string idPaquete)
{
    return (valor.listaPaq->existe(idPaquete) != NULL);
}


int main()
{
    srand(time(NULL));
    int opcion;
    bool repetir = true;
    Paquete p;
    CP centralPaq;
    CP cpAux;
    Paquete paqueteAux;
    int i=0, j=0, nPaquetes=0, nCP=0;
    int paquetesCogidos=0;
    int codCentralCase2 = 0;
    int codCentralCase3 = 0;
    int codCentralCase6 = 0;
    int codCentralCase7 = 0;
    int codCentralCase8 = 0;

    string idCase5;
    string idCase6;
    string idCase7;
    string idCase8;
    //CP cpSelec;
    int gradLat=0, minLat=0, segLat=0, gradLong=0, minLong=0, segLong=0;
    int contadorPaquetes=N1;

    cout << string(33, '#') << "ALMACEN DE PAQUETES" << string(33, '#') << endl;
    cout << string(27, '=') << "LISTADO DE CENTRALES DE PAQUETERIA" << string(27, '=') << endl;
    cout << setw(4) << " No." << "|" << setw(7) << "ID CP " << "|" << setw(9) << "   Nombre localidad   " << endl;
    cout << string(45, '-') << endl;

    inicializaSistema();

    // Bucle de iteraciones/días
    int contador = 0;
    while(contador++<N5)
    {
        sigInstruccion();
        paquetesCogidos=0;
        cout << "Paquetes enviados en el dia " << contador << ":"<<endl;
        while(paquetesCogidos++ < N3)
        {
            pNodoLista nodoLista = CAE->borrarAntiguo();
            if (nodoLista!=NULL)
            {
                p = nodoLista->getPaquete();
                CP cpAux;
                cpAux.numCP = p.numCP;
                pNodoArbol nodoArbol = arbolCP->buscar(cpAux);
                nodoArbol->getCentrarlP().listaPaq->insertarNodo(p,'p');
                delete(nodoLista);
                cout<< "Paquete: "<<p.idPaquete << " añadido a la lista de paquetes del CP de :" <<nodoArbol->getCentrarlP().numCP << endl;
            }
        }
    }

    do
    {
        system("cls");
        // Texto del menú que se verá cada vez
        cout << "\n\nMenu de Opciones" << endl;
        cout << "1. Insertar una CP de forma manual." << endl;
        cout << "2. Borrar una CP del arbol." << endl;
        cout << "3. Mostrar los datos de los paquetes que se distribuiran en una CP dada." << endl;
        cout << "4. Mostrar una estadistica de las CP de la empresa recorriendo Postorden los nodos del arbol." << endl;
        cout << "5. Buscar un paquete concreto por su ID." << endl;
        cout << "6. Extraer algun paquete concreto de una CP dada (borrarlo del sistema)." << endl;
        cout << "7. Llevar un paquete concreto del CAE a una CP concreta." << endl;
        cout << "8. Llevar un paquete concreto de una CP a otra." << endl;
        cout << "9. Continuar con la distribucion de paquetes." << endl;

        cout << "0. Salir del programa" << endl;

        cout << "\nIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            // Insertar una CP de forma manual
            cout<<"Numero de CP deseado(Numero de tres cifras): ";
            cin >>centralPaq.numCP;//Asigno el número de CP manual
            for(auto const& value : localidades) //Para ver las localidades disponibles.
            {
                cout << value << ", ";
            }
            cout << endl;
            cout << "Localidad deseada: ";
            cin >> centralPaq.localidad;
            cout << endl;
            centralPaq.listaPaq = new Lista();
            arbolCP->insertar(centralPaq);
            arbolCP->inOrden(&muestraNodoArbol);
            cout << "¿Quieres continuar con la distribucion de paquetes? (Si/No): ";
            string r;
            cin >> r;
            if (r == "Si")
            {
                for(int i=0; i<12; i++)
                {
                    p=generarPaquete(centralPaq.numCP);
                    centralPaq.listaPaq->insertarNodo(p,'p');
                }
                arbolCP->inOrden(&muestraNodoArbol);
            }
            else
            {
                arbolCP->inOrden(&muestraNodoArbol);

            }
            system("pause>nul"); // Pausa
            break;

        }
        case 2:
            // Borrar una CP del árbol
            cout << "Lista de centrales disponibles:"<<endl;
            arbolCP->inOrden(&muestraNodoArbol);
            cout << "Codigo de la central que desea eliminar: "; //Busco la central por su código
            cin >> cpAux.numCP;
            //cpAux.numCP=codCentralCase2;
            cout << endl;
            arbolCP->borrar(cpAux);

            arbolCP->inOrdenCP(&muestraCP);
            system("pause>nul"); // Pausa
            break;

        case 3:
            // Mostrar los datos de los paquetes que se distribuirán en una CP dada
            arbolCP->inOrden(&muestraNodoArbol);

            cout << "Central que desea ver (Numero de tres cifras): ";
            cin >> codCentralCase3;
            cpAux.numCP=codCentralCase3;
            pNodoArbol auxNodoArbol;
            auxNodoArbol=arbolCP->buscar(cpAux);
            if (auxNodoArbol!=NULL)
            {
                auxNodoArbol->getCentrarlP().listaPaq->mostrarLista();
            }
            else
            {
                cout<<"No hay ninguna central con ese codigo"<<endl;
            }
            system("pause>nul"); // Pausa
            break;

        case 4:
            // Mostrar una estadística de las CP de la empresa recorriendo Inorden los nodos del árbol
            cout << setw(4) << "CP " << "|" << setw(7) << " Frecuencias absolutas " << "|" << setw(9) << " Frecuencias relativas" << endl;
            arbolCP->postOrdenCP(&muestraEstadisticaCP);
            system("pause>nul"); // Pausa
            break;

        case 5:
            // Buscar un paquete concreto por su ID
            arbolCP->inOrdenCP(&muestraCP);
            cout << "ID del paquete a buscar: ";
            cin >> idCase5;
            cout << endl;
            {
                Paquete p;
                pNodoArbol n;
                n = arbolCP->buscarNodoInOrdenCP(&encuentraNodo,idCase5);
                if (n==NULL)
                {
                    cout << "No se ha encontrado el paquete " << idCase5 << endl;
                }
                else
                {
                    CP cp = n->getCentrarlP();
                    pNodoLista pn = cp.listaPaq->existe(idCase5);
                    p = pn->getPaquete();
                    cout << "El paquete encontrado es: " << setw(7) << p.idPaquete << " " << setw(9) << p.NIF << " " << setw(2)
                         << p.coordenadas.latitud[0] << "*" << setw(2) << p.coordenadas.latitud[1] << "'" << setw(2) << p.coordenadas.latitud[2]
                         << "''" << " " << setw(2) << p.coordenadas.longitud[0] << "*"<< setw(2) << p.coordenadas.longitud[1] << "'" << setw(2)
                         << p.coordenadas.longitud[2] << "''" << endl;
                }
            }
            system("pause>nul"); // Pausa
            break;

        case 6:
            // Extraer algún paquete concreto de una CP dada (borrarlo del sistema)
            arbolCP->inOrden(&muestraNodoArbol);
            cout << "Codigo de la central donde esta el paquete que quiere buscar: "; //Busco la central por su código
            cin >> codCentralCase6;
            cout << endl;
            cpAux.numCP=codCentralCase6;
            auxNodoArbol=arbolCP->buscar(cpAux);
//            muestraCP(auxNodoArbol->getCentrarlP());
            cout << auxNodoArbol->getCentrarlP().numCP << ";" << auxNodoArbol->getCentrarlP().localidad << ";" << endl;
            auxNodoArbol->getCentrarlP().listaPaq->mostrarLista();

            cout << "ID del paquete a buscar: ";
            cin >> idCase6;
            cout << endl;
            pNodoArbol n;
            n = arbolCP->buscarNodoInOrdenCP(&encuentraNodo,idCase6);
            if (n==NULL)
            {
                cout << "No se ha encontrado el paquete " << idCase6 << endl;
            }
            else
            {
                CP cp = n->getCentrarlP();
                pNodoLista pn = cp.listaPaq->existe(idCase6);
                            Paquete p = pn->getPaquete();
                cout << "El paquete encontrado es: " << setw(7) << p.idPaquete << " " << setw(9) << p.NIF << " " << setw(2) <<
                     p.coordenadas.latitud[0] << "*" << setw(2) << p.coordenadas.latitud[1] << "'" << setw(2) << p.coordenadas.latitud[2]
                     << "''" << " " << setw(2) << p.coordenadas.longitud[0] << "*"<< setw(2) << p.coordenadas.longitud[1] << "'" << setw(2)
                     << p.coordenadas.longitud[2] << "''" << endl;
                cp.listaPaq->borrarNodoIntermedio(pn);
                cout << "Paquete borrado" << endl;
            }
            system("pause>nul"); // Pausa
            break;

        case 7:
            // Llevar un paquete concreto del CAE a una CP concreta
            CAE->mostrarLista();
            cout << "ID del paquete a enviar: ";
            cin >> idCase7;
            cout << endl;
            arbolCP->inOrdenCP(&muestraCP);
            cout << "Codigo de la central de destino: "; //Busco la central por su código
            cin >> codCentralCase7;
            cout << endl;
            {
                pNodoLista n = CAE->existe(idCase7);
                if (n!=NULL)
                {
                    Paquete p = n->getPaquete();
                    CP cp;
                    cp.numCP=codCentralCase7;
                    pNodoArbol pna = arbolCP->buscar(cp);
                    pna->getCentrarlP().listaPaq->insertarNodo(p,'p');
                }
                cout << "Paquete remitido" << endl << endl;
                cout << "Lista de CPs y paquetes actualizada: " << endl;

                arbolCP->inOrdenCP(&muestraCP);
            }
            system("pause>nul"); // Pausa
            break;

        case 8:
        {

            // Llevar un paquete concreto de una CP a otra
            // Extraer algún paquete concreto de una CP dada (borrarlo del sistema)
            arbolCP->inOrden(&muestraNodoArbol);
            cout << "Codigo de la central donde esta el paquete que quiere buscar: "; //Busco la central por su código
            cin >> codCentralCase8;
            cout << endl;
            cpAux.numCP=codCentralCase8;
            auxNodoArbol=arbolCP->buscar(cpAux);
//            muestraCP(auxNodoArbol->getCentrarlP());
            cout << auxNodoArbol->getCentrarlP().numCP << ";" << auxNodoArbol->getCentrarlP().localidad << ";" << endl;
            auxNodoArbol->getCentrarlP().listaPaq->mostrarLista();

            cout << "ID del paquete a buscar: ";
            cin >> idCase8;
            cout << endl;
            n = arbolCP->buscarNodoInOrdenCP(&encuentraNodo,idCase8);
            if (n==NULL)
            {
                cout << "No se ha encontrado el paquete " << idCase8 << endl;
            }
            else
            {
                CP cp = n->getCentrarlP();
                pNodoLista pn = cp.listaPaq->existe(idCase8);
                Paquete p = pn->getPaquete();
                cout << "El paquete encontrado es: " << setw(7) << p.idPaquete << " " << setw(9) << p.NIF << " " << setw(2) << p.coordenadas.latitud[0] << "" << setw(2) << p.coordenadas.latitud[1] << "'" << setw(2) << p.coordenadas.latitud[2] << "''" << " " << setw(2) << p.coordenadas.longitud[0] << ""<< setw(2) << p.coordenadas.longitud[1] << "'" << setw(2) << p.coordenadas.longitud[2] << "''" << endl;
                cp.listaPaq->borrarNodoIntermedio(pn);
                cout << "Paquete borrado" << endl;
            }
            arbolCP->inOrdenCP(&muestraCP);
            cout << "Central que desea ver: ";
            cin >> codCentralCase8;
            CP cpa;
            cpa.numCP=codCentralCase8;
            pNodoArbol auxn;
            auxn=arbolCP->buscar(cpa);
            auxn->getCentrarlP().listaPaq->insertarNodo(p,'p');




            cout << "Paquete remitido" << endl << endl;
            cout << "Lista de CPs y paquetes actualizada: " << endl;
            arbolCP->inOrdenCP(&muestraCP);

            system("pause>nul"); // Pausa
            break;
        }


        case 9:
        {
            // Continuar con la distribución de paquetes
            bool seguir = true;
            while(!CAE->listaVacia()&& seguir)
            {
                sigInstruccion();
                paquetesCogidos=0;
                cout << "Paquetes enviados en el dia " << contador << ":"<<endl;
                while(paquetesCogidos++ < N3)
                {
                    pNodoLista nodoLista = CAE->borrarAntiguo();
                    if (nodoLista!=NULL)
                    {
                        p = nodoLista->getPaquete();
                        CP cpAux;
                        cpAux.numCP = p.numCP;
                        pNodoArbol nodoArbol = arbolCP->buscar(cpAux);
                        nodoArbol->getCentrarlP().listaPaq->insertarNodo(p,'p');
                        delete(nodoLista);
                        cout<< "Paquete: "<<p.idPaquete << " annadido a la lista de paquetes del CP de :" <<nodoArbol->getCentrarlP().numCP << endl;
                    }
                }
                cout << "¿Quieres continuar con la distribucion de paquetes? (Si/No): ";
                string r;
                cin >> r;
                if (r == "Si")
                {
                    contador++;
                }
                else
                {
                    contador++;
                    seguir = false;
                }
            }
            system("pause>nul"); // Pausa
            break;
        }
        system("pause>nul"); // Pausa
        break;

        case 0:
            // Salir del programa
            repetir = false;
            break;
        }
    }
    while (repetir);

    return 0;
}
