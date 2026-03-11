#include <iostream>
#include <vector>
using namespace std;

class Vehiculo {
protected:
    int id;
    double velocidad;

public:
    Vehiculo(int id, double velocidad) {
        this->id = id;
        this->velocidad = velocidad;
    }

    virtual void moverse() = 0;

    virtual void mostrarInfo() {
        cout << "ID: " << id << endl;
        cout << "Velocidad: " << velocidad << " km/h" << endl;
    }

    virtual ~Vehiculo() {
        cout << "Destructor de Vehiculo\n";
    }

    friend class Reporte;
};

class Auto : public Vehiculo {
private:
    int numeroPuertas;

public:
    Auto(int id, double velocidad, int puertas)
        : Vehiculo(id, velocidad), numeroPuertas(puertas) {}

    void moverse() override {
        cout << "El Auto se mueve por la carretera.\n";
    }

    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << "Numero de puertas: " << numeroPuertas << endl;
    }
};

class Drone : public Vehiculo {
private:
    double altitudMaxima;

public:
    Drone(int id, double velocidad, double altitud)
        : Vehiculo(id, velocidad), altitudMaxima(altitud) {}

    void moverse() override {
        cout << "El Drone vuela en el aire.\n";
    }

    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << "Altitud maxima: " << altitudMaxima << " metros\n";
    }
};

class Camion : public Vehiculo {
private:
    double capacidadCarga;

public:
    Camion(int id, double velocidad, double carga)
        : Vehiculo(id, velocidad), capacidadCarga(carga) {}

    void moverse() override {
        cout << "El Camion transporta carga pesada.\n";
    }

    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << "Capacidad de carga: " << capacidadCarga << " toneladas\n";
    }
};

class Reporte {
public:
    static void generarReporte(Vehiculo* v) {
        cout << "=== REPORTE INTERNO ===\n";
        cout << "ID: " << v->id << endl;
        cout << "Velocidad: " << v->velocidad << endl;
    }
};

template <typename T>
T calcularEficiencia(T consumo, T distancia) {
    return distancia / consumo;
}

int main() {

    vector<Vehiculo*> flota;

    flota.push_back(new Auto(1, 120, 4));
    flota.push_back(new Drone(2, 80, 500));
    flota.push_back(new Camion(3, 90, 20));

    for (Vehiculo* v : flota) {
        v->mostrarInfo();
        v->moverse();
        Reporte::generarReporte(v);
        cout << "-----------------\n";
    }

    cout << "Eficiencia: " << calcularEficiencia(10.0, 150.0) << endl;

    for (Vehiculo* v : flota) {
        delete v;
    }

    return 0;
}

/*
- ¿Qué ocurre si eliminamos virtual del destructor? 
Se ejecutaría solo el destructor de la clase base.

- ¿Qué sucede si quitamos override? 
El programa compila, pero si escribes mal el nombre del método, no sobrescribe.

- ¿Qué diferencia existe entre usar punteros y objetos directos?
La diferencia es que al usar objetos directos se produce object slicing y no se ejecuta el polimorfismo dinámico correctamente. 
En cambio, al usar punteros a la clase base, se conserva el comportamiento dinámico gracias a la tabla virtual (vtable)

*/