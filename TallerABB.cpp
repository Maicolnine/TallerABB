#include <iostream>
using namespace std;


struct nodo{

    char nombre [30];
    int fecha;
    char genero[15];
    int Dinero;

    nodo *izquierdo;
    nodo *Derecho;

};

struct nodo *raiz, *aux;

void insertarpelicula(struct nodo *nuevaPelicula){
    if (aux->nombre<nuevaPelicula->nombre){
        if(nuevaPelicula->izquierdo == NULL) {
            nuevaPelicula->izquierdo == aux;
        } else {
                insertarpelicula(nuevaPelicula->izquierdo);
        }
    } else  {
        if(nuevaPelicula->Derecho == NULL) {
            nuevaPelicula->Derecho = aux;
        }
    }
}

int main(){
    int opcion;

    do {
        cout << "\n MENU DE PELIS XDDD \n" << endl;
        cout << "1. Insertar pelicula." << endl;
        cout << "2. Buscar Pelicula." << endl;
        cout << "3. Generos." << endl;
        cout << "4. Fracasos taquilleros..." << endl;
        cout << "5. Salir."
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1:
                insertarpelicula();
                break;
        }
    }
        return
}