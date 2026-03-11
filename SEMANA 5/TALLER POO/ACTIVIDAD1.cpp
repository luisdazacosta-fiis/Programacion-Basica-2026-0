#include <iostream>
using namespace std;

class Celular {
public:
    string marca;
    string modelo;
    int bateria;

    void mostrarInfo() {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Bateria: " << bateria << "%" << endl;
        cout << "-------------------" << endl;
    }
};

int main() {

    Celular cel1;
    Celular cel2;

    cel1.marca = "Huawei";
    cel1.modelo = "P10 Lite";
    cel1.bateria = 81;

    cel2.marca = "iPhone";
    cel2.modelo = "15 Pro Max";
    cel2.bateria = 95;

    cel1.mostrarInfo();
    cel2.mostrarInfo();

    return 0;
}

/*
Crear una clase permite organizar la información en un solo bloque lógico. 
Entendí que una clase es como un molde y los objetos son las instancias creadas a partir de ese molde.
*/