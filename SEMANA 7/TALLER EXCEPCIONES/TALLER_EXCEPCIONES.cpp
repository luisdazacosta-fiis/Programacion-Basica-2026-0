#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

class CuentaNoEncontrada : public runtime_error {
public:
    CuentaNoEncontrada(const string& mensaje)
        : runtime_error(mensaje) {}
};

class CuentaBancaria {
private:
    int numeroCuenta;
    string titular;
    double saldo;

public:
    CuentaBancaria(int numero, string nombre, double saldoInicial)
        : numeroCuenta(numero), titular(nombre), saldo(saldoInicial) {}

    void depositar(double monto) {
        if (monto <= 0)
            throw invalid_argument("El monto a depositar debe ser positivo.");
        saldo += monto;
    }

    void retirar(double monto) {
        if (monto <= 0)
            throw invalid_argument("El monto a retirar debe ser positivo.");
        if (monto > saldo)
            throw runtime_error("Saldo insuficiente.");
        saldo -= monto;
    }

    double consultarSaldo() const {
        return saldo;
    }

    int getNumeroCuenta() const {
        return numeroCuenta;
    }

    void mostrar() const {
        cout << "Cuenta: " << numeroCuenta
             << " | Titular: " << titular
             << " | Saldo: " << saldo << endl;
    }
};

class Banco {
private:
    vector<CuentaBancaria> cuentas;

public:
    void agregarCuenta(int numero, string titular, double saldoInicial) {
        cuentas.emplace_back(numero, titular, saldoInicial);
    }

    CuentaBancaria& buscarCuenta(int numero) {
        for (auto& cuenta : cuentas) {
            if (cuenta.getNumeroCuenta() == numero)
                return cuenta;
        }
        throw CuentaNoEncontrada("Cuenta no encontrada.");
    }

    void mostrarCuentas() const {
        for (const auto& cuenta : cuentas) {
            cuenta.mostrar();
        }
    }
};

int main() {
    Banco banco;
    int opcion;

    do {
        try {
            cout << "\n--- SISTEMA BANCARIO ---\n";
            cout << "1. Crear cuenta\n";
            cout << "2. Depositar dinero\n";
            cout << "3. Retirar dinero\n";
            cout << "4. Consultar saldo\n";
            cout << "5. Mostrar todas las cuentas\n";
            cout << "6. Salir\n";
            cout << "Seleccione una opcion: ";
            
            if (!(cin >> opcion)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw out_of_range("Entrada invalida. Debe ingresar un numero.");
            }

            if (opcion < 1 || opcion > 6)
                throw out_of_range("Opcion fuera de rango.");

            if (opcion == 1) {
                int numero;
                string titular;
                double saldo;

                cout << "Numero de cuenta: ";
                cin >> numero;
                cout << "Titular: ";
                cin >> titular;
                cout << "Saldo inicial: ";
                cin >> saldo;

                banco.agregarCuenta(numero, titular, saldo);
                cout << "Cuenta creada correctamente.\n";
            }

            else if (opcion == 2) {
                int numero;
                double monto;

                cout << "Numero de cuenta: ";
                cin >> numero;
                cout << "Monto a depositar: ";
                cin >> monto;

                banco.buscarCuenta(numero).depositar(monto);
                cout << "Deposito exitoso.\n";
            }

            else if (opcion == 3) {
                int numero;
                double monto;

                cout << "Numero de cuenta: ";
                cin >> numero;
                cout << "Monto a retirar: ";
                cin >> monto;

                banco.buscarCuenta(numero).retirar(monto);
                cout << "Retiro exitoso.\n";
            }

            else if (opcion == 4) {
                int numero;
                cout << "Numero de cuenta: ";
                cin >> numero;

                double saldo = banco.buscarCuenta(numero).consultarSaldo();
                cout << "Saldo actual: " << saldo << endl;
            }

            else if (opcion == 5) {
                banco.mostrarCuentas();
            }

        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const CuentaNoEncontrada& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (opcion != 6);

    cout << "Programa finalizado correctamente.\n";
    return 0;
}