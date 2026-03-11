#include <iostream>
#include <string>

using namespace std;

struct Producto {
    int codigo;
    string nombre;
    float precio;
    int stock;
};

int main() {

    Producto inventario[100]; 
    int cont = 0;
    int op;

    do {
        cout << "\n========== MENU DE INVENTARIO TASTY ==========" << endl;
        cout << "1. Registrar productos" << endl;
        cout << "2. Mostrar productos" << endl;
        cout << "3. Buscar producto por codigo" << endl;
        cout << "4. Buscar producto por nombre" << endl;
        cout << "5. Mostrar producto con mayor stock" << endl;
        cout << "6. Mostrar producto mas caro" << endl;
        cout << "7. Calcular valor total del inventario" << endl;
        cout << "8. Ordenar productos por precio (Mayor a Menor)" << endl;
        cout << "9. Ordenar productos por nombre (A-Z)" << endl;
        cout << "10. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch (op) {
            
            case 1: { 
                int n;
                do {
                    cout << "Cuantos productos desea registrar (min. 5): ";
                    cin >> n;
                    if(n < 5) cout << "Error: Debe ingresar al menos 5 productos." << endl;
                } while (n < 5);

                for (int i = 0; i < n; i++) {
                    cout << "\n--- Producto " << cont + 1 << " ---" << endl;
                    cout << "Codigo: "; cin >> inventario[cont].codigo;
                    cout << "Nombre: "; cin.ignore(); getline(cin, inventario[cont].nombre);
                    
                    do {
                        cout << "Precio: "; cin >> inventario[cont].precio;
                    } while (inventario[cont].precio <= 0);

                    do {
                        cout << "Stock: "; cin >> inventario[cont].stock;
                    } while (inventario[cont].stock < 1);
                    cont++;
                }
                break;
            }

            case 2: { 
                if (cont == 0) cout << "Inventario vacio." << endl;
                else {
                    cout << "\nID\tCOD\tNOMBRE\t\tPRECIO\tSTOCK" << endl;
                    cout << "----------------------------------------------------" << endl;
                    for (int i = 0; i < cont; i++) {
                        cout << i+1 << "\t" << inventario[i].codigo << "\t" 
                             << inventario[i].nombre << "\t\t" << inventario[i].precio 
                             << "\t" << inventario[i].stock << endl;
                    }
                }
                break;
            }

            case 3: { 
                int busq;
                bool hallado = false;
                cout << "Ingrese codigo a buscar: "; cin >> busq;
                for (int i = 0; i < cont; i++) {
                    if (inventario[i].codigo == busq) {
                        cout << "ENCONTRADO: " << inventario[i].nombre << " | Precio: " << inventario[i].precio << endl;
                        hallado = true; break;
                    }
                }
                if (!hallado) cout << "No encontrado." << endl;
                break;
            }

            case 4: { 
                string bNombre;
                bool hallado = false;
                cout << "Nombre del producto a buscar: "; cin.ignore(); getline(cin, bNombre);
                for (int i = 0; i < cont; i++) {
                    if (inventario[i].nombre == bNombre) {
                        cout << "ENCONTRADO: Codigo " << inventario[i].codigo << " | Stock: " << inventario[i].stock << endl;
                        hallado = true;
                    }
                }
                if (!hallado) cout << "No encontrado." << endl;
                break;
            }

            case 5: { 
                if (cont > 0) {
                    int pos = 0;
                    for (int i = 1; i < cont; i++) {
                        if (inventario[i].stock > inventario[pos].stock) pos = i;
                    }
                    cout << "Producto con MAS unidades: " << inventario[pos].nombre << " (" << inventario[pos].stock << " uds)" << endl;
                } else cout << "No hay productos." << endl;
                break;
            }

            case 6: { 
                if (cont > 0) {
                    int pos = 0;
                    for (int i = 1; i < cont; i++) {
                        if (inventario[i].precio > inventario[pos].precio) pos = i;
                    }
                    cout << "Producto MAS caro: " << inventario[pos].nombre << " ($" << inventario[pos].precio << ")" << endl;
                } else cout << "No hay productos." << endl;
                break;
            }

            case 7: { 
                float sumaTotal = 0;
                for (int i = 0; i < cont; i++) {
                    sumaTotal += (inventario[i].precio * inventario[i].stock);
                }
                cout << "VALOR TOTAL DEL INVENTARIO: $" << sumaTotal << endl;
                break;
            }

            case 8: { 
                for (int i = 0; i < cont - 1; i++) {
                    for (int j = 0; j < cont - 1; j++) {
                        if (inventario[j].precio < inventario[j+1].precio) {
                            swap(inventario[j], inventario[j+1]);
                        }
                    }
                }
                cout << "Inventario ordenado por PRECIO (Mayor a Menor)." << endl;
                break;
            }

            case 9: { 
                for (int i = 0; i < cont - 1; i++) {
                    for (int j = 0; j < cont - 1; j++) {
                        if (inventario[j].nombre > inventario[j+1].nombre) {
                            swap(inventario[j], inventario[j+1]);
                        }
                    }
                }
                cout << "Inventario ordenado por NOMBRE (A-Z)." << endl;
                break;
            }
        }
    } while (op != 10);

    return 0;
}