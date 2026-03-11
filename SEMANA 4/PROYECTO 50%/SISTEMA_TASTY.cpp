#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Estructura para organizar los datos de cada item
struct Producto {
    string nombre;
    int cantidad;
    double subtotal;
};

// --- PILAR: FUNCIONES Y PASO POR REFERENCIA ---
// Usamos 'const string&' para no copiar el texto y ahorrar memoria
void mostrarQR(int metodo) {
    system("clear || cls");
    cout << "  .---------------------------." << endl;
    cout << "  |       PAGO CON " << (metodo == 3 ? "YAPE" : "PLIN") << "       |" << endl;
    cout << "  |---------------------------|" << endl;
    cout << "  |  CEL: 962559265           |" << endl;
    cout << "  |  TITULAR: TASTY CHICKEN   |" << endl;
    cout << "  |                           |" << endl;
    cout << "  |    [# # # # # # # #]      |" << endl;
    cout << "  |    [#    # #    #  ]      |" << endl;
    cout << "  |    [#  #     #  #  ]      |" << endl;
    cout << "  |    [#    # #    #  ]      |" << endl;
    cout << "  |    [# # # # # # # #]      |" << endl;
    cout << "  |      CODIGO QR SCAN       |" << endl;
    cout << "  '---------------------------'" << endl;
    cout << "  Presione Enter tras realizar el pago...";
    cin.ignore();
    cin.get();
}

// --- PILAR: FUNCIONES Y PASO POR PUNTERO ---
// Recibe el puntero al arreglo dinámico para imprimir el ticket final
void imprimirTicket(Producto* lista, int n, double total, string cliente, string ruc = "") {
    system("clear || cls");
    cout << "========================================" << endl;
    if (ruc == "") cout << "             BOLETA DE VENTA" << endl;
    else cout << "            FACTURA ELECTRÓNICA\nRUC: " << ruc << endl;
    cout << "========================================" << endl;
    cout << "Cliente: " << cliente << endl;
    cout << "----------------------------------------" << endl;
    cout << "Cant. | Descripcion          | Total" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < n; i++) {
        cout << "[" << lista[i].cantidad << "] | " 
             << left << setw(20) << lista[i].nombre 
             << " | S/ " << fixed << setprecision(2) << lista[i].subtotal << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "TOTAL A PAGAR: S/ " << total << endl;
    cout << "========================================" << endl;
    cout << "¡Gracias por su compra en Tasty Hot Chicken!" << endl;
}

int main() {
    // --- PILAR: MEMORIA DINÁMICA ---
    // Reservamos espacio en el HEAP para hasta 50 pedidos
    Producto* pedido = new Producto[50]; 
    
    int contador = 0;
    string continuar = "S";
    double totalGeneral = 0;

    cout << "======================================" << endl;
    cout << "    Bienvenidos a Tasty Hot Chicken" << endl;
    cout << "======================================" << endl;

    while (continuar == "S" || continuar == "s") {
        int cat, opc, cant;
        string nombreActual;
        double precioActual = 0;

        cout << "\n1. Platos\n2. Bebidas\nSeleccione categoria: "; cin >> cat;
        system("clear || cls");

        if (cat == 1) {
            cout << "--- PLATOS ---\n1. Brosther Pecho (S/12)   2. B. Entre-Pierna (S/11)  3. B. Pierna (S/10)\n4. B. Ala (S/9)          5. Salchibrosther (S/16)   6. H. Clasica (S/8)\n7. H. Mixta (S/10)       8. H. Royal (S/12)         9. H. Tasty (S/22)\n10. Alitas BBQ (S/20)     11. A. Acevichadas (S/20)  12. A. Crispy (S/20)\n13. A. Maracuya (S/20)    14. A. Picantes (S/20)     15. Salchipapa Cl. (S/8)\n16. Salchipapa Esp. (S/11) 17. S. Amazonica (S/25)   18. Choripapa Cl. (S/10)\n19. Choripapa Esp. (S/13)\nSeleccione: ";
            cin >> opc;
            switch(opc) {
                case 1: nombreActual="Brosther Pecho"; precioActual=12; break;
                case 2: nombreActual="Brosther E-Pierna"; precioActual=11; break;
                case 3: nombreActual="Brosther Pierna"; precioActual=10; break;
                case 4: nombreActual="Brosther Ala"; precioActual=9; break;
                case 5: nombreActual="Salchibrosther"; precioActual=16; break;
                case 6: nombreActual="H. Clasica"; precioActual=8; break;
                case 7: nombreActual="H. Mixta"; precioActual=10; break;
                case 8: nombreActual="H. Royal"; precioActual=12; break;
                case 9: nombreActual="H. Tasty"; precioActual=22; break;
                case 10: nombreActual="Alitas BBQ"; precioActual=20; break;
                case 11: nombreActual="Alitas Acevichadas"; precioActual=20; break;
                case 12: nombreActual="Alitas Crispy"; precioActual=20; break;
                case 13: nombreActual="Alitas Maracuya"; precioActual=20; break;
                case 14: nombreActual="Alitas Picantes"; precioActual=20; break;
                case 15: nombreActual="Salchipapa Cl."; precioActual=8; break;
                case 16: nombreActual="Salchipapa Esp."; precioActual=11; break;
                case 17: nombreActual="Salchipapa Amaz."; precioActual=25; break;
                case 18: nombreActual="Choripapa Cl."; precioActual=10; break;
                case 19: nombreActual="Choripapa Esp."; precioActual=13; break;
            }
        } else {
            cout << "--- BEBIDAS ---\n1. Cocona (S/2)      2. Chicha (S/2)     3. Gaseosa Pers. (S/4)\n4. Agua Pers. (S/2)  5. Cafe (S/3)       6. Jugo Fresa (S/4)\n7. Jugo Platano (S/4) 8. Jugo Esp. (S/6)  9. Jugo Piña (S/4)\n10. Jugo Malta (S/7)\nSeleccione: ";
            cin >> opc;
            switch(opc) {
                case 1: nombreActual="Bebida Cocona"; precioActual=2; break;
                case 2: nombreActual="Chicha Morada"; precioActual=2; break;
                case 3: nombreActual="Gaseosa Pers."; precioActual=4; break;
                case 4: nombreActual="Agua Personal"; precioActual=2; break;
                case 5: nombreActual="Cafe"; precioActual=3; break;
                case 6: nombreActual="Jugo Fresa"; precioActual=4; break;
                case 7: nombreActual="Jugo Platano"; precioActual=4; break;
                case 8: nombreActual="Jugo Especial"; precioActual=6; break;
                case 9: nombreActual="Jugo Piña"; precioActual=4; break;
                case 10: nombreActual="Jugo Malta"; precioActual=7; break;
            }
        }

        cout << "Cantidad: "; cin >> cant;
        
        // Asignación en memoria dinámica
        pedido[contador].nombre = nombreActual;
        pedido[contador].cantidad = cant;
        pedido[contador].subtotal = cant * precioActual;
        totalGeneral += pedido[contador].subtotal;
        contador++;

        cout << "¿Agregar otro? (S/N): "; cin >> continuar;
    }

    // Facturación
    int tipoC, pago;
    string cliente, ruc = "";
    cout << "\n1. Boleta\n2. Factura\nSeleccione: "; cin >> tipoC;
    if (tipoC == 2) {
        cout << "RUC (11 digitos): "; cin >> ruc;
        cliente = "Empresa ABC SAC";
    } else {
        cout << "Nombre cliente: "; cin.ignore(); getline(cin, cliente);
    }

    cout << "\nMetodo: 1.Efectivo 2.Tarjeta 3.Yape 4.Plin: "; cin >> pago;
    if (pago >= 3) mostrarQR(pago);

    // --- USO DEL PUNTERO EN FUNCIÓN ---
    imprimirTicket(pedido, contador, totalGeneral, cliente, ruc);

    // --- LIBERACIÓN DE MEMORIA DINÁMICA ---
    delete[] pedido; 
    pedido = nullptr; 

    return 0;
}