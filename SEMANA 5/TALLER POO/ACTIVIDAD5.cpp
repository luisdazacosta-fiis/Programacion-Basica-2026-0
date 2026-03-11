#include <iostream>
using namespace std;

class Persona {
private:
    string nombre;
    int edad;

public:

    Persona(string nombre, int edad) {
        this->nombre = nombre;
        setEdad(edad);
    }


    string getNombre() {
        return nombre;
    }

    void setNombre(string nombre) {
        this->nombre = nombre;
    }


    int getEdad() {
        return edad;
    }

    void setEdad(int edad) {
        if (edad >= 0)
            this->edad = edad;
        else
            this->edad = 0;
    }


    void mostrar() {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
    }
};

class Estudiante : public Persona {
private:
    string carrera;

public:
    Estudiante(string nombre, int edad, string carrera)
        : Persona(nombre, edad) {
        this->carrera = carrera;
    }

    void estudiar() {
        cout << getNombre() << " esta estudiando " << carrera << endl;
    }
};

class Profesor : public Persona {
private:
    string materia;

public:
    Profesor(string nombre, int edad, string materia)
        : Persona(nombre, edad) {
        this->materia = materia;
    }

    void enseniar() {
        cout << getNombre() << " esta enseniando " << materia << endl;
    }
};

int main() {

    Estudiante e1("Alessandro", 20, "Ingenieria de Sistemas");
    Profesor p1("Carlos", 45, "Programacion");

    cout << "----- ESTUDIANTE -----" << endl;
    e1.mostrar();
    e1.estudiar();

    cout << "\n----- PROFESOR -----" << endl;
    p1.mostrar();
    p1.enseniar();

    return 0;
}

/*
La herencia permite reutilizar código y evitar repetir atributos y métodos en distintas clases. 
*/