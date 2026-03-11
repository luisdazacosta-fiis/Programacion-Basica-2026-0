#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Libro {
    int id;
    string titulo;
    string autor;
    int anio;
    bool disponible;
};

struct Usuario {
    int id;
    string nombre;
    string carrera;
};

Libro* buscarLibroPorId(Libro* lista, int cantidad, int idBuscado) {
    for (int i = 0; i < cantidad; i++) {
        if (lista[i].id == idBuscado) {
            return &lista[i]; 
        }
    }
    return nullptr; 
}

void redimensionarLibros(Libro* &lista, int &capacidad) {
    int nuevaCap = capacidad * 2;
    Libro* nuevaLista = new Libro[nuevaCap];
    
    for (int i = 0; i < capacidad; i++) {
        nuevaLista[i] = lista[i]; 
    }
    
    delete[] lista; 
    lista = nuevaLista;
    capacidad = nuevaCap;
}

void agregarLibro(Libro* &lista, int &cant, int &cap) {
    if (cant == cap) {
        redimensionarLibros(lista, cap);
    }
    cout << "Ingrese ID: "; cin >> lista[cant].id;
    cout << "Titulo: "; cin.ignore(); getline(cin, lista[cant].titulo);
    cout << "Autor: "; getline(cin, lista[cant].autor);
    cout << "Anio: "; cin >> lista[cant].anio;
    lista[cant].disponible = true;
    cant++;
    cout << "Libro registrado con exito.\n";
}

void listarLibros(Libro* lista, int cant) {
    cout << "\n--- LISTADO DE LIBROS (REQ. A) ---" << endl;
    for (int i = 0; i < cant; i++) {
        cout << "ID: " << lista[i].id << " | " << lista[i].titulo 
             << " [" << (lista[i].disponible ? "Disponible" : "Prestado") << "]" << endl;
    }
}

void buscarLibrosPorTexto(Libro* lista, int cant) {
    string busqueda;
    cout << "Texto a buscar (titulo o autor): ";
    cin.ignore(); getline(cin, busqueda);
    bool encontrado = false;
    for (int i = 0; i < cant; i++) {
        if (lista[i].titulo.find(busqueda) != string::npos || lista[i].autor.find(busqueda) != string::npos) {
            cout << "Encontrado: " << lista[i].titulo << " - " << lista[i].autor << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontraron coincidencias." << endl;
}

int main() {
    int capL = 5, cantL = 0;
    Libro* libros = new Libro[capL];

    libros[cantL++] = {101, "Cien Anios de Soledad", "Garcia Marquez", 1967, true};
    libros[cantL++] = {102, "Don Quijote", "Miguel de Cervantes", 1605, true};
    libros[cantL++] = {103, "Rayuela", "Julio Cortazar", 1963, true};
    libros[cantL++] = {104, "El Aleph", "Jorge Luis Borges", 1949, true};
    libros[cantL++] = {105, "Pedro Paramo", "Juan Rulfo", 1955, true};

    int opcion = 0;
    while (opcion != 6) {
        cout << "\n--- MENU SISTEMA BIBLIOTECA ---" << endl;
        cout << "1. Registrar / Listar Libros" << endl;
        cout << "2. Registrar Usuarios" << endl;
        cout << "3. Prestar / Devolver Libro" << endl;
        cout << "4. Consultar libros" << endl;
        cout << "5. Guardar datos" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: "; cin >> opcion;

        if (opcion == 1) {
            int sub;
            cout << "1. Agregar nuevo\n2. Ver todos\nOpcion: "; cin >> sub;
            if (sub == 1) agregarLibro(libros, cantL, capL);
            else listarLibros(libros, cantL);
        }
        else if (opcion == 3) {
            int sub, idB;
            cout << "1. Prestar\n2. Devolver\nOpcion: "; cin >> sub;
            cout << "Ingrese ID del libro: "; cin >> idB;
            Libro* l = buscarLibroPorId(libros, cantL, idB);
            if (l != nullptr) {
                if (sub == 1) {
                    if (l->disponible) { l->disponible = false; cout << "Libro prestado."; }
                    else cout << "El libro ya esta prestado.";
                } else {
                    l->disponible = true; cout << "Libro devuelto.";
                }
            } else cout << "Libro no encontrado.";
        }
        else if (opcion == 4) buscarLibrosPorTexto(libros, cantL);
        else if (opcion == 5) {
            ofstream archivo("datos.txt");
            for (int i = 0; i < cantL; i++) {
                archivo << libros[i].id << "," << libros[i].titulo << "," << libros[i].disponible << endl;
            }
            archivo.close();
            cout << "Datos guardados con exito.";
        }
    }

    delete[] libros; 
    return 0;
}

/*
==================== BITÁCORA IA ====================
Herramienta IA usada: Gemini
Objetivo del uso: Resolver dudas sobre la gestion manual de arreglos y punteros. 

Preguntas que hice a la IA (resumen):
1) ¿Como hacer que un arreglo crezca sin usar vectores en C++? 
2) ¿Como funciona el retorno de un puntero en una funcion de busqueda? 
3) ¿Como buscar una palabra dentro de un string? 

Qué sugerencias acepté y por qué: 
- Acepté usar la reallocacion manual (crear arreglo nuevo, copiar y borrar el viejo) porque es un requisito obligatorio del examen.
- Acepté usar punteros para la busqueda porque facilita modificar el estado del libro directamente.

Qué sugerencias rechacé y por qué:
- Rechacé usar clases avanzadas para que el codigo sea mas sencillo y facil de explicar.

Test manual diseñado por mí:
Entrada (pasos/comandos): 
- Agregar un libro con ID 10. Luego usar la opcion 3 para prestarlo.
Salida esperada:
- El sistema debe confirmar el prestamo y marcarlo como "Prestado" en la lista.

Nota de autoría: Afirmo que entiendo cierta parte del código entregado y puedo explicarlo, aunque debo admitir que la IA tambien influyo mucho en el desarrollo de mi programa.
*/