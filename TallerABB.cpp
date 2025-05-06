// Michael Stwar Murillo Ruiz  Cesar Alberto Agudelo
#include <iostream>
#include <cstring> // Solo para strcmp
using namespace std;

// 1. Definición de nodo
struct nodo {
    char nombre[30];
    int fecha;
    char genero[30];
    double dinero;
    nodo *izquierdo;
    nodo *derecho;
};

// 2. Raíz global
nodo *raiz = NULL;

// 3. Funciones
nodo* crearPelicula();
void insertarPelicula(nodo *&raiz, nodo *nueva);
void mostrarInorden(nodo *raiz);
void mostrarPreorden(nodo *raiz);
void mostrarPostorden(nodo *raiz);
void imprimirJerarquico(nodo *raiz, int nivel = 0);
void mostrarPorGenero(nodo *raiz, char generoBuscado[]);
void encontrarFracasos(nodo *raiz, nodo *&primero, nodo *&segundo, nodo *&tercero);

// 4. Menú principal
int main() {
    int opcion;
    do {
        cout << "\nMENU DE PELIS" << endl;
        cout << "1. Insertar pelicula" << endl;
        cout << "2. Mostrar peliculas" << endl;
        cout << "3. Mostrar peliculas por genero" << endl;
        cout << "4. Mostrar 3 fracasos taquilleros" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                nodo *pelicula = crearPelicula();
                if (pelicula != NULL)
                    insertarPelicula(raiz, pelicula);
                break;
            }
            case 2: {
                int tipo;
                cout << "\nMostrar peliculas:" << endl;
                cout << "1. Inorden (Antiguas a recientes)" << endl;
                cout << "2. Preorden (Peliculas y secuelas)" << endl;
                cout << "3. Postorden (Árbol jerárquico)" << endl;
                cout << "Opcion: ";
                cin >> tipo;
                cin.ignore();

                if (tipo == 1) mostrarInorden(raiz);
                else if (tipo == 2) mostrarPreorden(raiz);
                else if (tipo == 3) mostrarPostorden(raiz);
                else cout << "Opcion no valida." << endl;
                break;
            }
            case 3: {
                char generoBuscado[30];
                cout << "Ingrese el genero que desea buscar: ";
                cin.getline(generoBuscado, 30);
                mostrarPorGenero(raiz, generoBuscado);
                break;
            }
            case 4: {
                nodo *primero = NULL;
                nodo *segundo = NULL;
                nodo *tercero = NULL;
                encontrarFracasos(raiz, primero, segundo, tercero);

                cout << "\nTop 3 fracasos taquilleros:\n";

                if (primero != NULL) {
                    cout << "\nNombre: " << primero->nombre;
                    cout << " | Fecha: " << primero->fecha;
                    cout << " | Genero: " << primero->genero;
                    cout << " | Dinero: " << primero->dinero << "M\n";
                }
                if (segundo != NULL) {
                    cout << "\nNombre: " << segundo->nombre;
                    cout << " | Fecha: " << segundo->fecha;
                    cout << " | Genero: " << segundo->genero;
                    cout << " | Dinero: " << segundo->dinero << "M\n";
                }
                if (tercero != NULL) {
                    cout << "\nNombre: " << tercero->nombre;
                    cout << " | Fecha: " << tercero->fecha;
                    cout << " | Genero: " << tercero->genero;
                    cout << " | Dinero: " << tercero->dinero << "M\n";
                }
                break;
            }
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}

// -------------- Funciones Básicas -------------------

nodo* crearPelicula() {
    nodo *nueva = new nodo;
    if (nueva == NULL) {
        cout << "Error al asignar memoria." << endl;
        return NULL;
    }
    cout << "Nombre de la pelicula: ";
    cin.ignore();
    cin.getline(nueva->nombre, 30);
    cout << "Fecha de realizacion: ";
    cin >> nueva->fecha;
    cin.ignore();
    cout << "Genero: ";
    cin.getline(nueva->genero, 30);
    cout << "Dinero recaudado (en millones): ";
    cin >> nueva->dinero;
    cin.ignore();

    nueva->izquierdo = NULL;
    nueva->derecho = NULL;
    return nueva;
}

void insertarPelicula(nodo *&raiz, nodo *nueva) {
    if (raiz == NULL) {
        raiz = nueva;
    } else if (nueva->fecha <= raiz->fecha) {
        insertarPelicula(raiz->izquierdo, nueva);
    } else {
        insertarPelicula(raiz->derecho, nueva);
    }
}

void mostrarInorden(nodo *raiz) {
    if (raiz == NULL) return;
    mostrarInorden(raiz->izquierdo);
    cout << "\nNombre: " << raiz->nombre
         << " | Fecha: " << raiz->fecha
         << " | Genero: " << raiz->genero
         << " | Dinero: " << raiz->dinero << "M\n";
    mostrarInorden(raiz->derecho);
}

void mostrarPreorden(nodo *raiz) {
    if (raiz == NULL) return;
    cout << "\nNombre: " << raiz->nombre
         << " | Fecha: " << raiz->fecha
         << " | Genero: " << raiz->genero
         << " | Dinero: " << raiz->dinero << "M\n";
    mostrarPreorden(raiz->izquierdo);
    mostrarPreorden(raiz->derecho);
}

void mostrarPostorden(nodo *raiz) {
    if (raiz == NULL) {
        cout << "Arbol vacio.\n";
        return;
    }
    cout << "\nÁrbol Jerárquico:\n\n";
    imprimirJerarquico(raiz, 0);
}

void imprimirJerarquico(nodo *raiz, int nivel) {
    if (raiz == NULL) return;

    if (raiz->derecho != NULL) {
        imprimirJerarquico(raiz->derecho, nivel + 1);
    }

    for (int i = 0; i < nivel; i++) {
        cout << "       ";
    }
    cout << raiz->nombre << endl;

    if (raiz->izquierdo != NULL) {
        for (int i = 0; i < nivel; i++) {
            cout << "       ";
        }
        cout << "/" << endl;
        imprimirJerarquico(raiz->izquierdo, nivel + 1);
    }
}

// -------------- Mostrar Peliculas por Genero -------------------

void mostrarPorGenero(nodo *raiz, char generoBuscado[]) {
    if (raiz == NULL) return;

    mostrarPorGenero(raiz->izquierdo, generoBuscado);

    bool esIgual = true;
    int i = 0;
    while (generoBuscado[i] != '\0' && raiz->genero[i] != '\0') {
        if (generoBuscado[i] != raiz->genero[i]) {
            esIgual = false;
            break;
        }
        i++;
    }
    if (generoBuscado[i] != '\0' || raiz->genero[i] != '\0') {
        esIgual = false;
    }

    if (esIgual) {
        cout << "\nNombre: " << raiz->nombre
    << " | Fecha: " << raiz->fecha
    << " | Genero: " << raiz->genero
    << " | Dinero: " << raiz->dinero << "M\n";
    }

    mostrarPorGenero(raiz->derecho, generoBuscado);
}

// -------------- Encontrar 3 fracasos -------------------

void encontrarFracasos(nodo *raiz, nodo *&aux1, nodo *&aux2, nodo *&aux3) {
    if (raiz == NULL) return;

    // Recorrer el lado izquierdo
    encontrarFracasos(raiz->izquierdo, aux1, aux2, aux3);

    // Comparar el dinero recaudado
    if (aux1 == NULL || raiz->dinero < aux1->dinero) {
        aux3 = aux2;
        aux2 = aux1;
        aux1 = raiz;
    } else if (aux2 == NULL || raiz->dinero < aux2->dinero) {
        aux3 = aux2;
        aux2 = raiz;
    } else if (aux3 == NULL || raiz->dinero < aux3->dinero) {
        aux3 = raiz;
    }

    // Recorrer el lado derecho
    encontrarFracasos(raiz->derecho, aux1, aux2, aux3);
}
