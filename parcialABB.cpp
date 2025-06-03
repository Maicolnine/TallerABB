// Michael Stwar Murillo Ruiz  Cesar Alberto Agudelo
#include <iostream>
#include <cstring> // Solo para getline
using namespace std;

struct nodo {
    char nombre[30];
    int fecha;
    char genero[30];
    double dinero;
    nodo *izquierdo;
    nodo *derecho;
};

nodo *raiz = NULL;

// Crear película
nodo* crearPelicula() {
    nodo *nueva = new nodo;
    cout << "Nombre de la pelicula: ";
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

// Insertar nodo según fecha (menor o igual a la izquierda, mayor a la derecha)
void insertarPelicula(nodo *&raiz, nodo *nueva) {
    if (raiz == NULL) {
        raiz = nueva;
    } else if (nueva->fecha <= raiz->fecha) {
        insertarPelicula(raiz->izquierdo, nueva);
    } else {
        insertarPelicula(raiz->derecho, nueva);
    }
}

// Mostrar en inorden
void mostrarInorden(nodo *raiz) {
    if (raiz == NULL) return;
    mostrarInorden(raiz->izquierdo);    // izquierda
    cout << "\nNombre: " << raiz->nombre
         << " | Fecha: " << raiz->fecha
         << " | Genero: " << raiz->genero
         << " | Dinero: " << raiz->dinero << "M\n";
    mostrarInorden(raiz->derecho);      // derecha
}


// Mostrar en preorden
void mostrarPreorden(nodo *raiz) {
    if (raiz == NULL) return;
    cout << "\nNombre: " << raiz->nombre
         << " | Fecha: " << raiz->fecha
         << " | Genero: " << raiz->genero
         << " | Dinero: " << raiz->dinero << "M\n";
    mostrarPreorden(raiz->izquierdo);   // izquierda
    mostrarPreorden(raiz->derecho);     // derecha
}

// Mostrar en postorden con formato jerárquico
void mostrarJerarquico(nodo *raiz, int nivel) {
    if (raiz == NULL) return;
    mostrarJerarquico(raiz->derecho, nivel + 1);
    for (int i = 0; i < nivel; i++) cout << "       ";
    cout << raiz->nombre << endl;
    mostrarJerarquico(raiz->izquierdo, nivel + 1);
}

void mostrarPostorden(nodo *raiz) {
    if (raiz == NULL) {
        cout << "Arbol vacio.\n";
        return;
    }
    cout << "\nÁrbol Jerárquico:\n\n";
    mostrarJerarquico(raiz, 0);
}

// Comparar cadenas sin usar strcmp
bool compararCadenas(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

// Mostrar películas por género
void mostrarPorGenero(nodo *raiz, char generoBuscado[]) {
    if (raiz == NULL) return;

    mostrarPorGenero(raiz->izquierdo, generoBuscado);

    if (compararCadenas(raiz->genero, generoBuscado)) {
        cout << "\nNombre: " << raiz->nombre
            << " | Fecha: " << raiz->fecha
            << " | Genero: " << raiz->genero
            << " | Dinero: " << raiz->dinero << "M\n";
    }

    mostrarPorGenero(raiz->derecho, generoBuscado);
}

// Encontrar el mínimo nodo (el más a la izquierda)
nodo* buscarMinimo(nodo *raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->izquierdo != NULL)
        raiz = raiz->izquierdo;
    return raiz;
}

// Eliminar un nodo por nombre
void eliminarPelicula(nodo *&raiz, char nombreEliminar[]) {
    if (raiz == NULL) return;

    // Si el nodo actual es el que queremos eliminar
    if (compararCadenas(nombreEliminar, raiz->nombre)) {
        // Caso hoja
        if (raiz->izquierdo == NULL && raiz->derecho == NULL) {
            delete raiz;
            raiz = NULL;
        }
        // Solo hijo derecho
        else if (raiz->izquierdo == NULL) {
            nodo *temp = raiz;
            raiz = raiz->derecho;
            delete temp;
        }
        // Solo hijo izquierdo
        else if (raiz->derecho == NULL) {
            nodo *temp = raiz;
            raiz = raiz->izquierdo;
            delete temp;
        }
        // Dos hijos
        else {
            nodo *minimo = buscarMinimo(raiz->derecho);
            strcpy(raiz->nombre, minimo->nombre);
            raiz->fecha = minimo->fecha;
            strcpy(raiz->genero, minimo->genero);
            raiz->dinero = minimo->dinero;
            eliminarPelicula(raiz->derecho, minimo->nombre);
        }
    } else {
        // Recorrer ambos subárboles para buscar el nombre
        eliminarPelicula(raiz->izquierdo, nombreEliminar);
        eliminarPelicula(raiz->derecho, nombreEliminar);
    }
}


int main() {
    int opcion;

    do {
        cout << "\nMENU DE PELIS\n";
        cout << "1. Insertar pelicula\n";
        cout << "2. Mostrar peliculas\n";
        cout << "3. Mostrar peliculas por genero\n";
        cout << "4. Eliminar pelicula\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                nodo *pelicula = crearPelicula();
                insertarPelicula(raiz, pelicula);
                break;
            }
            case 2: {
                int subopcion;
                cout << "Mostrar peliculas:\n";
                cout << "1. Inorden\n";
                cout << "2. Preorden\n";
                cout << "3. Postorden (Jerarquico)\n";
                cout << "Opcion: ";
                cin >> subopcion;
                cin.ignore();

                if (subopcion == 1) mostrarInorden(raiz);
                else if (subopcion == 2) mostrarPreorden(raiz);
                else if (subopcion == 3) mostrarPostorden(raiz);
                else cout << "Opcion invalida.\n";
                break;
            }
            case 3: {
                char genero[30];
                cout << "Ingrese el genero: ";
                cin.getline(genero, 30);
                mostrarPorGenero(raiz, genero);
                break;
            }
            case 4: {
                char nombre[30];
                cout << "Ingrese el nombre de la pelicula a eliminar: ";
                cin.getline(nombre, 30);
                eliminarPelicula(raiz, nombre);
                break;
            }
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);

    return 0;
}
