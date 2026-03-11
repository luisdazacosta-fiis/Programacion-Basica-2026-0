#include <iostream>
using namespace std;

class Celular {
private:
    string marca;
    string modelo;
    int bateria;

public:

    string getMarca() const { return marca; }
    string getModelo() const { return modelo; }
    int getBateria() const { return bateria; }

    void setMarca(string marca) {
        this->marca = marca;
    }

    void setModelo(string modelo) {
        this->modelo = modelo;
    }

    void setBateria(int bateria) {
        if (bateria >= 0 && bateria <= 100)
            this->bateria = bateria;
        else
            cout << "Error: bateria invalida\n";
    }
};

int main() {

    Celular cel1;

    cel1.setMarca("Apple");
    cel1.setModelo("iPhone 15");
    cel1.setBateria(95);

    cout << cel1.getMarca() << endl;
    cout << cel1.getModelo() << endl;
    cout << cel1.getBateria() << "%" << endl;

    return 0;
}

/*
El constructor permite inicializar los atributos del objeto desde el momento en que se crea.
Es importante porque garantiza que el objeto tenga valores válidos desde el inicio.
*/