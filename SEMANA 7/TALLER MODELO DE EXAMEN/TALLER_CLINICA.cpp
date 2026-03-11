#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <regex>

using namespace std;

class EntidadNoEncontrada : public runtime_error {
public:
    EntidadNoEncontrada(const string& msg) : runtime_error(msg) {}
};

class Persona {
protected:
    string nombre;
public:
    Persona(string n) : nombre(n) {}
    virtual ~Persona() {}
    string getNombre() const { return nombre; }
    virtual void mostrar() const = 0;
};

class EntradaHistoria {
private:
    string fecha, nota;
public:
    EntradaHistoria(string f, string n) : fecha(f), nota(n) {}
    void imprimir() const { cout << "[" << fecha << "] " << nota << endl; }
};

class HistoriaClinica {
private:
    vector<unique_ptr<EntradaHistoria>> entradas;
public:
    void agregarEntrada(string f, string n) {
        entradas.push_back(make_unique<EntradaHistoria>(f, n));
    }
};

class Paciente : public Persona {
private:
    string dni, telefono;
    int edad;
    HistoriaClinica historia;
public:
    Paciente(string n, string d, int e, string t) : Persona(n), dni(d), edad(e), telefono(t) {}
    string getDni() const { return dni; }
    void mostrar() const override {
        cout << "PACIENTE: " << nombre << " | DNI: " << dni << " | Edad: " << edad << " | Telf: " << telefono << endl;
    }
    void agregarNotaHistoria(string f, string n) { historia.agregarEntrada(f, n); }
};

class Doctor : public Persona {
private:
    string codigo, especialidad;
    double tarifa;
public:
    Doctor(string n, string c, string e, double t) : Persona(n), codigo(c), especialidad(e), tarifa(t) {}
    string getCodigo() const { return codigo; }
    string getEspecialidad() const { return especialidad; }
    void mostrar() const override {
        cout << "DR: " << nombre << " | Cod: " << codigo << " | Esp: " << especialidad << " | Tarifa: " << tarifa << endl;
    }
};

class Cita {
private:
    int id;
    Paciente* paciente;
    Doctor* doctor;
    string fecha, hora, motivo;
public:
    Cita(int _id, Paciente* p, Doctor* d, string f, string h, string m) 
        : id(_id), paciente(p), doctor(d), fecha(f), hora(h), motivo(m) {}
    int getId() const { return id; }
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }
    Doctor* getDoctor() const { return doctor; }
    Paciente* getPaciente() const { return paciente; }
    void mostrarCita() const {
        cout << "ID Cita: " << id << " | " << fecha << " " << hora << " | Paciente: " << paciente->getNombre() 
             << " | Dr: " << doctor->getNombre() << " | Motivo: " << motivo << endl;
    }
};

class Validador {
public:
    static string leerDNI(string msg) {
        string v;
        while (true) {
            cout << msg; cin >> v;
            if (v.length() == 8 && all_of(v.begin(), v.end(), ::isdigit)) return v;
            cout << ">>> Error: El DNI debe ser de exactamente 8 digitos numericos.\n";
        }
    }
    static int leerEdad(string msg) {
        string v;
        while (true) {
            cout << msg; cin >> v;
            if (all_of(v.begin(), v.end(), ::isdigit)) {
                int e = stoi(v);
                if (e >= 0 && e <= 120) return e;
            }
            cout << ">>> Error: Edad invalida (0-120) y solo numeros.\n";
        }
    }
    static string leerTelf(string msg) {
        string v;
        while (true) {
            cout << msg; cin >> v;
            if (v.length() == 9 && all_of(v.begin(), v.end(), ::isdigit)) return v;
            cout << ">>> Error: El telefono debe tener 9 digitos numericos.\n";
        }
    }
    static double leerTarifa(string msg) {
        double v;
        while (true) {
            cout << msg;
            if (cin >> v && v > 0) return v;
            cout << ">>> Error: Tarifa debe ser mayor a 0.\n";
            cin.clear(); cin.ignore(1000, '\n');
        }
    }
    static string leerRegex(string msg, string exp, string error) {
        string v; regex r(exp);
        while (true) {
            cout << msg; cin >> v;
            if (regex_match(v, r)) return v;
            cout << ">>> Error: " << error << endl;
        }
    }
};

class Clinica {
private:
    vector<unique_ptr<Paciente>> pacientes;
    vector<unique_ptr<Doctor>> doctores;
    vector<unique_ptr<Cita>> citas;
    int contadorCitas = 1;
public:
    void registrarPaciente(string n, string d, int e, string t) {
        pacientes.push_back(make_unique<Paciente>(n, d, e, t));
    }
    void registrarDoctor(string n, string c, string e, double t) {
        doctores.push_back(make_unique<Doctor>(n, c, e, t));
    }
    Paciente* buscarPaciente(string dni) {
        for (auto& p : pacientes) if (p->getDni() == dni) return p.get();
        throw EntidadNoEncontrada("Paciente no registrado en el sistema.");
    }
    Doctor* buscarDoctor(string cod) {
        for (auto& d : doctores) if (d->getCodigo() == cod) return d.get();
        throw EntidadNoEncontrada("Doctor no registrado en el sistema.");
    }
    void agendarCita(Paciente* p, Doctor* d, string f, string h, string m) {
        for (auto& c : citas) {
            if (c->getDoctor()->getCodigo() == d->getCodigo() && c->getFecha() == f && c->getHora() == h)
                throw runtime_error("Cita Duplicada: El doctor ya tiene compromiso en esa fecha/hora.");
        }
        citas.push_back(make_unique<Cita>(contadorCitas++, p, d, f, h, m));
        p->agregarNotaHistoria(f, "Cita agendada con " + d->getNombre());
    }
    void cancelarCita(int id) {
        auto it = remove_if(citas.begin(), citas.end(), [id](const unique_ptr<Cita>& c) { return c->getId() == id; });
        if (it == citas.end()) throw runtime_error("No se encontro ninguna cita con el ID proporcionado.");
        citas.erase(it, citas.end());
    }
    const vector<unique_ptr<Cita>>& getCitas() const { return citas; }
    const vector<unique_ptr<Doctor>>& getDoctores() const { return doctores; }
};

int main() {
    Clinica saludMas;
    int op;
    do {
        cout << "\n--- CLINICA SALUD+ ---\n1.Registrar Paciente  \n2.Registrar Doctor  \n3.Agendar Cita\n4.Cancelar Cita   \n5.Listar citas por paciente  \n6.Listar citas por doctor\n7.Reporte por especialidad   \n8.Salir\nSeleccion: ";
        if (!(cin >> op)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        try {
            switch (op) {
                case 1: {
                    string n, d, t; int e;
                    cout << "Nombre: "; cin.ignore(); getline(cin, n);
                    d = Validador::leerDNI("DNI (8 digitos): ");
                    e = Validador::leerEdad("Edad (0-120): ");
                    t = Validador::leerTelf("Telefono (9 digitos): ");
                    saludMas.registrarPaciente(n, d, e, t);
                    cout << ">>> Paciente registrado correctamente.\n";
                    break;
                }
                case 2: {
                    string n, c, e; double t;
                    cout << "Nombre Doctor: "; cin.ignore(); getline(cin, n);
                    cout << "Codigo Doctor: "; cin >> c;
                    cout << "Especialidad: "; cin.ignore(); getline(cin, e);
                    t = Validador::leerTarifa("Tarifa: ");
                    saludMas.registrarDoctor(n, c, e, t);
                    cout << ">>> Doctor registrado correctamente.\n";
                    break;
                }
                case 3: {
                    string dni = Validador::leerDNI("DNI del Paciente: ");
                    Paciente* p = saludMas.buscarPaciente(dni);
                    cout << "Codigo del Doctor: "; string cod; cin >> cod;
                    Doctor* d = saludMas.buscarDoctor(cod);
                    string f = Validador::leerRegex("Fecha (YYYY-MM-DD): ", R"(\d{4}-\d{2}-\d{2})", "Formato invalido.");
                    string h = Validador::leerRegex("Hora (HH:MM): ", R"([0-2][0-9]:[0-5][0-9])", "Formato invalido.");
                    cout << "Motivo: "; cin.ignore(); string m; getline(cin, m);
                    saludMas.agendarCita(p, d, f, h, m);
                    cout << ">>> Cita agendada exitosamente.\n";
                    break;
                }
                case 4: {
                    cout << "ID de la cita a cancelar: "; int id; cin >> id;
                    saludMas.cancelarCita(id);
                    cout << ">>> Cita cancelada.\n";
                    break;
                }
                case 5: {
                    string dni = Validador::leerDNI("DNI del Paciente: ");
                    for (auto& c : saludMas.getCitas()) if (c->getPaciente()->getDni() == dni) c->mostrarCita();
                    break;
                }
                case 6: {
                    cout << "Codigo del Doctor: "; string cod; cin >> cod;
                    for (auto& c : saludMas.getCitas()) if (c->getDoctor()->getCodigo() == cod) c->mostrarCita();
                    break;
                }
                case 7: {
                    cout << "\n--- REPORTE POR ESPECIALIDAD ---\n";
                    for (auto& d : saludMas.getDoctores()) {
                        int total = 0;
                        for (auto& c : saludMas.getCitas()) if (c->getDoctor()->getEspecialidad() == d->getEspecialidad()) total++;
                        cout << d->getEspecialidad() << ": " << total << " citas.\n";
                    }
                    break;
                }
            }
        } catch (const exception& ex) { cout << ">>> ERROR: " << ex.what() << endl; }
    } while (op != 8);
    return 0;
}