#include <iostream>
#include <string>
using namespace std;

int main() {
    string nombre, carrera;
    int edad;

    cout << "Ingrese su nombre completo: ";
    getline(cin, nombre);

    cout << "Ingrese su edad: ";
    cin >> edad;

    cout << "Ingrese su carrera: ";
    getline(cin, carrera);

    cout << "\n--- FORMULARIO REGISTRADO ---\n";
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << endl;
    cout << "Carrera: " << carrera << endl;

    return 0;
}