#ifndef PAQUETES_H_INCLUDED
#define PAQUETES_H_INCLUDED
#include<math.h>
#include<conio.h>
#include<iomanip>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Codigo_ID
{
    int dos_primeros;
    char letra;
    int numeros_restantes;
};

struct Latitud
{
    int grados;
    int minutos;
    int segundos;


};
struct Longitud
{
    int grados;
    int minutos;
    int segundos;


};

struct NIF
{
    string numeros = "06021665";
    string letra = "N";
};


struct etiqueta
{
    struct Codigo_ID id;
    struct Latitud coordenadas_latitud;
    struct Longitud coordenadas_longitud;
    struct NIF nif;
} etiquetas[100];


class Pila
{
private:
    static const int MAX = 8;
    int tope;
    int valores[MAX];
public:
    Pila()
    {
        tope = -1;
    }

    int empty()
    {
        if (tope==-1) return 1;
        else return 0;
    }
    int full()
    {
        if (tope== MAX-1) return 1;
        else return 0;
    }

    void apilar(int v)
    {
        if (! full())
        {
            valores[++tope]=v;
        }
        else
        {
            cout << "No es posible agregar un elemento" << endl;
        }
    }
    int desapilar()
    {
        if (! empty())
        {
            return (valores[tope--]);
        }
        else
        {
            cout << "No es posible extraer un elemento" << endl;
            return (0);
        }
    }
};

class Nodo
{
private:
    int valor;
    Nodo *siguiente;
    friend class Cola;
public:
    Nodo(int v, Nodo *sig = NULL)
    {
        valor = v;
        siguiente = sig;
    }
};
typedef Nodo *pnodo;



class Cola
{
public:
    Cola() : frente(NULL), final(NULL) {}
    ~Cola();
    void encolar(int v);
    int desencolar();
    int vaciar();

private:
    pnodo frente, final;
};


//Destructor
Cola::~Cola()
{
    while(frente) desencolar();
}
//Añadir elemento en la cola
void Cola::encolar(int v)
{
    pnodo nuevo;
    nuevo = new Nodo(v); // Se crea un nodo nuevo
    // Si cola no vacía, se añade el nuevo a continuación de ultimo
    if(final) final->siguiente = nuevo;
    //El último elemento de la cola es el nuevo nodo
    final= nuevo;
    // Si frente es NULL, la cola está vacía y el nuevo nodo pasa a ser el primero
    if(!frente) frente = nuevo;
}

//Leer elemento de la cola
int Cola::desencolar()
{
    pnodo nodo; //Var aux para manipular nodo
    int v; //Var aux para retorno del valor
    // Nodo apunta al primer elemento de la pila
    nodo = frente;
    if(!nodo) return 0; // Si no hay nodos en la pila se devuelve 0
    //Se asigna a frente la dirección del segundo nodo
    frente = nodo->siguiente;
    //Se guarda el valor de retorno
    v = nodo->valor;
    delete nodo; // Se borra el nodo
    // Si cola vacía, ultimo debe ser NULL también
    if(!frente) final = NULL;
    return v;
}
/*
bool Cola::es_vacia()
{
    return ((frente==NULL)&&(final==NULL));
}

void Cola::mostrar()
{
    if(es_vacia()) {
    cout << "Cola vacia"<<endl;
    }
    else{
        frente->v.verCliente();
    }
}*/
/*
void Cola::mostrarCola(){
    Cola aux;
    while(!es_vacia()){
        mostrar();
        aux.encolar(frente->v);
        desencolar();
    }
    while(!aux.es_vacia()){
        encolar(aux.frente->);v
        aux.desencolar();
    }
}*/
int Cola::vaciar()
{
    pnodo nodo; //Var aux para manipular nodo
    int v; //Var aux para retorno del valor
    nodo = frente;
    //Se guarda el valor de retorno
    v = nodo->valor;
    while (frente)desencolar();
    return v;
}





Pila pila1;
Pila pila2;
Pila pila3;
Pila pila4;
Pila pilaID1;
Pila pilaID2;
Pila pilaID3;
Pila pilaID4;

Cola cola_ID1;
Cola cola_ID2;
Cola cola_ID3;
Cola cola_ID4;
Cola cola1;
Cola cola2;
Cola cola3;
Cola cola4;
Cola central_ID;
Cola central_la_minutos;
Cola central_lo_minutos;
char DNI[8];
/*
void DNI(char dni[10]){
    char DNI[9];
    for(int i=0;i<9;i++){
        DNI[i] = dni[i];
    };
}*/


void genDNI()
{
    for (int i=0; i<8; i++)
    {
        char num="0123456789"[rand()%10];
        DNI[i]=num;
    }
}

int intDNI()
{
    int intdni = 0;
    for (int i=7; i>=0; i--)
    {
        float mult=pow(10,7-i);
        intdni = intdni + (DNI[i]-'0')*(int)mult;
    }
    return(intdni);
}

char genLetraDNI(int valor)
{
    char letras[24]="TRWAGMYFPDXBNJZSQVHLCKE";
    for (int i=7; i>=0; i--)
    {

        valor+=(int)DNI[i];
    }
    return (letras[(valor%23)]);
}
/*
int sec()
{

    cout<<setfill('0')<<setw(4)<<1;

}

*/

int la_min()
{
    int a = 32 + rand() % (42-32);
    return a;
}

int la_seg()
{
    int a = 5 + rand() % (7-5);
    return a;
}

int lo_min()
{
    int a = 46 + rand() % (52-46);
    return a;
}


int lo_seg()
{
    int a = 5 + rand() % (7-5);
    return a;
}

int num()
{
    int a = 0 + rand() % (100);
    return a;
}

char palabra()
{
    int a = 65 + rand() % (90-65);
    return a;
}



string crear(string DNI) {
    string a;
    string b;
    for (int i = 0; i < 8; i++){
        int pos = rand()%DNI.length();
        a = DNI[pos];
        b += a;
        DNI.erase(DNI.begin()+pos);
    }
    return b;
}
int crea_num(int cifras[2]){
    for (int j = 0; j < 2; j++){
        cifras[j] = rand() & (10);
    }
}


int cola_paquetes()
{
    int contador;
    srand(time(NULL));
    for(int i=0; i<100; i++)
    {
        etiquetas[i].id.dos_primeros= num();
        etiquetas[i].id.letra=palabra();
        etiquetas[i].id.numeros_restantes = etiquetas[i].id.numeros_restantes+contador;
        contador+=1;
        etiquetas[i].coordenadas_latitud.grados = 40;
        etiquetas[i].coordenadas_latitud.minutos= la_min();
        etiquetas[i].coordenadas_latitud.segundos= la_seg();
        etiquetas[i].coordenadas_longitud.grados= -3;
        etiquetas[i].coordenadas_longitud.minutos= lo_min();
        etiquetas[i].coordenadas_longitud.segundos= lo_seg();
        genDNI();
        etiquetas[i].nif.numeros = crear(etiquetas[i].nif.numeros);
        etiquetas[i].nif.letra;
    }
    for(int i=0; i<100; i++)
    {
        contador=1;
        /*cout<< "Paquete "<<i<<": "<<setw(5)<<"Id"<<setw(25)<<"Latitud"<<setw(25)<<"Longitud"<<setw(20)<<"NIF"<<setw(25)
            <<"\n\n\n\n"<<setw(15)<<etiquetas[i].id.dos_primeros<<etiquetas[i].id.letra<<setfill('0')<<setw(4)<<etiquetas[i].id.numeros_restantes<<
            setw(20)<<etiquetas[i].coordenadas_latitud.grados <<"º "<< etiquetas[i].coordenadas_latitud.minutos <<"' " <<
            etiquetas[i].coordenadas_latitud.segundos <<"'' "<<setw(13)<<etiquetas[i].coordenadas_longitud.grados <<
            "º "  << etiquetas[i].coordenadas_longitud.minutos << "' " <<etiquetas[i].coordenadas_longitud.segundos <<"'' "<<setw(20)<<
            etiquetas[i].nif.numeros<< etiquetas[i].nif.letra<<"\n\n\n\n";*/

/*
        cout<< "Paquete"<<i<<":"<<"\t\t\t\t"<<"Id"<<"\t\t\t\t"<<"Latitud"<<"\t\t\t\t"<<"Longitud"<<"\t\t\t\t"<<"NIF"<<"\t\t\t\t"
            <<"\n\n\n\n"<<"\t\t\t\t\t"<<etiquetas[i].id.dos_primeros<<etiquetas[i].id.letra<<setfill('0')<<setw(4)<<etiquetas[i].id.numeros_restantes
            <<"\t\t\t\t"<<etiquetas[i].coordenadas_latitud.grados <<"º"<< etiquetas[i].coordenadas_latitud.minutos <<"'"<<
            etiquetas[i].coordenadas_latitud.segundos <<"''"<<"\t\t\t"<<etiquetas[i].coordenadas_longitud.grados <<
            "º"<< etiquetas[i].coordenadas_longitud.minutos<< "'"<<etiquetas[i].coordenadas_longitud.segundos <<"'' "<<"\t\t\t\t"<<
            etiquetas[i].nif.numeros<< etiquetas[i].nif.letra<<"\n\n\n\n";
*/

        cout<< "Paquete "<<i<<": "<<"\t\t"<<"Id"<<"\t\t"<<"Latitud"<<"\t\t\t"<<"Longitud"<<"\t\t"<<"NIF"<<
            "\n\n\n\n"<<"\t\t\t"<<setfill('0')<<setw(2)<<etiquetas[i].id.dos_primeros<<etiquetas[i].id.letra<<setfill('0')<<setw(4)<<etiquetas[i].id.numeros_restantes
            <<"\t\t"<<setfill('0')<<setw(2)<<etiquetas[i].coordenadas_latitud.grados <<"º "<<setfill('0')<<setw(2)<<
             etiquetas[i].coordenadas_latitud.minutos <<"' " <<setfill('0')<<setw(2)<<etiquetas[i].coordenadas_latitud.segundos <<"'' "<<"\t\t"<<
             setfill('0')<<setw(2)<<etiquetas[i].coordenadas_longitud.grados <<"º "  <<setfill('0')<<setw(2)<< etiquetas[i].coordenadas_longitud.minutos <<
             "' " <<setfill('0')<<setw(2)<<etiquetas[i].coordenadas_longitud.segundos <<"'' "<<"\t\t"<<setw(1) << etiquetas[i].nif.numeros << setw(0) <<
              etiquetas[i].nif.letra<<"\n\n\n\n";
    }
}


int contador_NE_Camiones=0;
int contador_NO_Camiones=0;
int contador_SE_Camiones=0;
int contador_SO_Camiones=0;

int Colass()
{
    for(int i=0; i<100; i++)
    {
        central_la_minutos.encolar(etiquetas[i].coordenadas_latitud.minutos);
        central_lo_minutos.encolar(etiquetas[i].coordenadas_longitud.minutos);
        central_ID.encolar(etiquetas[i].id.numeros_restantes);
    }
}

int paquetes()
{
    string muelle="";
    int nu=100;
    int contador_NE=0;
    int contador_NO=0;
    int contador_SE=0;
    int contador_SO=0;


    for(int i=0; i<nu; i++)
    {
        int a = central_la_minutos.desencolar();
        int c = central_lo_minutos.desencolar();
        int d = central_ID.desencolar();
        if (48<c && 36>a)
        {
            if(contador_NE!=5)
            {
                pila1.apilar(a);
                pilaID1.apilar(d);
                muelle="NE";
                cout << "Paquete " << i << ": " << muelle<< endl;
                contador_NE+=1;
                cout<<"Grados:"<<etiquetas[i].coordenadas_latitud.grados<<"º"<<"\t\t"<<"Min:"<<etiquetas[i].coordenadas_latitud.minutos<<"'"<<"\t\t"
                    <<"Seg:"<<etiquetas[i].coordenadas_latitud.segundos<<"''"<<"\t\t"<<"ID:"<<etiquetas[i].id.dos_primeros<<
                    etiquetas[i].id.letra<<setfill('0')<<setw(4)<<etiquetas[i].id.numeros_restantes<<
                    "\t\t"<<"NIF:"<<etiquetas[i].nif.numeros<< etiquetas[i].nif.letra<<endl;
                cout<<"Contador de paquetes: "<<contador_NE<<endl;
            }
            if(contador_NE==5)
            {
                cola1.encolar(pila1.desapilar());
                cola_ID1.encolar(pilaID1.desapilar());

                cola1.encolar(pila1.desapilar());
                cola_ID1.encolar(pilaID1.desapilar());

                cola1.encolar(pila1.desapilar());
                cola_ID1.encolar(pilaID1.desapilar());

                cola1.encolar(pila1.desapilar());
                cola_ID1.encolar(pilaID1.desapilar());

                cola1.encolar(pila1.desapilar());
                cola_ID1.encolar(pilaID1.desapilar());

                cout<<"Paquete del cliente enviado: "<< cola1.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID1.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola1.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID1.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola1.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID1.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola1.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID1.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola1.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID1.desencolar()<<endl;

                contador_NE=0;

                contador_NE_Camiones+=1;
            }
        }
        else  if (48 < c && 36 < a)
        {


            if(contador_NO!=5)
            {
                pila2.apilar(a);
                pilaID2.apilar(d);
                muelle="NO";
                cout << "Paquete " << i << ": " << muelle<< endl;
                contador_NO+=1;
                cout<<"Grados:"<<etiquetas[i].coordenadas_latitud.grados<<"º"<<"\t\t"<<"Min:"<<etiquetas[i].coordenadas_latitud.minutos<<"'"<<"\t\t"
                    <<"Seg:"<<etiquetas[i].coordenadas_latitud.segundos<<"''"<<"\t\t"<<"ID:"<<etiquetas[i].id.dos_primeros<<
                    etiquetas[i].id.letra<<setfill('0')<<setw(4)<<etiquetas[i].id.numeros_restantes<<
                    "\t\t"<<"NIF:"<<etiquetas[i].nif.numeros<< etiquetas[i].nif.letra<<endl;
                cout<<"Contador de paquetes: "<<contador_NO<<endl;

            }
            if(contador_NO==5)
            {
                cola2.encolar(pila2.desapilar());
                cola_ID2.encolar(pilaID2.desapilar());

                cola2.encolar(pila2.desapilar());
                cola_ID2.encolar(pilaID2.desapilar());

                cola2.encolar(pila2.desapilar());
                cola_ID2.encolar(pilaID2.desapilar());

                cola2.encolar(pila2.desapilar());
                cola_ID2.encolar(pilaID2.desapilar());

                cola2.encolar(pila2.desapilar());
                cola_ID2.encolar(pilaID2.desapilar());


                cout<<"Paquete del cliente enviado: "<< cola2.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID2.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola2.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID2.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola2.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID2.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola2.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID2.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola2.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID2.desencolar()<<endl;

                contador_NO=0;

                contador_NO_Camiones+=1;

            }
        }
        else   if (c < 48 && 36 < a)
        {

            if(contador_SE!=5)
            {
                pila3.apilar(a);
                pilaID3.apilar(d);
                muelle="SE";
                cout << "Paquete " << i << ": " << muelle<< endl;
                contador_SE+=1;
                cout<<"Grados:"<<etiquetas[i].coordenadas_latitud.grados<<"º"<<"\t\t"<<"Min:"<<etiquetas[i].coordenadas_latitud.minutos<<"'"<<"\t\t"
                    <<"Seg:"<<etiquetas[i].coordenadas_latitud.segundos<<"''"<<"\t\t"<<"ID:"<<etiquetas[i].id.dos_primeros<<
                    etiquetas[i].id.letra<<setfill('0')<<setw(4)<<etiquetas[i].id.numeros_restantes<<
                    "\t\t"<<"NIF:"<<etiquetas[i].nif.numeros<< etiquetas[i].nif.letra<<endl;

            }
            if(contador_SE==5)
            {


                cola3.encolar(pila3.desapilar());
                cola_ID3.encolar(pilaID3.desapilar());

                cola3.encolar(pila3.desapilar());
                cola_ID3.encolar(pilaID3.desapilar());

                cola3.encolar(pila3.desapilar());
                cola_ID3.encolar(pilaID3.desapilar());

                cola3.encolar(pila3.desapilar());
                cola_ID3.encolar(pilaID3.desapilar());

                cola3.encolar(pila3.desapilar());
                cola_ID3.encolar(pilaID3.desapilar());


                cout<<"Paquete del cliente enviado: "<< cola3.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID3.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola3.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID3.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola3.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID3.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola3.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID3.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola3.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID3.desencolar()<<endl;

                contador_SE=0;

                contador_SE_Camiones+=1;

            }
        }
        else
        {
            if(contador_SO!=5)
            {
                pila4.apilar(a);
                pilaID4.apilar(d);
                muelle="SO";
                cout << "Paquete " << i << ": " << muelle<< endl;
                contador_SO+=1;
                cout<<"Grados:"<<etiquetas[i].coordenadas_latitud.grados<<"º"<<"\t\t"<<"Min:"<<etiquetas[i].coordenadas_latitud.minutos<<"'"<<"\t\t"
                    <<"Seg:"<<etiquetas[i].coordenadas_latitud.segundos<<"''"<<"\t\t"<<"ID:"<<etiquetas[i].id.dos_primeros<<
                    etiquetas[i].id.letra<<setfill('0')<<setw(4)<<etiquetas[i].id.numeros_restantes<<
                    "\t\t"<<"NIF:"<<etiquetas[i].nif.numeros<< etiquetas[i].nif.letra<<endl;
                cout<<"Contador de paquetes: "<<contador_SO<<endl;
            }
            if(contador_SO==5)
            {


                cola4.encolar(pila4.desapilar());
                cola_ID4.encolar(pilaID4.desapilar());

                cola4.encolar(pila4.desapilar());
                cola_ID4.encolar(pilaID4.desapilar());

                cola4.encolar(pila4.desapilar());
                cola_ID4.encolar(pilaID4.desapilar());

                cola4.encolar(pila4.desapilar());
                cola_ID4.encolar(pilaID4.desapilar());

                cola4.encolar(pila4.desapilar());
                cola_ID4.encolar(pilaID4.desapilar());


                cout<<"Paquete del cliente enviado: "<<cola4.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID4.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola4.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID4.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola4.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID4.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola4.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID4.desencolar()<<endl;

                cout<<"Paquete del cliente enviado: "<<cola4.desencolar()<<"''"<<"   "<<"Pertenece al Paquete: "<<setfill('0')<<setw(4)<<cola_ID4.desencolar()<<endl;

                contador_SO=0;

                contador_SO_Camiones+=1;

            }
        }
    }

}



int camiones()
{
    cout<<"Numero De Camiones Llenos NE: "<<contador_NE_Camiones<<endl<<endl;
    cout<<"Numero De Camiones Llenos NO: "<<contador_NO_Camiones<<endl<<endl;
    cout<<"Numero De Camiones Llenos SE: "<<contador_SE_Camiones<<endl<<endl;
    cout<<"Numero De Camiones Llenos SO: "<<contador_SO_Camiones<<endl<<endl;


}


#endif // PAQUETES_H_INCLUDED
