#include <iostream>
using namespace std;

class Persona {
protected:
    string nombre;
    int edad;

public:
    Persona(string nombre, int edad) {
        this->nombre = nombre;
        this->edad = (edad >= 0) ? edad : 0;
    }

    virtual void rol() {
        cout << "Soy una persona" << endl;
    }
};

class Estudiante : public Persona {
public:
    Estudiante(string nombre, int edad)
        : Persona(nombre, edad) {}

    void rol() override {
        cout << "Soy estudiante" << endl;
    }
};

class Profesor : public Persona {
public:
    Profesor(string nombre, int edad)
        : Persona(nombre, edad) {}

    void rol() override {
        cout << "Soy profesor" << endl;
    }
};

int main() {

    Persona* personas[2];

    personas[0] = new Estudiante("Alessandro", 20);
    personas[1] = new Profesor("Carlos", 45);

    for (int i = 0; i < 2; i++) {
        personas[i]->rol(); 
    }

    delete personas[0];
    delete personas[1];

    return 0;
}

/*
El polimorfismo permite que diferentes objetos respondan de manera distinta al mismo método. 
*/