#include <iostream>
using namespace std;

class Celular {
private:
    string marca;
    string modelo;
    int bateria;

public:

    string getMarca() const {
        return marca;
    }

    string getModelo() const {
        return modelo;
    }

    int getBateria() const {
        return bateria;
    }


    void setMarca(string m) {
        marca = m;
    }

    void setModelo(string m) {
        modelo = m;
    }

    void setBateria(int b) {
        if (b >= 0 && b <= 100) {
            bateria = b;
        } else {
            cout << "Valor de bateria invalido. Debe estar entre 0 y 100.\n";
        }
    }

    void mostrarInfo() const {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Bateria: " << bateria << "%" << endl;
        cout << "-------------------" << endl;
    }
};

int main() {

    Celular cel1;

    cel1.setMarca("Motorola");
    cel1.setModelo("G84");
    cel1.setBateria(70);

    cel1.setBateria(150);
    cel1.setBateria(-20);

    cel1.mostrarInfo();

    return 0;
}

/*
El encapsulamiento protege los datos internos del objeto y evita modificaciones incorrectas. 
Los getters y setters permiten controlar cómo se accede y modifica la información.
*/