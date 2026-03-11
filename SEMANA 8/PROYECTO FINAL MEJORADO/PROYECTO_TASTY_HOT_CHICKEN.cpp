#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <vector>   
#include <fstream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

enum EstadoPedido {

    RECEPCIONADO,
    PENDIENTE_PREPARACION,
    EN_PREPARACION,
    LISTO,
    ENTREGADO

};

string validarSoloTexto(string mensaje) {
    string texto;
    while (true) {
        try {
            cout << mensaje;
            getline(cin, texto);

            if (texto.empty()) throw runtime_error("El campo no puede estar vacio.");

            for (char c : texto) {
                if (!isalpha(c) && !isspace(c)) {
                    throw runtime_error("El nombre debe contener solo letras.");
                }
            }
            return texto;
        }
        catch (const exception& e) {
            cout << ">>> Error: " << e.what() << endl;
        }
    }
}

string estadoToString(EstadoPedido estado) {

    switch(estado) {

        case RECEPCIONADO: return "Recepcionado";
        case PENDIENTE_PREPARACION: return "Pendiente Preparacion";
        case EN_PREPARACION: return "En Preparacion";
        case LISTO: return "Listo";
        case ENTREGADO: return "Entregado";

        default: return "Desconocido";
    }
}

class Producto {
private:
    string nombre;
    double precio;
    int cantidad;
    double subtotal;

public:

    void setNombre(string n) { nombre = n; }
    string getNombre() const { return nombre; }
    
    void setPrecio(double p) { precio = p; }
    double getPrecio() const { return precio; }
    
    void setCantidad(int c) { cantidad = c; }
    int getCantidad() const { return cantidad; }
    
    void setSubtotal(double s) { subtotal = s; }
    double getSubtotal() const { return subtotal; }
};


class Cliente {
private:
    string nombre;
    string tipoDocumento;
    string ruc;

public:
    void setNombre(string n) { nombre = n; }
    string getNombre() const { return nombre; }
    
    void setTipoDocumento(string t) { tipoDocumento = t; }
    string getTipoDocumento() const { return tipoDocumento; }
    
    void setRuc(string r) { ruc = r; }
    string getRuc() const { return ruc; }
};

class Pedido {
private:
    Producto productos[100];
    int cantidadProductos;
    double total;
    EstadoPedido estado;

public:
    void setCantidadProductos(int c) { cantidadProductos = c; }
    int getCantidadProductos() const { return cantidadProductos; }
    
    void setTotal(double t) { total = t; }
    double getTotal() const { return total; }
    
    void setEstado(EstadoPedido e) { estado = e; }
    EstadoPedido getEstado() const { return estado; }
    
    Producto& getProducto(int index) { return productos[index]; }
};

class Trabajador {
private:
    int id;
    string nombre;
    string rol; 

public:
    void setId(int _id) { id = _id; }
    int getId() const { return id; }
    
    void setNombre(string n) { nombre = n; }
    string getNombre() const { return nombre; }
    
    void setRol(string r) { rol = r; }
    string getRol() const { return rol; }
};

class IImprimible {

public:

    virtual void imprimir() = 0;

    virtual ~IImprimible() {}

};

class Orden : public IImprimible {

private:

    vector<Producto> items; 
    EstadoPedido estado;

    Cliente* cliente; 
    Trabajador* atendidoPor;

public:

    Orden(Cliente* c, Trabajador* t) : cliente(c), atendidoPor(t), estado(RECEPCIONADO) {}

    void agregarProducto(const Producto& p) { 
        items.push_back(p); 
    }

    double calcularTotal() const {

        double total = 0;

        for(const auto& p : items)
            total += p.getPrecio() * p.getCantidad();

        return total;
    }

    void imprimir() override {
        cout << "Orden del cliente: " << cliente->getNombre() << endl;
        cout << "Atendido por: " << atendidoPor->getNombre() << endl;
        cout << "Estado: " << estadoToString(estado) << endl;
    }
};

ostream& operator<<(ostream& os, const Orden& o) {
    os << "===== TICKET PEDIDO =====\n";
    os << "Pedido registrado en el sistema.\n";
    os << "=========================\n";
    return os;
}

class GestorPersistencia {
public:
    static void guardarTicket(const Orden& o) {
        ofstream archivo("pedidos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << o; 
            archivo << "\n\n";
            archivo.close();
            cout << ">>> Pedido guardado en archivo.\n";
        }
    }
};

class Ticket : public IImprimible {

private:

    Producto* lista;
    int n;
    double total;

public:

    Ticket(Producto* l, int cantidad, double t) {

        lista = l;
        n = cantidad;
        total = t;
    }

    void imprimir() override {

        cout << "==============================\n";
        cout << "        TICKET DE VENTA\n";
        cout << "==============================\n";

        for (int i = 0; i < n; i++) {

            cout << lista[i].getNombre()
                 << " x" << lista[i].getCantidad()
                 << " = S/ " << lista[i].getSubtotal()
                 << endl;
        }

        cout << "------------------------------\n";
        cout << "TOTAL: S/ " << total << endl;
    }
};

class InputException : public runtime_error {
public:
    InputException(const string& msg) : runtime_error(msg) {}
};

class Validador {
public:
    static int leer(string msg, int min, int max) {
        int v;
        while (true) {
            try {
                cout << msg;
                if (!(cin >> v)) throw InputException("Formato no numerico.");
                if (v < min || v > max) throw out_of_range("Fuera de rango.");
                return v;
            } catch (const exception& e) {
                cout << ">>> Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    static string leer(string msg) { 
        string v;
        cout << msg;
        cin.ignore();
        getline(cin, v);
        return v;
    }
};

int leerEnteroSeguro(string mensaje, int min, int max) {

    int valor;

    while (true) {

        try {

            cout << mensaje;

            if (!(cin >> valor)) {
                throw runtime_error("Debe ingresar solo numeros.");
            }

            if (valor < min || valor > max) {
                throw out_of_range("Opcion fuera del rango permitido.");
            }

            return valor;
        }

        catch (exception &e) {

            cout << ">>> Error: " << e.what() << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string leerRespuestaSiNo(string mensaje) {
    string respuesta;
    while (true) {
        cout << mensaje;
        cin >> respuesta;
        transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);
        if (respuesta == "si" || respuesta == "no") return respuesta;
        cout << ">>> Error: Escriba exactamente 'si' o 'no'.\n";
    }
}

void guardarClienteTXT(Cliente c) {
    ofstream archivo("clientes.txt", ios::app);
    archivo << c.getNombre() << " | "
            << c.getTipoDocumento() << " | "
            << c.getRuc() << endl;
    archivo.close();
}

void guardarTrabajadorTXT(Trabajador t) {
    ofstream archivo("trabajadores.txt", ios::app);
    archivo << t.getId() << " | "
            << t.getNombre() << " | "
            << t.getRol() << endl;
    archivo.close();
}

bool buscarTrabajadorPorID(int idBuscado, Trabajador &trabajadorEncontrado) {

    ifstream archivo("trabajadores.txt");
    if (!archivo.is_open()) return false;

    string linea;

    while (getline(archivo, linea)) {

        size_t pos1 = linea.find("|");
        size_t pos2 = linea.rfind("|");

        if (pos1 == string::npos || pos2 == string::npos) continue;

        string idStr = linea.substr(0, pos1);
        string nombre = linea.substr(pos1 + 2, pos2 - pos1 - 3);
        string rol = linea.substr(pos2 + 2);

        int id = stoi(idStr);

        if (id == idBuscado) {
            trabajadorEncontrado.setId(id);
            trabajadorEncontrado.setNombre(nombre);
            trabajadorEncontrado.setRol(rol);
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void guardarPedidoTXT(Cliente c, Trabajador t, Producto* lista, int n, double total) {
    ofstream archivo("pedidos.txt", ios::app);
    archivo << "========================================\n";
    archivo << "Cliente: " << c.getNombre() << endl;
    archivo << "Documento: " << c.getTipoDocumento() << endl;
    archivo << "Atendido por: " << t.getNombre() << " (" << t.getRol() << ")\n";
    archivo << "----------------------------------------\n";
    for (int i = 0; i < n; i++) {
        archivo << lista[i].getNombre() << " | "
                << lista[i].getCantidad() << " | "
                << lista[i].getSubtotal() << endl;
    }
    archivo << "TOTAL: S/ " << total << endl;
    archivo << "========================================\n\n";
    archivo.close();
}

Trabajador loginTrabajador() {
    Trabajador t;

    cout << "\n===== LOGIN TRABAJADOR =====\n";
    
    int idTemp;
    while (true) {
        try {
            idTemp = leerEnteroSeguro("Ingrese su ID (exactamente 4 digitos): ", 1000, 9999);
            
            if (to_string(idTemp).length() != 4) {
                throw runtime_error("El ID debe tener exactamente 4 digitos.");
            }
            break; 
        } catch (const exception& e) {
            cout << ">>> Error: " << e.what() << endl;
        }
    }
    
    cin.ignore();

    if (buscarTrabajadorPorID(idTemp, t)) {
        cout << "\nBienvenido nuevamente " << t.getNombre() << endl;
        cout << "Rol: " << t.getRol() << endl;
    } else {
        cout << "\nID no encontrado. Registrando nuevo trabajador...\n";
        t.setId(idTemp);

        string nomTemp = validarSoloTexto("Nombre: ");
        t.setNombre(nomTemp);

        int rolOp = leerEnteroSeguro("1. Cajero\n2. Mesero\nSeleccione: ", 1, 2);        
        t.setRol((rolOp == 1) ? "Cajero" : "Mesero");

        guardarTrabajadorTXT(t);
        cout << "\nRegistro exitoso.\n";
    }
    return t;
}

Cliente registrarCliente() {
    Cliente c;
    cout << "\n===== DATOS inicial del cliente =====\n";
    int tipo = leerEnteroSeguro("1. Boleta\n2. Factura\nSeleccione: ", 1, 2);

    cin.ignore();
    
    string nomTemp = validarSoloTexto("Nombre del cliente: ");
    c.setNombre(nomTemp);

    if (tipo == 2) {
        c.setTipoDocumento("Factura");
        bool valido = false;
        while (!valido) {
            cout << "Ingrese RUC (11 digitos): ";
            string rucTemp;
            cin >> rucTemp;
            valido = (rucTemp.length() == 11 &&
                      all_of(rucTemp.begin(), rucTemp.end(), ::isdigit));
            if (!valido) cout << ">>> RUC invalido.\n";
            else c.setRuc(rucTemp);
        }
    } else {
        c.setTipoDocumento("Boleta");
        c.setRuc("-");
    }

    guardarClienteTXT(c);
    return c;
}

void mostrarQR(int metodo) {
    system("cls"); 

    cout << "\n";
    cout << "=========================================\n";
    cout << "              PAGO DIGITAL               \n";
    cout << "=========================================\n";

    if (metodo == 3)
        cout << "          PAGO CON YAPE\n";
    else
        cout << "          PAGO CON PLIN\n";

    cout << "  .---------------------------." << endl;
    cout << "  |       PAGO CON " << (metodo == 3 ? "YAPE" : "PLIN") << "       |" << endl;
    cout << "  |---------------------------|" << endl;
    cout << "  |  CEL: 962559265           |" << endl;
    cout << "  |  TITULAR: TASTY CHICKEN   |" << endl;
    cout << "  |                           |" << endl;
    cout << "  |    [# # # # # # # #]      |" << endl;
    cout << "  |    [#  #  # #    # ]      |" << endl;
    cout << "  |    [# #        #  #]      |" << endl;
    cout << "  |    [#      # #    #]      |" << endl;
    cout << "  |    [# # # # # # # #]      |" << endl;
    cout << "  |      CODIGO QR SCAN       |" << endl;
    cout << "  '---------------------------'" << endl;
    cout << "  Presione Enter tras realizar el pago...";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void imprimirTicket(Producto* lista, int n, double total, Cliente c, Trabajador t, EstadoPedido estadoActual) {

    system("cls || clear");

    cout << "========================================\n";
    cout << "          TASTY HOT CHICKEN\n";
    cout << "========================================\n";
    cout << "Cliente: " << c.getNombre() << endl;
    cout << "Documento: " << c.getTipoDocumento() << endl;
    cout << "Atendido por: " << t.getNombre() << " (" << t.getRol() << ")\n";
    cout << "----------------------------------------\n";
    cout << "Cant | Producto                | Total\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < n; i++) {

        cout << setw(4) << lista[i].getCantidad() << " | "
             << left << setw(22) << lista[i].getNombre()
             << " | S/ " << fixed << setprecision(2)
             << lista[i].getSubtotal() << endl;
    }

    cout << "----------------------------------------\n";
    cout << "TOTAL: S/ " << total << endl;
    cout << "========================================\n";

    cout << "Estado del pedido: "
         << estadoToString(estadoActual)
         << endl;

    cout << "========================================\n";
}

int main() {

    Trabajador trabajador = loginTrabajador();
    Cliente cliente = registrarCliente();

    Producto* pedido = new Producto[100];
    int contador = 0;
    double totalGeneral = 0;
    string continuar = "si";
    EstadoPedido estadoActual = RECEPCIONADO;

    cout << "\n===== BIENVENIDO A TASTY HOT CHICKEN =====\n";

    while (continuar == "si") {

        int cat, opc, cant;
        string nombreActual;
        double precioActual = 0;

        do {
           cat = leerEnteroSeguro("\n1. Platos\n2. Bebidas\nSeleccione categoria: ",1,2);
        } while (cat < 1 || cat > 2);

        if (cat == 1) {

            do {
                cout << "\n--- PLATOS ---\n"
                     << "1. Brosther Pecho (S/12)\n"
                     << "2. B. Entre-Pierna (S/11)\n"
                     << "3. B. Pierna (S/10)\n"
                     << "4. B. Ala (S/9)\n"
                     << "5. Salchibrosther (S/16)\n"
                     << "6. H. Clasica (S/8)\n"
                     << "7. H. Mixta (S/10)\n"
                     << "8. H. Royal (S/12)\n"
                     << "9. H. Tasty (S/22)\n"
                     << "10. Alitas BBQ (S/20)\n"
                     << "11. A. Acevichadas (S/20)\n"
                     << "12. A. Crispy (S/20)\n"
                     << "13. A. Maracuya (S/20)\n"
                     << "14. A. Picantes (S/20)\n"
                     << "15. Salchipapa Cl. (S/8)\n"
                     << "16. Salchipapa Esp. (S/11)\n"
                     << "17. S. Amazonica (S/25)\n"
                     << "18. Choripapa Cl. (S/10)\n"
                     << "19. Choripapa Esp. (S/13)\n";
                opc = leerEnteroSeguro("Seleccione: ",1,19);
            } while (opc < 1 || opc > 19);

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

            do {
                cout << "\n--- BEBIDAS ---\n"
                     << "1. Cocona (S/2)\n"
                     << "2. Chicha (S/2)\n"
                     << "3. Gaseosa Pers. (S/4)\n"
                     << "4. Agua Pers. (S/2)\n"
                     << "5. Cafe (S/3)\n"
                     << "6. Jugo Fresa (S/4)\n"
                     << "7. Jugo Platano (S/4)\n"
                     << "8. Jugo Esp. (S/6)\n"
                     << "9. Jugo Piña (S/4)\n"
                     << "10. Jugo Malta (S/7)\n";
                opc = leerEnteroSeguro("Seleccione: ",1,10);
            } while (opc < 1 || opc > 10);

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

        cant = leerEnteroSeguro("Cantidad: ",1,50);

        pedido[contador].setNombre(nombreActual);
        pedido[contador].setPrecio(precioActual);
        pedido[contador].setCantidad(cant);
        pedido[contador].setSubtotal(precioActual * cant);

        totalGeneral += pedido[contador].getSubtotal();
        contador++;

        continuar = leerRespuestaSiNo("¿Desea pedir algo mas? (si/no): ");
    }

    int pago = leerEnteroSeguro("\nMetodo de pago:\n1. Efectivo\n2. Tarjeta\n3. Yape\n4. Plin\nSeleccione: ",1,4);
    if (pago >= 3) mostrarQR(pago);

    imprimirTicket(pedido, contador, totalGeneral, cliente, trabajador, estadoActual);

    guardarPedidoTXT(cliente, trabajador, pedido, contador, totalGeneral);

    delete[] pedido;
    return 0;
}