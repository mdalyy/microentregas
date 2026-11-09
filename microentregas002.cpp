#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// CLASE PEDIDO
class Pedido {
public:
    int codigo;
    string cliente, direccion, zona, estado, prioridad;

    Pedido(int c, string cl, string d, string z, string e, string p) {
        codigo = c;
        cliente = cl;
        direccion = d;
        zona = z;
        estado = e;
        prioridad = p;
    }
};

// CLASE CONDUCTOR
class Conductor {
public:
    int codigo;
    string nombre, zona;

    Conductor(int c, string n, string z) {
        codigo = c;
        nombre = n;
        zona = z;
    }
};

// CLASE RUTA
class Ruta {
public:
    int codigo, codigoConductor;
    string zona;
    vector<int> pedidos;

    Ruta(int c, string z, int conductor) {
        codigo = c;
        zona = z;
        codigoConductor = conductor;
    }
};

// COLECCIONES DINAMICAS
vector<Pedido> pedidos;
vector<Conductor> conductores;
vector<Ruta> rutas;

int sigPedido = 1;
int sigConductor = 1;
int sigRuta = 1;

// SELECCIONAR ZONA
string seleccionarZona() {
    int opcion;

    do {
        cout << "\nSeleccione la zona:\n";
        cout << "1. Norte\n";
        cout << "2. Sur\n";
        cout << "3. Este\n";
        cout << "4. Oeste\n";
        cout << "5. Centro\n";
        cout << "Opcion: ";

        cin >> opcion;
        cin.ignore(10000, '\n');

        switch (opcion) {
        case 1: return "Norte";
        case 2: return "Sur";
        case 3: return "Este";
        case 4: return "Oeste";
        case 5: return "Centro";
        default:
            cout << "Opcion incorrecta. Intente nuevamente.\n";
        }
    } while (true);
}

// BUSCAR PEDIDO
int buscarPedido(int codigo) {
    for (int i = 0; i < pedidos.size(); i++) {
        if (pedidos[i].codigo == codigo)
            return i;
    }
    return -1;
}

// BUSCAR CONDUCTOR
int buscarConductor(int codigo) {
    for (int i = 0; i < conductores.size(); i++) {
        if (conductores[i].codigo == codigo)
            return i;
    }
    return -1;
}

// 1. REGISTRAR PEDIDO
void registrarPedido() {
    string cliente, direccion, zona, prioridad;

    cout << "Nombre del cliente: ";
    getline(cin, cliente);

    cout << "Direccion: ";
    getline(cin, direccion);

    zona = seleccionarZona();

    cout << "Prioridad (Alta, Media, Baja): ";
    getline(cin, prioridad);

    pedidos.push_back(Pedido(sigPedido, cliente, direccion,
        zona, "Pendiente", prioridad));

    cout << "Pedido registrado. Codigo: " << sigPedido << endl;
    sigPedido++;
}

// 2. LISTAR PEDIDOS
void listarPedidos() {
    if (pedidos.empty()) {
        cout << "No hay pedidos registrados.\n";
        return;
    }

    for (int i = 0; i < pedidos.size(); i++) {
        cout << "\nCodigo: " << pedidos[i].codigo
            << "\nCliente: " << pedidos[i].cliente
            << "\nDireccion: " << pedidos[i].direccion
            << "\nZona: " << pedidos[i].zona
            << "\nEstado: " << pedidos[i].estado
            << "\nPrioridad: " << pedidos[i].prioridad << "\n";
    }
}

// 3. BUSCAR PEDIDO
void consultarPedido() {
    int codigo;

    cout << "Codigo del pedido: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    int pos = buscarPedido(codigo);

    if (pos == -1) {
        cout << "Pedido no encontrado.\n";
    }
    else {
        cout << "Cliente: " << pedidos[pos].cliente << endl;
        cout << "Direccion: " << pedidos[pos].direccion << endl;
        cout << "Zona: " << pedidos[pos].zona << endl;
        cout << "Estado: " << pedidos[pos].estado << endl;
        cout << "Prioridad: " << pedidos[pos].prioridad << endl;
    }
}

// 4. ACTUALIZAR PEDIDO
void actualizarPedido() {
    int codigo;

    cout << "Codigo del pedido: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    int pos = buscarPedido(codigo);

    if (pos == -1) {
        cout << "Pedido no encontrado.\n";
        return;
    }

    if (pedidos[pos].estado != "Pendiente") {
        cout << "Solo se pueden actualizar pedidos pendientes.\n";
        return;
    }

    cout << "Nuevo cliente: ";
    getline(cin, pedidos[pos].cliente);

    cout << "Nueva direccion: ";
    getline(cin, pedidos[pos].direccion);

    cout << "Seleccione la nueva zona:\n";
    pedidos[pos].zona = seleccionarZona();

    cout << "Nueva prioridad (Alta, Media, Baja): ";
    getline(cin, pedidos[pos].prioridad);

    cout << "Pedido actualizado.\n";
}

// 5. ELIMINAR PEDIDO
void eliminarPedido() {
    int codigo;

    cout << "Codigo del pedido: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    int pos = buscarPedido(codigo);

    if (pos == -1) {
        cout << "Pedido no encontrado.\n";
        return;
    }

    if (pedidos[pos].estado != "Pendiente") {
        cout << "Solo se pueden eliminar pedidos pendientes.\n";
        return;
    }

    pedidos.erase(pedidos.begin() + pos);
    cout << "Pedido eliminado.\n";
}

// 6. REGISTRAR CONDUCTOR
void registrarConductor() {
    string nombre, zona;

    cout << "Nombre del conductor: ";
    getline(cin, nombre);

    cout << "Seleccione la zona del conductor:\n";
    zona = seleccionarZona();

    conductores.push_back(Conductor(sigConductor, nombre, zona));

    cout << "Conductor registrado. Codigo: " << sigConductor << endl;
    sigConductor++;
}

// 7. LISTAR CONDUCTORES
void listarConductores() {
    if (conductores.empty()) {
        cout << "No hay conductores registrados.\n";
        return;
    }

    for (int i = 0; i < conductores.size(); i++) {
        cout << "\nCodigo: " << conductores[i].codigo
            << "\nNombre: " << conductores[i].nombre
            << "\nZona: " << conductores[i].zona << "\n";
    }
}

// 8. GENERAR REPORTES
void generarReporte() {
    int pendientes = 0, enRuta = 0, entregados = 0;

    for (int i = 0; i < pedidos.size(); i++) {
        if (pedidos[i].estado == "Pendiente")
            pendientes++;
        else if (pedidos[i].estado == "En Ruta")
            enRuta++;
        else if (pedidos[i].estado == "Entregado")
            entregados++;
    }

    cout << "\n===== REPORTE GENERAL =====\n";
    cout << "Total de pedidos: " << pedidos.size() << endl;
    cout << "Pendientes: " << pendientes << endl;
    cout << "En ruta: " << enRuta << endl;
    cout << "Entregados: " << entregados << endl;

    ofstream archivo("reporte.txt");
    archivo << "REPORTE DE MICROENTREGAS\n";
    archivo << "Total: " << pedidos.size() << endl;
    archivo << "Pendientes: " << pendientes << endl;
    archivo << "En ruta: " << enRuta << endl;
    archivo << "Entregados: " << entregados << endl;
    archivo.close();

    cout << "Reporte guardado en reporte.txt\n";
}

// 9. CREAR RUTA Y CONSOLIDAR PEDIDOS
void crearRuta() {
    string zona;
    int codigoConductor;

    cout << "Seleccione la zona de la ruta:\n";
    zona = seleccionarZona();

    cout << "Codigo del conductor: ";
    cin >> codigoConductor;
    cin.ignore(10000, '\n');

    int posConductor = buscarConductor(codigoConductor);

    if (posConductor == -1) {
        cout << "Conductor no encontrado.\n";
        return;
    }

    if (conductores[posConductor].zona != zona) {
        cout << "El conductor pertenece a otra zona.\n";
        return;
    }

    Ruta nuevaRuta(sigRuta, zona, codigoConductor);

    for (int i = 0; i < pedidos.size(); i++) {
        if (pedidos[i].zona == zona &&
            pedidos[i].estado == "Pendiente") {
            nuevaRuta.pedidos.push_back(pedidos[i].codigo);
        }
    }

    if (nuevaRuta.pedidos.empty()) {
        cout << "No hay pedidos pendientes en esa zona.\n";
        return;
    }

    for (int i = 0; i < nuevaRuta.pedidos.size(); i++) {
        int pos = buscarPedido(nuevaRuta.pedidos[i]);
        pedidos[pos].estado = "En Ruta";
    }

    rutas.push_back(nuevaRuta);

    cout << "Ruta creada correctamente.\n";
    cout << "Codigo de ruta: " << sigRuta << endl;
    cout << "Pedidos consolidados: "
        << nuevaRuta.pedidos.size() << endl;

    sigRuta++;
}

// 10. LISTAR RUTAS
void listarRutas() {
    if (rutas.empty()) {
        cout << "No hay rutas registradas.\n";
        return;
    }

    for (int i = 0; i < rutas.size(); i++) {
        cout << "\nRuta: " << rutas[i].codigo << endl;
        cout << "Zona: " << rutas[i].zona << endl;
        cout << "Conductor: " << rutas[i].codigoConductor << endl;

        for (int j = 0; j < rutas[i].pedidos.size(); j++) {
            int pos = buscarPedido(rutas[i].pedidos[j]);

            if (pos != -1) {
                cout << "Pedido: " << pedidos[pos].codigo
                    << " | Cliente: " << pedidos[pos].cliente
                    << " | Estado: " << pedidos[pos].estado << endl;
            }
        }
    }
}

// 11. MARCAR PEDIDO COMO ENTREGADO
void marcarEntregado() {
    int codigo;

    cout << "Codigo del pedido: ";
    cin >> codigo;
    cin.ignore(10000, '\n');

    int pos = buscarPedido(codigo);

    if (pos == -1) {
        cout << "Pedido no encontrado.\n";
        return;
    }

    if (pedidos[pos].estado != "En Ruta") {
        cout << "El pedido debe estar en ruta.\n";
        return;
    }

    pedidos[pos].estado = "Entregado";
    cout << "Pedido marcado como entregado.\n";
}

// GUARDAR DATOS EN ARCHIVOS
void guardarDatos() {
    ofstream archivoPedidos("pedidos.csv");

    for (int i = 0; i < pedidos.size(); i++) {
        archivoPedidos << pedidos[i].codigo << ","
            << pedidos[i].cliente << ","
            << pedidos[i].direccion << ","
            << pedidos[i].zona << ","
            << pedidos[i].estado << ","
            << pedidos[i].prioridad << endl;
    }
    archivoPedidos.close();

    ofstream archivoConductores("conductores.csv");

    for (int i = 0; i < conductores.size(); i++) {
        archivoConductores << conductores[i].codigo << ","
            << conductores[i].nombre << ","
            << conductores[i].zona << endl;
    }
    archivoConductores.close();

    ofstream archivoRutas("rutas.csv");

    for (int i = 0; i < rutas.size(); i++) {
        archivoRutas << rutas[i].codigo << ","
            << rutas[i].zona << ","
            << rutas[i].codigoConductor << ",";

        for (int j = 0; j < rutas[i].pedidos.size(); j++) {
            if (j > 0)
                archivoRutas << ";";

            archivoRutas << rutas[i].pedidos[j];
        }

        archivoRutas << endl;
    }
    archivoRutas.close();
}

// MENU PRINCIPAL
int main() {
    int opcion;

    do {
        cout << "\n====================================\n";
        cout << " SISTEMA DE MICROENTREGAS\n";
        cout << "====================================\n";
        cout << "1. Registrar pedido\n";
        cout << "2. Listar pedidos\n";
        cout << "3. Buscar pedido\n";
        cout << "4. Actualizar pedido\n";
        cout << "5. Eliminar pedido\n";
        cout << "6. Registrar conductor\n";
        cout << "7. Listar conductores\n";
        cout << "8. Generar reportes\n";
        cout << "9. Crear ruta y consolidar pedidos\n";
        cout << "10. Listar rutas\n";
        cout << "11. Marcar pedido como entregado\n";
        cout << "12. Guardar datos y salir\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;
        cin.ignore(10000, '\n');

        switch (opcion) {
        case 1: registrarPedido(); break;
        case 2: listarPedidos(); break;
        case 3: consultarPedido(); break;
        case 4: actualizarPedido(); break;
        case 5: eliminarPedido(); break;
        case 6: registrarConductor(); break;
        case 7: listarConductores(); break;
        case 8: generarReporte(); break;
        case 9: crearRuta(); break;
        case 10: listarRutas(); break;
        case 11: marcarEntregado(); break;
        case 12:
            guardarDatos();
            cout << "Datos guardados. Programa finalizado.\n";
            break;
        default:
            cout << "Opcion incorrecta.\n";
        }

    } while (opcion != 12);

    return 0;
}
