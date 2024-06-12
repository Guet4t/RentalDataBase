#include "Hotel.hpp"

Inmueble::Inmueble() {
    direccion = new char[1];
    direccion[0] = '\0';
    numCuartos = -1;
    precio = -1;
}

Inmueble::Inmueble(const Inmueble& original) {
    direccion = new char[strlen(original.getDireccion()) + 1];
    strcpy(direccion, original.getDireccion());
    numCuartos = original.getNumCuartos();
    precio = original.getPrecio();
}

Inmueble& Inmueble::operator=(const Inmueble& original) {
    if (this != &original) {
        delete[] direccion;
        direccion = new char[strlen(original.getDireccion()) + 1];
        strcpy(direccion, original.getDireccion());
        numCuartos = original.getNumCuartos();
        precio = original.getPrecio();
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

void Inmueble::print() const {
    cout << "Direccion: " << direccion;
    cout << ", Numero de cuartos: " << numCuartos;
    cout << ", Precio: " << precio;
    cout << endl;
}

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
        while (fscanf(archivo, "%[^\n]\n%d\n%f\n\n", direccion, &numCuartos, &precio) == 3) {
            Inmueble nuevoInmueble;
            nuevoInmueble.setDireccion(direccion);
            nuevoInmueble.setNumCuartos(numCuartos);
            nuevoInmueble.setPrecio(precio);
            addInmueble(nuevoInmueble);
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

void ListaDeInmuebles::mostrar() const {
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        Lista[i].print();
    }
}

Cliente::Cliente() {
    nombre = new char[1];
    nombre[0] = '\0';
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

Propietario::Propietario() {
    nombre = new char [1];
    nombre[0] = '\0';
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
}

Propietario& Propietario::operator=(Propietario &original) {
    if (this != &original) {
        delete[] nombre;
        nombre = new char[strlen(original.getNombre()) + 1];
        strcpy(nombre, original.getNombre());
        strcpy(dni, original.getDni());
        strcpy(telefono, original.getTelefono());
    }
    return *this;
}

Propietario::~Propietario() {
    delete[] nombre;
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

void Propietario::print() const {
    cout << "Nombre: " << nombre << endl;
    cout << "DNI: " << dni << endl;
    cout << "Telefono: " << telefono << endl;
}

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
