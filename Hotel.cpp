#include <iomanip>
#include "Hotel.hpp"

// -------------------------------------------------
// -----------   I N M U E B L E S   ---------------
// -------------------------------------------------

Inmueble::Inmueble() {
    direccion = nullptr;
    numCuartos = -1;
    precio = -1;
    dniPropietario[0] = '\0';
}

Inmueble::Inmueble(Inmueble& original) {
    direccion = new char[strlen(original.getDireccion()) + 1];
    strcpy(direccion, original.getDireccion());
    numCuartos = original.getNumCuartos();
    precio = original.getPrecio();
    strcpy(dniPropietario, original.getDniPropietario());
}


Inmueble& Inmueble::operator=(Inmueble& original) {
    if (this != &original) {
        delete[] direccion;
        direccion = new char[strlen(original.getDireccion()) + 1];
        strcpy(direccion, original.getDireccion());
        numCuartos = original.getNumCuartos();
        precio = original.getPrecio();
        strcpy(dniPropietario, original.getDniPropietario());
    }   
    return *this;
}

Inmueble::~Inmueble() {
    delete[] direccion;
}

char* Inmueble::getDireccion() const {
    return direccion;
}

int Inmueble::getNumCuartos() const {
    return numCuartos;
}

float Inmueble::getPrecio() const {
    return precio;
}

char* Inmueble::getDniPropietario() {
    return dniPropietario;
}

void Inmueble::setNumCuartos(int cuartos) {
    numCuartos = cuartos;
}

void Inmueble::setPrecio(float precio) {
    this->precio = precio;
}

void Inmueble::setDireccion(char* direccion) {
    delete[] this->direccion;
    this->direccion = new char[strlen(direccion) + 1];
    strcpy(this->direccion, direccion);
}

void Inmueble::setDniPropietario (char* dni) {
    strcpy(this->dniPropietario,dni);
}

void Inmueble::print() const {
    cout << setw(57) << direccion; // 128
    cout << setw(10) << numCuartos;
    cout << setw(10) << precio;
    cout << endl;
}

// -------------------------------------------------
// ----------   LISTA DE INMUEBLES   ---------------
// -------------------------------------------------

ListaDeInmuebles::ListaDeInmuebles(int size) {
    if (size >=1) {
        this->size = size;
    } else {
        this->size = 0;
    }
    Lista = new Inmueble[this->size];
}



ListaDeInmuebles& ListaDeInmuebles::operator=(const ListaDeInmuebles& other) {
    if (this != &other) {
        size = other.size;
        Inmueble* nuevaLista = new Inmueble[size];

        for (int i = 0; i < size; i++) {
            nuevaLista[i] = other.Lista[i];
        }
        delete[] Lista;
        Lista = nuevaLista;
    }
    return *this;
}

ListaDeInmuebles::~ListaDeInmuebles() {
    delete[] Lista;
}

int ListaDeInmuebles::getSize() {
    return size; 
}

Inmueble& ListaDeInmuebles::getInmueble(int index) {
    if (index >= 0 && index < size) {
        return Lista[index];
    }
}

void ListaDeInmuebles::leerInmuebles() {
    FILE* archivo = fopen("inmuebles.txt", "r");
    if (archivo != NULL) {
        char direccion[100];
        int numCuartos;
        float precio;
        char dniPropietario[9];
        while (fscanf(archivo, "%[^\n]\n%d\n%f\n%s\n\n", direccion, &numCuartos, &precio, dniPropietario) == 4) {
            Inmueble nuevoInmueble;
            nuevoInmueble.setDireccion(direccion);
            nuevoInmueble.setNumCuartos(numCuartos);
            nuevoInmueble.setPrecio(precio);
            nuevoInmueble.setDniPropietario(dniPropietario);
            addInmueble(nuevoInmueble);
        }
        fclose(archivo);
    } else {
        cout << "No se pudo abrir 'inmuebles.txt'" << endl;
    }
}

void ListaDeInmuebles::guardarInmuebles() {
    FILE* archivo = fopen("inmuebles.txt","w");

    if (archivo != NULL) {
        for (int i = 0; i < size;  i++) {
            Inmueble& inmueble = Lista[i];
            fprintf(archivo, "%s\n%d\n%f\n%s\n\n", inmueble.getDireccion(), inmueble.getNumCuartos(), inmueble.getPrecio(), inmueble.getDniPropietario());
        }

        fclose(archivo);
    } else {
        cout << "No se pudo abrir 'inmuebles.txt'" << endl;
    }
}

void ListaDeInmuebles::addInmueble(Inmueble& inmueble) {
    Inmueble* nuevaLista = new Inmueble[size + 1];
    for (int i = 0; i < size; i++) {
        nuevaLista[i] = Lista[i];
    }
    nuevaLista[size] = inmueble;
    delete[] Lista;
    Lista = nuevaLista;
    size++;
}

void ListaDeInmuebles::eliminarInmueble(int index) {
    if (index >= 0 && index < size) {
        Inmueble* nuevaLista = new Inmueble[size - 1];
        for (int i = 0, j = 0; i < size; i++) {
            if (i != index) {
                nuevaLista[j++] = Lista[i];
            }
        }
        delete[] Lista;
        Lista = nuevaLista;
        size--;
    } else {
        cout << "Indice fuera de rango" << endl;
    }
}

ListaDeInmuebles ListaDeInmuebles::buscarPorDireccion(char* direccion) {
    ListaDeInmuebles resultado(0);
    for (int i = 0; i < size; i++) {
        if (strcontains(Lista[i].getDireccion(), direccion)) {
            resultado.addInmueble(Lista[i]);
        }
    } 
    return resultado;
}

ListaDeInmuebles ListaDeInmuebles::buscarPorPrecio(float precioMin, float precioMax) {
    ListaDeInmuebles resultado(0);
    for (int i = 0; i < size; i++) {
        float precio = Lista[i].getPrecio();
        if ((precioMin == -1 || precio >= precioMin) && (precioMax == -1 || precio <= precioMax)) {
            resultado.addInmueble(Lista[i]);
        }
    }
    return resultado;
}

ListaDeInmuebles ListaDeInmuebles::buscarPorNumCuartos(int min, int max) {
    ListaDeInmuebles resultado(0);
    for (int i = 0; i < size; i++) {
        int numCuartos = Lista[i].getNumCuartos();
        if ((min == -1 || numCuartos >= min) && (max == -1 || numCuartos <= max)) {
            resultado.addInmueble(Lista[i]);
        }
    }
    return resultado;
}

ListaDeInmuebles ListaDeInmuebles::filtrarPorPropietario(char* dniPropietario){
    ListaDeInmuebles resultado(0);
    for (int i = 0; i < size; i++) {
        if (strcomp(Lista[i].getDniPropietario(),dniPropietario)) {
            resultado.addInmueble(Lista[i]);
        }
    }
    return resultado;
}

void ListaDeInmuebles::mostrar() const {
    cout << "\x1B[1;35m";
    cout << setw(60) << "Direccion" // 130
        // << setw(20) << "Numero de Cuartos"
        << setw(10) << "Cuartos"
        << setw(10) << "Precio" << endl;
    cout << "\x1B[0m";


    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        Lista[i].print();
    }
}

// -------------------------------------------------
// ---------------  C L I E N T E  -----------------
// -------------------------------------------------

//el objeto YY es un tipo de objeto y, si es asi es HERENCIA

Cliente::Cliente() {
    nombre = nullptr;
    for(int i = 0; i < 9; i++) {
        dni[i] = '-';
    }
    for(int i = 0; i < 10; i++) {
        telefono[i] = '-';
    }
}

Cliente::Cliente(Cliente &original) {
    nombre = new char[strlen(original.getNombre()) + 1];
    strcpy(nombre, original.getNombre());
    strcpy(dni, original.getDni());
    strcpy(telefono, original.getTelefono());
}

Cliente& Cliente::operator=(Cliente &original) {
    if (this != &original) {
        delete[] nombre;
        nombre = new char[strlen(original.getNombre()) + 1];
        strcpy(nombre, original.getNombre());
        strcpy(dni, original.getDni());
        strcpy(telefono, original.getTelefono());
    }
    return *this;
}

Cliente::~Cliente() {
    delete[] nombre;
}

char* Cliente::getNombre() const {
    return nombre;
}

char* Cliente::getDni() {
    return dni;
}

char* Cliente::getTelefono() {
    return telefono;
}

void Cliente::setNombre(char* nombre) {
    delete[] this->nombre;
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);
}

void Cliente::setDni(char* dni) {
    strcpy(this->dni, dni);
}

void Cliente::setTelefono(char* telefono) {
    strcpy(this->telefono, telefono);
}

void Cliente::print() const {
    cout << "Nombre: " << nombre << endl;
    cout << "DNI: " << dni << endl;
    cout << "Telefono: " << telefono << endl;
}

// -------------------------------------------------
// -----------   LISTA DE CLIENTES   ---------------
// -------------------------------------------------

ListaDeClientes::ListaDeClientes(int size) {
    if (size >= 1) {
        this->size = size;
    }
    Lista = new Cliente[size];
}

ListaDeClientes::ListaDeClientes(ListaDeClientes& other) {
    size = other.getSize();
    Lista = new Cliente[size];
    for (int i = 0; i < size; i++) {
        Lista[i] = other.Lista[i];
    }
}

ListaDeClientes& ListaDeClientes::operator=(const ListaDeClientes& other) {
    if (this != &other) {
        size = other.size;
        Cliente* nuevaLista = new Cliente[size];

        for (int i = 0; i < size; ++i) {
            nuevaLista[i] = other.Lista[i];
        }

        delete[] Lista;
        Lista = nuevaLista;
    }
    return *this;
}

ListaDeClientes::~ListaDeClientes() {
    delete[] Lista;
}

int ListaDeClientes::getSize() {
    return size; 
}

Cliente& ListaDeClientes::getCliente(int index) {
    return Lista[index];
}

void ListaDeClientes::addCliente(Cliente& cliente) {
    Cliente* nuevaLista = new Cliente[size + 1];
    for (int i = 0; i < size; i++) {
        nuevaLista[i] = Lista[i];
    }
    nuevaLista[size] = cliente;
    delete[] Lista;
    Lista = nuevaLista;
    size++;
}

ListaDeClientes ListaDeClientes::buscarPorNombre(char* nombre) {
    ListaDeClientes resultado(0);
    for (int i = 0; i < size; i++) {
        if (strcontains(Lista[i].getNombre(), nombre)) {
            resultado.addCliente(Lista[i]);
        }
    }
    return resultado;
}

ListaDeClientes ListaDeClientes::buscarPorDni(char* dni) {
    ListaDeClientes resultado(0);
    for (int i = 0; i < size; i++) {
        if (strcomp(Lista[i].getDni(), dni)) {
            resultado.addCliente(Lista[i]);
        }
    }
    return resultado;
}

ListaDeClientes ListaDeClientes::buscarPorTelefono(char* telefono) {
    ListaDeClientes resultado(0);
    for (int i = 0; i < size; i++) {
        if (strcomp(Lista[i].getTelefono(), telefono)) {
            resultado.addCliente(Lista[i]);
        }
    }
    return resultado;
}

void ListaDeClientes::mostrar() const {
    for (int i = 0; i < size; i++){
        cout << i+1 <<". ";
        Lista[i].print();
    }
}

// -------------------------------------------------
// ---------   P R O P I E T A R I O   -------------
// -------------------------------------------------

Propietario::Propietario() {
    nombre = nullptr;
    contrasena = nullptr;
    for(int i = 0; i < 9; i++) {
        dni[i] = '-';
    }
    for(int i = 0; i < 10; i++) {
        telefono[i] = '-';
    }
}

Propietario::Propietario(Propietario &original) {
    nombre = new char[strlen(original.getNombre()) + 1];
    strcpy(nombre, original.getNombre());
    strcpy(dni, original.getDni());
    strcpy(telefono, original.getTelefono());
    strcpy(contrasena, original.getContrasena());
}

Propietario& Propietario::operator=(Propietario &original) {
    if (this != &original) {
        delete[] nombre;
        delete[] contrasena;
        nombre = new char[strlen(original.getNombre()) + 1];
        strcpy(nombre, original.getNombre());
        strcpy(dni, original.getDni());
        strcpy(telefono, original.getTelefono());
        contrasena = new char[strlen(original.getContrasena()) + 1];
        strcpy(contrasena, original.getContrasena()); 
    }
    return *this;
}

Propietario::~Propietario() {
    delete[] nombre;
    delete[] contrasena;
}

char* Propietario::getNombre() const {
    return nombre;
}

char* Propietario::getDni() {
    return dni;
}

char* Propietario::getTelefono() {
    return telefono;
}

char* Propietario::getContrasena(){
    return contrasena;
}

void Propietario::setNombre(char* nombre) {
    delete[] this->nombre;
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);
}

void Propietario::setDni(char* dni) {
    strcpy(this->dni, dni);
}

void Propietario::setTelefono(char* telefono) {
    strcpy(this->telefono, telefono);
}

void Propietario::setContrasena(char* contrasena) {
        delete[] this->contrasena;
        this->contrasena = new char[strlen(contrasena) + 1];
        strcpy(this->contrasena, contrasena);
    }

void Propietario::print() const {
    cout << "Nombre: " << nombre << endl;
    cout << "DNI: " << dni << endl;
    cout << "Telefono: " << telefono << endl;
}

// -------------------------------------------------
// ----------  LISTA DE PROPIETARIOS  --------------
// -------------------------------------------------

ListaDePropietarios::ListaDePropietarios(int size) {
    if (size >=1) {
        this->size = size;
    } else {
        this->size = 0;
    }
    Lista = new Propietario[this->size];
}

ListaDePropietarios::ListaDePropietarios(ListaDePropietarios& other) {
    size = other.getSize();
    Lista = new Propietario[size];
    for (int i = 0; i < size; i++) {
        Lista[i] = other.Lista[i];
    }
}

ListaDePropietarios& ListaDePropietarios::operator=(const ListaDePropietarios& other) {
    if (this != &other) {
        size = other.size;
        Propietario* nuevaLista = new Propietario[size];

        for (int i = 0; i < size; ++i) {
            nuevaLista[i] = other.Lista[i];
        }

        delete[] Lista;
        Lista = nuevaLista;
    }
    return *this;
}

ListaDePropietarios::~ListaDePropietarios() {
    delete[] Lista;
}

int ListaDePropietarios::getSize() {
    return size; 
}

Propietario& ListaDePropietarios::getPropietario(int index) {
    return Lista[index];
}

ListaDePropietarios ListaDePropietarios::buscarPorNombre(char* nombre) {
    ListaDePropietarios resultado(0);
    for (int i = 0; i < size; i++) {
        if (strcontains(Lista[i].getNombre(), nombre)) {
            resultado.addPropietario(Lista[i]);
        }
    }
    return resultado;
}

ListaDePropietarios ListaDePropietarios::buscarPorDni(char* dni) {
    ListaDePropietarios resultado(0);
    for (int i = 0; i < size; i++) {
        if (strcomp(Lista[i].getDni(), dni)) {
            resultado.addPropietario(Lista[i]);
        }
    }
    return resultado;
}

ListaDePropietarios ListaDePropietarios::buscarPorTelefono(char* telefono) {
    ListaDePropietarios resultado(0);
    for (int i = 0; i < size; i++) {
        if (strcomp(Lista[i].getTelefono(), telefono)) {
            resultado.addPropietario(Lista[i]);
        }
    }
    return resultado;
}

void ListaDePropietarios::addPropietario(Propietario& propietario) {
    Propietario* nuevaLista = new Propietario[size + 1];
    for (int i = 0; i < size; i++) {
        nuevaLista[i] = Lista[i];
    }
    nuevaLista[size] = propietario;
    delete[] Lista;
    Lista = nuevaLista;
    size++;
}

void ListaDePropietarios::mostrar() const {
    for (int i = 0; i < size; i++){
        cout << i+1 <<". ";
        Lista[i].print();
    }
}


void ListaDePropietarios::leerPropietarios(){
    FILE* archivo = fopen("propietarios.txt", "r");
    if (archivo != NULL) {
        char nombre[128];
        char dni[9];
        char telefono[10];
        char contrasena[100];
        while(fscanf(archivo, "%[^\n]\n%s\n%s\n%s\n\n", nombre, dni, telefono, contrasena) == 4) {
            Propietario nuevoPropietario;
            nuevoPropietario.setNombre(nombre);
            nuevoPropietario.setDni(dni);
            nuevoPropietario.setTelefono(telefono);
            nuevoPropietario.setContrasena(contrasena);
            addPropietario(nuevoPropietario);
        }
        fclose(archivo);
    } else {
        cout << "No se pudo abrir el archivo propietarios" << endl;
    }
}

void ListaDePropietarios::guardarPropietarios() {
    FILE* archivo = fopen("propietarios.txt", "w");
    if (archivo != NULL) {
        for (int i = 0; i < size; i++) {
            Propietario& propietario = Lista[i];
            fprintf(archivo, "%s\n%s\n%s\n%s\n\n", propietario.getNombre(), propietario.getDni(), propietario.getTelefono(), propietario.getContrasena());
        }
        fclose(archivo);
    } else {
        cout << "No se pudo abrir 'propietarios.txt'" << endl;
    }
}

Propietario* ListaDePropietarios::verificar(char* dni, char* contrasena) {
    for (int i = 0; i < size; i++) {
        if (strcomp(Lista[i].getDni(),dni) && strcomp(Lista[i].getContrasena(),contrasena)) {
            return &Lista[i];
        }
    }
    return nullptr;
}

// -------------------------------------------------
// ----------  FUNCIONES DE TIPO CHAR  -------------
// -------------------------------------------------

int strlen(char* string) {
    int len = 0;
    while (string[len] != '\0') {
        len++;
    }
    return len;
}

void strcpy(char* destino, const char* original) {
    int i = 0;
    while (original[i] != '\0') {
        destino[i] = original[i];
        i++;
    }
    destino[i] = '\0';
}

bool strcomp(char* str1, char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (*str1 == *str2);
}

bool strcontains(const char* cadenaPrincipal, const char* subcadena) {
    while (*cadenaPrincipal) {
        const char* p1 = cadenaPrincipal; // recorre la cadena princial
        const char* p2 = subcadena; // recorre la subcadena
        while (*p1 && *p2 && *p1 == *p2) { // 
            p1++;
            p2++;
        }
        if (*p2 == '\0') { 
            return true;
        }
        cadenaPrincipal++;
    }
    return false;
}
