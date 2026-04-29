#include <iostream>
#include <vector>
#include <string>

using namespace std;


//Clase abstracta
class Vehiculo {
protected:
    int id;
    string marca;
    string modelo;
    int anioFabricacion;
    string color;
    double precio;
    int stock;

public:
//Constructor con validaciones
    Vehiculo(int i, string ma, string mo, int anio, string col, double p, int s) {
        if (p <= 0) throw "Precio invalido";
        if (s < 0) throw "Stock invalido";
        id = i; marca = ma; modelo = mo; 
        anioFabricacion = anio; color = col; 
        precio = p; stock = s;
    }
    //Destructor virtual
    virtual ~Vehiculo() {}
    // Getters 
    int getId() { return id; }
    string getMarca() { return marca; }
    double getPrecio() { return precio; }
    int getStock() { return stock; }
//Modulo: GESTION DE STOCK
    void actualizarStock(int n) { stock += n; }
//Mostrar detalles con metodo virtual
    virtual void mostrar() = 0;
};
// Motores 
//Clase base
class MotorGasolina {
protected:
    double cilindrada;
    double capacidadTanque;
    string tipoCombustible;
    double consumoKmL;
    int numCilindros;
public:
    MotorGasolina(double c, double cap, string tipo, double cons, int num) {
        if (c <= 0) throw "Cilindrada invalida";
        cilindrada = c; capacidadTanque = cap; 
        tipoCombustible = tipo; consumoKmL = cons; numCilindros = num;
    }
};

class MotorElectrico {
protected:
    double autonomia;
    double capBateriaKwh;
    double tiempoCargaHrs;
    double potenciaHp;
    bool cargaRapida;
public:
    MotorElectrico(double a, double capBat, double tiempoC, double pot, bool rapida) {
        if (a <= 0) throw "Autonomia invalida";
        autonomia = a; capBateriaKwh = capBat; 
        tiempoCargaHrs = tiempoC; potenciaHp = pot; cargaRapida = rapida;
    }
};

//Herencias
// Auto a gasolina (herencia multiple)
class AutoGasolina : public Vehiculo, public MotorGasolina {
public:
    AutoGasolina(int i, string ma, string mo, int anio, string col, double p, int s, double c, double cap, string tipo, double cons, int num)
        : Vehiculo(i,ma,mo,anio,col,p,s), MotorGasolina(c, cap, tipo, cons, num) {}

    void mostrar() override {
        cout << "[Gasolina] " << marca << " " << modelo << " (" << anioFabricacion << ") - Color: " << color << " | $" << precio << " | Stock: " << stock << endl;
    }
};
// Auto eléctrico
class AutoElectrico : public Vehiculo, public MotorElectrico {
public:
    AutoElectrico(int i, string ma, string mo, int anio, string col, double p, int s, double a, double capBat, double tiempoC, double pot, bool rapida)
        : Vehiculo(i,ma,mo,anio,col,p,s), MotorElectrico(a, capBat, tiempoC, pot, rapida) {}
//Polimorfismo 
    void mostrar() override {
        cout << "[Electrico] " << marca << " " << modelo << " (" << anioFabricacion << ") - Color: " << color << " | $" << precio << " | Stock: " << stock << endl;
    }
};

//Auto hibrido (Concepto de herencia multiple)
class AutoHibrido : public Vehiculo, public MotorGasolina, public MotorElectrico {
public:
    AutoHibrido(int i, string ma, string mo, int anio, string col, double p, int s, double c, double cap, string tipo, double cons, int num, double a, double capBat, double tiempoC, double pot, bool rapida)
        : Vehiculo(i,ma,mo,anio,col,p,s), MotorGasolina(c, cap, tipo, cons, num), MotorElectrico(a, capBat, tiempoC, pot, rapida) {}

    void mostrar() override {
        cout << "[Hibrido] " << marca << " " << modelo << " (" << anioFabricacion << ") - Color: " << color << " | $" << precio << " | Stock: " << stock << endl;
    }
};
//Cliente 
class Cliente {
private:
    int id;
    string cedula;
    string nombre;
    string telefono;
    string correo;
    int compras;
    double totalGastado;

public:
    Cliente(int i, string ced, string nom, string tel, string mail) {
        if (nom == "") throw "Nombre invalido";
        id = i; cedula = ced; nombre = nom; 
        telefono = tel; correo = mail; 
        compras = 0; totalGastado = 0;
    }

    int getId() { return id; }
    int getCompras() { return compras; }
    void comprar(double x) { compras++; totalGastado += x; }
};
// Vendedor 
class Vendedor {
private:
    int id;
    string cedula;
    string nombre;
    string telefono;
    string sucursal;
    double totalVendido;
    double comisionGenerada;

public:
    Vendedor(int i, string ced, string nom, string tel, string suc) {
        if (nom == "") throw "Nombre invalido";
        id = i; cedula = ced; nombre = nom; 
        telefono = tel; sucursal = suc; 
        totalVendido = 0; comisionGenerada = 0;
    }

    int getId() { return id; }
    void vender(double x) { 
        totalVendido += x; 
        comisionGenerada += (x * 0.01); 
    }
};
// Venta 
//Modulo:Gestion Transaccional por composicion
class Venta {
private:
    int idVenta;
    string fecha;
    string metodoPago;
    double total;
    double desc;
    double impuestos;
    int cant;

public:
    Venta(int idV, string fec, string metodo, double t, double d, double imp, int c) {
        idVenta = idV; fecha = fec; metodoPago = metodo;
        total = t; desc = d; impuestos = imp; cant = c;
    }
    double getTotal() { return total; }
};


// Gestores 
class GestorInv {
private:
//Composicion porque el vector administra una coleccion de objetos vehiculos.
    vector<Vehiculo*> v;
    string nombreAlmacen = "Bodega Principal";
    int limiteCapacidad = 100;
    bool estadoOperativo = true;
    string responsable = "Admin";

public:
//Modulo: Baja y limpieza 
    ~GestorInv() { for (Vehiculo* veh : v) delete veh; }

    void agregar(Vehiculo* vehiculoNuevo) {
        if(v.size() < limiteCapacidad) v.push_back(vehiculoNuevo);
        else throw "Capacidad de inventario llena";
    }
//Modulo: Busqueda y consulta/ Consulta polimorfica
    Vehiculo* buscar(int id) {
        for (Vehiculo* veh : v) {
            if (veh->getId() == id) return veh;
        }
        return NULL;
    }
//Modulo: Reporte Global
    void mostrar() {
        if(v.empty()) cout << "Inventario vacio.\n";
        for (Vehiculo* veh : v) veh->mostrar();
    }
};

class GestorC {
private:
    vector<Cliente*> c;
    string baseDatos = "Local";
    int maxClientes = 500;
    string ultimaActualizacion = "Hoy";
    bool backupActivo = true;

public:
    ~GestorC() { for (Cliente* cli : c) delete cli; }
    void agregar(Cliente* cli) { c.push_back(cli); }
    Cliente* buscar(int id) {
        for (Cliente* cli : c) if (cli->getId() == id) return cli;
        return NULL;
    }
};

class GestorV {
private:
    vector<Vendedor*> v;
    string region = "Sierra";
    int maxVendedores = 50;
    string supervisor = "Gerencia";
    bool contratacionesAbiertas = false;

public:
    ~GestorV() { for (Vendedor* ven : v) delete ven; }
    void agregar(Vendedor* ven) { v.push_back(ven); }
    Vendedor* buscar(int id) {
        for (Vendedor* ven : v) if (ven->getId() == id) return ven;
        return NULL;
    }
};

class GestorVentas {
private:
    vector<Venta*> v;
    string moneda = "USD";
    double metaMensual = 50000.0;
    string periodo = "2026";
    bool auditoriaPendiente = false;

public:
    ~GestorVentas() { for (Venta* venta : v) delete venta; }
    void agregar(Venta* x) { v.push_back(x); }
    double total() {
        double t = 0;
        for (Venta* venta : v) t += venta->getTotal();
        return t;
    }
};
//Main 
int main() {
    GestorInv inv;
    GestorC gc;
    GestorV gv;
    GestorVentas ventas;

    int op;

    do {
        cout << "\n1 Registrar carro\n2 Registrar cliente\n3 Registrar vendedor\n4 Mostrar carros\n5 Realizar venta\n0 Salir\n> ";
        cin >> op;
//Envolvemos en try para evitar colapsos
        try {
            switch(op) {
                // Registrar carro 
            case 1: {
                cout << "\n--- REGISTRAR CARRO ---\n";
                int id, stock, tipo, anio;
                string m, mod, col;
                double p;

                cout << "ID: "; cin >> id;
                cout << "Marca: "; cin >> m;
                cout << "Modelo: "; cin >> mod;
                cout << "Anio: "; cin >> anio;
                cout << "Color: "; cin >> col;
                cout << "Precio: "; cin >> p;
                cout << "Stock: "; cin >> stock;
                cout << "Tipo (1 Gasolina, 2 Electrico, 3 Hibrido): "; cin >> tipo;
//Modulo de ingreso dinamico 
                if (tipo == 1) {
                  
                    inv.agregar(new AutoGasolina(id, m, mod, anio, col, p, stock, 2.0, 15.0, "Extra", 40.0, 4));
                }
                else if (tipo == 2) {
                    inv.agregar(new AutoElectrico(id, m, mod, anio, col, p, stock, 400.0, 60.0, 8.0, 150.0, true));
                }
                else if (tipo == 3) {
                    inv.agregar(new AutoHibrido(id, m, mod, anio, col, p, stock, 1.6, 12.0, "Super", 60.0, 4, 100.0, 15.0, 4.0, 100.0, false));
                }
                else throw "Tipo invalido";
                cout << "Vehiculo registrado con exito.\n";
                break;
            }
            case 2: {
                
                cout << "\n--- REGISTRAR CLIENTE ---\n";
                int id; string ced, n, tel, correo;
                cout << "ID: "; cin >> id;
                cout << "Cedula: "; cin >> ced;
                cout << "Nombre: "; cin >> n;
                cout << "Telefono: "; cin >> tel;
                cout << "Correo: "; cin >> correo;
                gc.agregar(new Cliente(id, ced, n, tel, correo));
                cout << "Cliente registrado.\n";
                break;
            }
            case 3: {
                cout << "\n--- REGISTRAR VENDEDOR ---\n";
                int id; string ced, n, tel, suc;
                cout << "ID: "; cin >> id;
                cout << "Cedula: "; cin >> ced;
                cout << "Nombre: "; cin >> n;
                cout << "Telefono: "; cin >> tel;
                cout << "Sucursal (Ej: Latacunga_Matriz): "; cin >> suc;
                gv.agregar(new Vendedor(id, ced, n, tel, suc));
                cout << "Vendedor registrado.\n";
                break;
            }
            case 4:
                cout << "\n--- LISTA DE CARROS ---\n";
                inv.mostrar();
                break;

            case 5: {
//Modulo: Gestion transaccional 
                cout << "\n--- REALIZAR VENTA ---\n";
                int idV, idC, idVeh, cant;
                cout << "ID vendedor: "; cin >> idV;
                cout << "ID cliente: "; cin >> idC;
                cout << "ID vehiculo: "; cin >> idVeh;
                cout << "Cantidad: "; cin >> cant;

                Vehiculo* v = inv.buscar(idVeh);
                Cliente* c = gc.buscar(idC);
                Vendedor* ven = gv.buscar(idV);
//Excepciones
                if (v == NULL) throw "Vehiculo no existe";
                if (c == NULL) throw "Cliente no existe";
                if (ven == NULL) throw "Vendedor no existe";
                if (v->getStock() < cant) throw "Stock insuficiente";

                double subtotal = v->getPrecio() * cant;
                double desc = (c->getCompras() > 0) ? subtotal * 0.02 : 0;
                //Calculo de impuestos usando polimorfismo
                double impuestos = (subtotal - desc) * 0.15; // 15% IVA
                double totalFinal = (subtotal - desc) + impuestos;
//Actualizaciones
                v->actualizarStock(-cant);
                c->comprar(totalFinal);
                ven->vender(totalFinal);

              
                ventas.agregar(new Venta(rand() % 1000, "2026-04-26", "Tarjeta", totalFinal, desc, impuestos, cant));

                cout << "Venta realizada correctamente. Total a pagar: $" << totalFinal << "\n";
                break;
            }
            }
        } catch(const char* e) {
            cout << "Error: " << e << endl;
        }

    } while(op != 0);

    return 0;
}
