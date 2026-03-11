#include <iostream>
using namespace std;

class Vehiculo {
private:
    string marca;
    int velocidadMax;

public:
    Vehiculo(string m, int v) {
        marca = m;
        velocidadMax = v;
    }

    string getMarca() {
        return marca;
    }

    int getVelocidadMax() {
        return velocidadMax;
    }

    void setMarca(string m) {
        marca = m;
    }

    void setVelocidadMax(int v) {
        if (v > 0)
            velocidadMax = v;
    }

    void mostrarInfo() {
        cout << "Marca: " << marca << endl;
        cout << "Velocidad Max: " << velocidadMax << " km/h" << endl;
    }
};

class Carro : public Vehiculo {
private:
    int puertas;

public:
    Carro(string m, int v, int p) : Vehiculo(m, v) {
        puertas = p;
    }

    int getPuertas() {
        return puertas;
    }

    void setPuertas(int p) {
        if (p > 0)
            puertas = p;
    }

    void mostrarInfo() {
        Vehiculo::mostrarInfo();
        cout << "Puertas: " << puertas << endl;
    }
};

class Moto : public Vehiculo {
private:
    int cilindraje;

public:
    Moto(string m, int v, int c) : Vehiculo(m, v) {
        cilindraje = c;
    }

    int getCilindraje() {
        return cilindraje;
    }

    void setCilindraje(int c) {
        if (c > 0)
            cilindraje = c;
    }

    void mostrarInfo() {
        Vehiculo::mostrarInfo();
        cout << "Cilindraje: " << cilindraje << " cc" << endl;
    }
};

int main() {

    Carro carro1("Toyota", 180, 4);
    Moto moto1("Yamaha", 220, 600);

    cout << "=== CARRO ===" << endl;
    carro1.mostrarInfo();

    cout << "\n=== MOTO ===" << endl;
    moto1.mostrarInfo();

    return 0;
}

/*
La herencia reduce la repetición de código al colocar los atributos y métodos comunes en una clase base y dejar lo específico en las clases derivadas. 
*/