#include <iostream>
using namespace std;

int main() {

    int opcion, cerrado = 0, units, code, ventas = 0, devoluciones = 0, invalidas = 0, primera = 1;
    float unitPrice, ingreso, ingreso_neto = 0, mayor = 0, menor = 0, suma_ventas = 0;


    do {
        cout << "\n1) Registrar transaccion\n2) Reporte de ventas del dia\n3) Reporte por transaccion (A / B / C / D)\n4) Cerrar dia\n5) Salir\n";
        cout <<"Eliga una opcion: ";cin >> opcion;

        if (opcion == 1) {

            if (cerrado == 1) {
                cout << "DIA CERRADO\n";
            } else {
                cout << "Ingrese units: \n"; cin >> units;
                cout << "Ingrese unitPrice: \n"; cin >> unitPrice;
                cout << "Ingrese code: \n"; cin >> code;

                if (units == 0 || unitPrice == 0) {
                    invalidas++;
                } else {
                    ingreso = units * unitPrice;
                    ingreso_neto += ingreso;

                    if (primera == 1) {
                        mayor = ingreso;
                        menor = ingreso;
                        primera = 0;
                    } else {
                        if (ingreso > mayor) mayor = ingreso;
                        if (ingreso < menor) menor = ingreso;
                    }

                    if (units > 0) {
                        ventas++;
                        suma_ventas += ingreso;
                    } else {
                        devoluciones++;
                    }

                    cout << "Ingreso: " << ingreso << endl;
                }
            }

        } else if (opcion == 2) {

            cout << "\nINGRESO_NETO=" << ingreso_neto << endl;
            cout << "VENTAS_VALIDAS=" << ventas << endl;
            cout << "DEVOLUCIONES=" << devoluciones << endl;
            cout << "TRANS_INVALIDAS=" << invalidas << endl;
            cout << "MAYOR_ING=" << mayor << endl;
            cout << "MENOR_ING=" << menor << endl;

            if (ventas > 0)
                cout << "PROM_VENTA=" << (suma_ventas / ventas) << endl;
            else
                cout << "PROM_VENTA=NO EXISTE\n";

        } else if (opcion == 3) {
            cout << "No se puede usar esta funcion.\n";

        } else if (opcion == 4) {
            cerrado = 1;
            cout << "DIA CERRADO\n";

        }

    } while (opcion != 5);

    cout<<"\nSaliendo...";

    return 0;
}