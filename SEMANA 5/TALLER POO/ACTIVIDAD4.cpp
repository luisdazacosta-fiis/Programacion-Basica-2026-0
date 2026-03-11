#include <iostream>
using namespace std;

class Celular {
private:
    string marca;
    string modelo;
    int bateria;

public:

    Celular() {
        marca = "Desconocida,";
        modelo = "Generico,";
        bateria = 100;
    }

    Celular(string marca, string modelo) {
        this->marca = marca;
        this->modelo = modelo;
        bateria = 100;
    }

    Celular(string marca, string modelo, int bateria) {
        this->marca = marca;
        this->modelo = modelo;

        if (bateria >= 0 && bateria <= 100)
            this->bateria = bateria;
        else
            this->bateria = 100;
    }

    void mostrarInfo() const {
        cout << "Marca: " << marca
             << " Modelo: " << modelo
             << " Bateria: " << bateria << "%\n";
    }
};

int main() {

    Celular c1;  
    Celular c2("Samsung,", "S23,");
    Celular c3("Apple,", "iPhone 15,", 90);

    c1.mostrarInfo();
    c2.mostrarInfo();
    c3.mostrarInfo();

    return 0;
}

/*
La sobrecarga permite crear objetos de diferentes maneras según la información disponible. 
*/