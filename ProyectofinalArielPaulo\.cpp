#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

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

        if(i <= 0)
            throw "ID invalido";

        if(p <= 0)
            throw "Precio invalido";

        if(s < 0)
            throw "Stock invalido";

        id = i;
        marca = ma;
        modelo = mo;
        anioFabricacion = anio;
        color = col;
        precio = p;
        stock = s;
    }

    virtual ~Vehiculo(){}

    int getId() {
        return id;
    }

    double getPrecio() {
        return precio;
    }

    int getStock() {
        return stock;
    }

    void actualizarStock(int n) {
        stock += n;
    }

    virtual void mostrar() = 0;
    
};

// ===================== MOTOR GASOLINA =====================
class MotorGasolina {

protected:
    double cilindrada;
    double capacidadTanque;
    string tipoCombustible;
    double consumoKmL;
    int numCilindros;

public:

    MotorGasolina(double c, double cap, string tipo, double cons, int num) {

        if(c <= 0)
            throw "Cilindrada invalida";

        cilindrada = c;
        capacidadTanque = cap;
        tipoCombustible = tipo;
        consumoKmL = cons;
        numCilindros = num;
    }
};

// ===================== MOTOR ELECTRICO =====================
class MotorElectrico {

protected:
    double autonomia;
    double capBateriaKwh;
    double tiempoCargaHrs;
    double potenciaHp;
    bool cargaRapida;

public:

    MotorElectrico(double a, double capBat, double tiempoC, double pot, bool rapida) {

        if(a <= 0)
            throw "Autonomia invalida";

        autonomia = a;
        capBateriaKwh = capBat;
        tiempoCargaHrs = tiempoC;
        potenciaHp = pot;
        cargaRapida = rapida;
    }
};

// ===================== AUTO GASOLINA =====================
class AutoGasolina : public Vehiculo, public MotorGasolina {

public:

    AutoGasolina(
        int i, string ma, string mo, int anio, string col, double p, int s,
        double c, double cap, string tipo, double cons, int num
    )

    : Vehiculo(i,ma,mo,anio,col,p,s),
      MotorGasolina(c,cap,tipo,cons,num){}

    void mostrar() override {

        cout << "\n[Gasolina]";
        cout << "\nID: " << id;
        cout << "\nMarca: " << marca;
        cout << "\nModelo: " << modelo;
        cout << "\nAnio: " << anioFabricacion;
        cout << "\nColor: " << color;
        cout << "\nPrecio: $" << precio;
        cout << "\nStock: " << stock << endl;
    }
};

// ===================== AUTO ELECTRICO =====================
class AutoElectrico : public Vehiculo, public MotorElectrico {

public:

    AutoElectrico(
        int i, string ma, string mo, int anio, string col, double p, int s,
        double a, double capBat, double tiempoC, double pot, bool rapida
    )

    : Vehiculo(i,ma,mo,anio,col,p,s),
      MotorElectrico(a,capBat,tiempoC,pot,rapida){}

    void mostrar() override {

        cout << "\n[Electrico]";
        cout << "\nID: " << id;
        cout << "\nMarca: " << marca;
        cout << "\nModelo: " << modelo;
        cout << "\nAnio: " << anioFabricacion;
        cout << "\nColor: " << color;
        cout << "\nPrecio: $" << precio;
        cout << "\nStock: " << stock << endl;
    }
};

// ===================== AUTO HIBRIDO =====================
class AutoHibrido : public Vehiculo, public MotorGasolina, public MotorElectrico {

public:

    AutoHibrido(
        int i, string ma, string mo, int anio, string col, double p, int s,
        double c, double cap, string tipo, double cons, int num,
        double a, double capBat, double tiempoC, double pot, bool rapida
    )

    : Vehiculo(i,ma,mo,anio,col,p,s),
      MotorGasolina(c,cap,tipo,cons,num),
      MotorElectrico(a,capBat,tiempoC,pot,rapida){}

    void mostrar() override {

        cout << "\n[Hibrido]";
        cout << "\nID: " << id;
        cout << "\nMarca: " << marca;
        cout << "\nModelo: " << modelo;
        cout << "\nAnio: " << anioFabricacion;
        cout << "\nColor: " << color;
        cout << "\nPrecio: $" << precio;
        cout << "\nStock: " << stock << endl;
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

        if(nom == "")
            throw "Nombre invalido";

        id = i;
        cedula = ced;
        nombre = nom;
        telefono = tel;
        correo = mail;

        compras = 0;
        totalGastado = 0;
    }

    int getId() {
        return id;
    }

    int getCompras() {
        return compras;
    }

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

        if(nom == "")
            throw "Nombre invalido";

        id = i;
        cedula = ced;
        nombre = nom;
        telefono = tel;
        sucursal = suc;

        totalVendido = 0;
        comisionGenerada = 0;
    }

    int getId() {
        return id;
    }

    double getComision() {
        return comisionGenerada;
    }

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

    Venta(
        int idV,
        string fec,
        string metodo,
        double t,
        double d,
        double imp,
        int c
    ) {

        idVenta = idV;
        fecha = fec;
        metodoPago = metodo;

        total = t;
        desc = d;
        impuestos = imp;
        cant = c;
    }
};

// ===================== GESTOR INVENTARIO =====================
class GestorInv {

private:
    vector<Vehiculo*> v;

public:

    ~GestorInv() {

        for(Vehiculo* veh : v)
            delete veh;
    }

    bool existeId(int id) {

        for(Vehiculo* veh : v) {

            if(veh->getId() == id)
                return true;
        }

        return false;
    }

    void agregar(Vehiculo* nuevoVehiculo) {

        v.push_back(nuevoVehiculo);
    }

    Vehiculo* buscar(int id) {

        for(Vehiculo* veh : v) {

            if(veh->getId() == id)
                return veh;
        }

        return nullptr;
    }

    void mostrar() {

        if(v.empty()) {

            cout << "\nNo hay vehiculos registrados.\n";
            return;
        }

        for(Vehiculo* veh : v)
            veh->mostrar();
    }
};

// ===================== GESTOR CLIENTES =====================
class GestorC {

private:
    vector<Cliente*> c;

public:

    ~GestorC() {

        for(Cliente* cli : c)
            delete cli;
    }

    bool existeId(int id) {

        for(Cliente* cli : c) {

            if(cli->getId() == id)
                return true;
        }

        return false;
    }

    void agregar(Cliente* nuevoCliente) {

        c.push_back(nuevoCliente);
    }

    Cliente* buscar(int id) {

        for(Cliente* cli : c) {

            if(cli->getId() == id)
                return cli;
        }

        return nullptr;
    }
};

// ===================== GESTOR VENDEDORES =====================
class GestorV {

private:
    vector<Vendedor*> v;

public:

    ~GestorV() {

        for(Vendedor* ven : v)
            delete ven;
    }

    bool existeId(int id) {

        for(Vendedor* ven : v) {

            if(ven->getId() == id)
                return true;
        }

        return false;
    }

    void agregar(Vendedor* nuevoVendedor) {

        v.push_back(nuevoVendedor);
    }

    Vendedor* buscar(int id) {

        for(Vendedor* ven : v) {

            if(ven->getId() == id)
                return ven;
        }

        return nullptr;
    }
};

// ===================== GESTOR VENTAS =====================
class GestorVentas {

private:
    vector<Venta*> v;

public:

    ~GestorVentas() {

        for(Venta* venta : v)
            delete venta;
    }

    void agregar(Venta* nuevaVenta) {

        v.push_back(nuevaVenta);
    }
};

// ===================== LIMPIAR CIN =====================
void limpiarCin() {

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ===================== MAIN =====================
int main() {

    srand(time(0));

    GestorInv inv;
    GestorC gc;
    GestorV gv;
    GestorVentas ventas;

    int op;

    do {

        cout << "\n========== SISTEMA CONCESIONARIA ==========";
        cout << "\n1. Registrar carro";
        cout << "\n2. Registrar cliente";
        cout << "\n3. Registrar vendedor";
        cout << "\n4. Mostrar carros";
        cout << "\n5. Realizar venta";
        cout << "\n0. Salir";
        cout << "\nSeleccione: ";

        cin >> op;

        if(cin.fail()) {

            limpiarCin();
            cout << "\nEntrada invalida.\n";
            continue;
        }

        try {

            switch(op) {

            // ===================== REGISTRAR CARRO =====================
            case 1: {

                int id, stock, tipo, anio;
                string marca, modelo, color;
                double precio;

                cout << "\n=== REGISTRO VEHICULO ===";

                cout << "\nIngrese ID: ";
                cin >> id;

                if(inv.existeId(id))
                    throw "Ese ID ya existe";

                cout << "Ingrese Marca: ";
                cin >> marca;

                cout << "Ingrese Modelo: ";
                cin >> modelo;

                cout << "Ingrese Anio: ";
                cin >> anio;

                cout << "Ingrese Color: ";
                cin >> color;

                cout << "Ingrese Precio: ";
                cin >> precio;

                cout << "Ingrese Stock: ";
                cin >> stock;

                cout << "\nTipo:";
                cout << "\n1. Gasolina";
                cout << "\n2. Electrico";
                cout << "\n3. Hibrido";
                cout << "\nSeleccione: ";
                cin >> tipo;

                if(tipo == 1) {

                    inv.agregar(
                        new AutoGasolina(
                            id,marca,modelo,anio,color,precio,stock,
                            2.0,15,"Extra",40,4
                        )
                    );
                }

                else if(tipo == 2) {

                    inv.agregar(
                        new AutoElectrico(
                            id,marca,modelo,anio,color,precio,stock,
                            400,60,8,150,true
                        )
                    );
                }

                else if(tipo == 3) {

                    inv.agregar(
                        new AutoHibrido(
                            id,marca,modelo,anio,color,precio,stock,
                            1.6,12,"Super",60,4,
                            100,15,4,100,false
                        )
                    );
                }

                else {

                    throw "Tipo invalido";
                }

                cout << "\nVehiculo registrado con exito.\n";

                break;
            }

            // ===================== REGISTRAR CLIENTE =====================
            case 2: {

                int id;
                string ced, nom, tel, mail;

                cout << "\nIngrese ID: ";
                cin >> id;

                if(gc.existeId(id))
                    throw "Ese ID ya existe";

                cout << "Ingrese Cedula: ";
                cin >> ced;

                cout << "Ingrese Nombre: ";
                cin >> nom;

                cout << "Ingrese Telefono: ";
                cin >> tel;

                cout << "Ingrese Correo: ";
                cin >> mail;

                gc.agregar(
                    new Cliente(id,ced,nom,tel,mail)
                );

                cout << "\nCliente registrado con exito.\n";

                break;
            }

            // ===================== REGISTRAR VENDEDOR =====================
            case 3: {

                int id;
                string ced, nom, tel, suc;

                cout << "\nIngrese ID: ";
                cin >> id;

                if(gv.existeId(id))
                    throw "Ese ID ya existe";

                cout << "Ingrese Cedula: ";
                cin >> ced;

                cout << "Ingrese Nombre: ";
                cin >> nom;

                cout << "Ingrese Telefono: ";
                cin >> tel;

                cout << "Ingrese Sucursal: ";
                cin >> suc;

                gv.agregar(
                    new Vendedor(id,ced,nom,tel,suc)
                );

                cout << "\nVendedor registrado con exito.\n";

                break;
            }

            // ===================== MOSTRAR VEHICULOS =====================
            case 4: {

                cout << "\n========== INVENTARIO ==========";

                inv.mostrar();

                break;
            }

            // ===================== REALIZAR VENTA =====================
            case 5: {

                int idV, idC, idVeh, cant;

                cout << "\n=== REALIZAR VENTA ===";

                cout << "\nIngrese ID vendedor: ";
                cin >> idV;

                cout << "Ingrese ID cliente: ";
                cin >> idC;

                cout << "Ingrese ID vehiculo: ";
                cin >> idVeh;

                cout << "Ingrese cantidad: ";
                cin >> cant;

                if(cant <= 0)
                    throw "Cantidad invalida";

                Vehiculo* v = inv.buscar(idVeh);
                Cliente* c = gc.buscar(idC);
                Vendedor* ven = gv.buscar(idV);

                if(v == nullptr)
                    throw "Vehiculo no existe";

                if(c == nullptr)
                    throw "Cliente no existe";

                if(ven == nullptr)
                    throw "Vendedor no existe";

                if(v->getStock() < cant)
                    throw "Stock insuficiente";

                double subtotal = v->getPrecio() * cant;

                double desc = 0;

                if(c->getCompras() > 0)
                    desc = subtotal * 0.02;

                double impuestos = (subtotal - desc) * 0.15;

                double totalFinal = (subtotal - desc) + impuestos;

                double comision = totalFinal * 0.01;

                v->actualizarStock(-cant);

                c->comprar(totalFinal);

                ven->vender(totalFinal);

                ventas.agregar(
                    new Venta(
                        rand()%10000,
                        "2026",
                        "Tarjeta",
                        totalFinal,
                        desc,
                        impuestos,
                        cant
                    )
                );

                cout << "\n========== FACTURA ==========";
                cout << "\nSubtotal: $" << subtotal;
                cout << "\nDescuento: $" << desc;
                cout << "\nImpuestos: $" << impuestos;
                cout << "\nTotal Final: $" << totalFinal;
                cout << "\nComision vendedor (1%): $" << comision;
                cout << "\nVenta realizada con exito.\n";

                break;
            }

            // ===================== SALIR =====================
            case 0: {

                cout << "\nSaliendo del sistema...\n";
                break;
            }

            // ===================== DEFAULT =====================
            default: {

                cout << "\nOpcion invalida.\n";
            }

            }

        }

        catch(const char* e) {

            cout << "\nERROR: " << e << endl;
        }

    } while(op != 0);

    return 0;
}
