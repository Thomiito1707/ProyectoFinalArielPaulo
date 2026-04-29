#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 

using namespace std;

// ===================== CLASE ABSTRACTA =====================
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
    Vehiculo(int i, string ma, string mo, int anio, string col, double p, int s) {
        if (p <= 0) throw "Precio invalido";
        if (s < 0) throw "Stock invalido";

        id = i; 
        marca = ma; 
        modelo = mo; 
        anioFabricacion = anio; 
        color = col; 
        precio = p; 
        stock = s;
    }

    virtual ~Vehiculo() {}

    int getId() { return id; }
    string getMarca() { return marca; }
    double getPrecio() { return precio; }
    int getStock() { return stock; }

    void actualizarStock(int n) { stock += n; }

    virtual void mostrar() = 0;
};

// ===================== MOTORES =====================
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

        cilindrada = c; 
        capacidadTanque = cap; 
        tipoCombustible = tipo; 
        consumoKmL = cons; 
        numCilindros = num;
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

        autonomia = a; 
        capBateriaKwh = capBat; 
        tiempoCargaHrs = tiempoC; 
        potenciaHp = pot; 
        cargaRapida = rapida;
    }
};

// ===================== HERENCIA =====================
class AutoGasolina : public Vehiculo, public MotorGasolina {
public:
    AutoGasolina(int i, string ma, string mo, int anio, string col, double p, int s,
                 double c, double cap, string tipo, double cons, int num)
        : Vehiculo(i,ma,mo,anio,col,p,s), MotorGasolina(c, cap, tipo, cons, num) {}

    void mostrar() override {
        cout << "[Gasolina] " << marca << " " << modelo 
             << " (" << anioFabricacion << ") - Color: " << color 
             << " | $" << precio << " | Stock: " << stock << endl;
    }
};

class AutoElectrico : public Vehiculo, public MotorElectrico {
public:
    AutoElectrico(int i, string ma, string mo, int anio, string col, double p, int s,
                  double a, double capBat, double tiempoC, double pot, bool rapida)
        : Vehiculo(i,ma,mo,anio,col,p,s), MotorElectrico(a, capBat, tiempoC, pot, rapida) {}

    void mostrar() override {
        cout << "[Electrico] " << marca << " " << modelo 
             << " (" << anioFabricacion << ") - Color: " << color 
             << " | $" << precio << " | Stock: " << stock << endl;
    }
};

class AutoHibrido : public Vehiculo, public MotorGasolina, public MotorElectrico {
public:
    AutoHibrido(int i, string ma, string mo, int anio, string col, double p, int s,
                double c, double cap, string tipo, double cons, int num,
                double a, double capBat, double tiempoC, double pot, bool rapida)
        : Vehiculo(i,ma,mo,anio,col,p,s),
          MotorGasolina(c, cap, tipo, cons, num),
          MotorElectrico(a, capBat, tiempoC, pot, rapida) {}

    void mostrar() override {
        cout << "[Hibrido] " << marca << " " << modelo 
             << " (" << anioFabricacion << ") - Color: " << color 
             << " | $" << precio << " | Stock: " << stock << endl;
    }
};

// ===================== CLIENTE =====================
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

        id = i; 
        cedula = ced; 
        nombre = nom; 
        telefono = tel; 
        correo = mail; 
        compras = 0; 
        totalGastado = 0;
    }

    int getId() { return id; }
    int getCompras() { return compras; }

    void comprar(double x) { 
        compras++; 
        totalGastado += x; 
    }
};

// ===================== VENDEDOR =====================
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

        id = i; 
        cedula = ced; 
        nombre = nom; 
        telefono = tel; 
        sucursal = suc; 
        totalVendido = 0; 
        comisionGenerada = 0;
    }

    int getId() { return id; }

    void vender(double x) { 
        totalVendido += x; 
        comisionGenerada += (x * 0.01); 
    }
};

// ===================== VENTA =====================
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
        idVenta = idV; 
        fecha = fec; 
        metodoPago = metodo;
        total = t; 
        desc = d; 
        impuestos = imp; 
        cant = c;
    }

    double getTotal() { return total; }
};

// ===================== GESTORES =====================
class GestorInv {
private:
    vector<Vehiculo*> v;

public:
    ~GestorInv() { 
        for (Vehiculo* veh : v) delete veh; 
    }

    void agregar(Vehiculo* vehiculoNuevo) {
        v.push_back(vehiculoNuevo);
    }

    Vehiculo* buscar(int id) {
        for (Vehiculo* veh : v)
            if (veh->getId() == id) return veh;
        return nullptr;
    }

    void mostrar() {
        if (v.empty()) {
            cout << "No hay vehiculos registrados.\n";
            return;
        }
        for (Vehiculo* veh : v)
            veh->mostrar();
    }
};

class GestorC {
private:
    vector<Cliente*> c;

public:
    ~GestorC() { 
        for (Cliente* cli : c) delete cli; 
    }

    void agregar(Cliente* nuevoCliente) {
        c.push_back(nuevoCliente);
    }

    Cliente* buscar(int id) {
        for (Cliente* cli : c)
            if (cli->getId() == id) return cli;
        return nullptr; 
    }
};

class GestorV {
private:
    vector<Vendedor*> v;

public:
    ~GestorV() { 
        for (Vendedor* ven : v) delete ven; 
    }

    void agregar(Vendedor* nuevoVendedor) {
        v.push_back(nuevoVendedor);
    }

    Vendedor* buscar(int id) {
        for (Vendedor* ven : v)
            if (ven->getId() == id) return ven;
        return nullptr;
    }
};

class GestorVentas {
private:
    vector<Venta*> v;

public:
    ~GestorVentas() { 
        for (Venta* venta : v) delete venta; 
    }

    void agregar(Venta* nuevaVenta) {
        v.push_back(nuevaVenta);
    }
};

// ===================== MAIN =====================
int main() {
    GestorInv inv;
    GestorC gc;
    GestorV gv;
    GestorVentas ventas;

    int op;

    do {
        cout << "\n=== SISTEMA DE CONCESIONARIA ===";
        cout << "\n1 Registrar carro\n2 Registrar cliente\n3 Registrar vendedor\n4 Mostrar carros\n5 Realizar venta\n0 Salir\n> ";
        cin >> op;

        try {
            switch(op) {

            case 1: {
                int id, stock, tipo, anio;
                string m, mod, col;
                double p;

                cout << "ID, Marca, Modelo, Anio, Color, Precio, Stock, Tipo (1.Gasolina, 2.Electrico, 3.Hibrido): ";
                cin >> id >> m >> mod >> anio >> col >> p >> stock >> tipo;

                if (tipo == 1)
                    inv.agregar(new AutoGasolina(id,m,mod,anio,col,p,stock,2,15,"Extra",40,4));
                else if (tipo == 2)
                    inv.agregar(new AutoElectrico(id,m,mod,anio,col,p,stock,400,60,8,150,true));
                else if (tipo == 3)
                    inv.agregar(new AutoHibrido(id,m,mod,anio,col,p,stock,1.6,12,"Super",60,4,100,15,4,100,false));
                else throw "Tipo invalido";

                cout << "Vehiculo registrado con exito.\n";
                break;
            }

            case 2: {
                int id;
                string ced, nom, tel, mail;
                cout << "Ingrese ID, Cedula, Nombre, Telefono, Correo (sin espacios): ";
                cin >> id >> ced >> nom >> tel >> mail;
                gc.agregar(new Cliente(id, ced, nom, tel, mail));
                cout << "Cliente registrado con exito.\n";
                break;
            }

            case 3: {
                int id;
                string ced, nom, tel, suc;
                cout << "Ingrese ID, Cedula, Nombre, Telefono, Sucursal (sin espacios): ";
                cin >> id >> ced >> nom >> tel >> suc;
                gv.agregar(new Vendedor(id, ced, nom, tel, suc));
                cout << "Vendedor registrado con exito.\n";
                break;
            }

            case 4: {
                cout << "\n--- INVENTARIO DE VEHICULOS ---\n";
                inv.mostrar();
                break;
            }

            case 5: {
                int idV, idC, idVeh, cant;
                cout << "ID Vendedor, ID Cliente, ID Vehiculo, Cantidad: ";
                cin >> idV >> idC >> idVeh >> cant;

                Vehiculo* v = inv.buscar(idVeh);
                Cliente* c = gc.buscar(idC);
                Vendedor* ven = gv.buscar(idV);

                if (v == nullptr) throw "Vehiculo no existe";
                if (c == nullptr) throw "Cliente no existe";
                if (ven == nullptr) throw "Vendedor no existe";
                if (v->getStock() < cant) throw "Stock insuficiente";

                double subtotal = v->getPrecio() * cant;
                double desc = (c->getCompras() > 0) ? subtotal * 0.02 : 0;
                double impuestos = (subtotal - desc) * 0.15;
                double totalFinal = (subtotal - desc) + impuestos;

                v->actualizarStock(-cant);
                c->comprar(totalFinal);
                ven->vender(totalFinal);

                ventas.agregar(new Venta(rand()%1000, "2026", "Tarjeta", totalFinal, desc, impuestos, cant));

                cout << "Venta realizada con exito. Total a pagar: $" << totalFinal << endl;
                break;
            }
            
            case 0:
                cout << "Saliendo del sistema...\n";
                break;
                
            default:
                cout << "Opcion no valida.\n";
            }

        } catch(const char* e) {
            cout << "Error: " << e << endl;
        }

    } while(op != 0);

    return 0;
}
