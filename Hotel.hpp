#ifndef HOTEL_HPP
#define HOTEL_HPP
#include <iostream>

using namespace std;

int strlen(char* string);
void strcpy(char* destino, const char* original);
bool strcomp(char* str1, char* str2);
bool strcontains(const char* cadenaPrincipal, const char* subcadena);

class Inmueble {
public:
    Inmueble();
    Inmueble(Inmueble& original);
    Inmueble& operator=(Inmueble& original);
    ~Inmueble();
    char* getDireccion() const;
    int getNumCuartos() const;
    float getPrecio() const;
    void setNumCuartos(int cuartos);
    void setPrecio(float precio);
    void setDireccion(char* direccion);
    void print() const;

    char* getDniPropietario();
    void setDniPropietario (char* dni);

private: 
    char* direccion;
    int numCuartos;
    float precio;
    char dniPropietario[9];
    
    friend int strlen(char* string);
    friend void strcpy(char* destino, const char* original);
};

class ListaDeInmuebles {
public:
    ListaDeInmuebles(int size);
    ListaDeInmuebles& operator=(const ListaDeInmuebles& other);
    ~ListaDeInmuebles();
    int getSize();
    Inmueble& getInmueble(int index);
    void addInmueble(Inmueble& inmueble);
    void eliminarInmueble(int index);
    ListaDeInmuebles buscarPorDireccion(char* direccion);
    ListaDeInmuebles buscarPorPrecio(float precioMin, float precioMax);
    ListaDeInmuebles buscarPorNumCuartos(int min, int max);
    void mostrar() const;
    
    void leerInmuebles();
    void guardarInmuebles();

   ListaDeInmuebles filtrarPorPropietario(char* dniPropietario);

    friend bool strcomp(char* str1, char* str2);
    friend bool strcontains(const char* cadenaPrincipal, const char* subcadena);

private:
    int size; 
    Inmueble* Lista;
};

class Cliente {
public: 
    Cliente();
    Cliente(Cliente &original);
    Cliente& operator=(Cliente &original);
    ~Cliente();
    char* getNombre() const;
    char* getDni();
    char* getTelefono();
    void setNombre(char* nombre);
    void setDni(char* dni);
    void setTelefono(char* telefono);
    void print() const;

private: 
    char* nombre;
    char dni[9];
    char telefono[10];

    friend int strlen(char* string);
    friend void strcpy(char* destino, const char* original);
};

class ListaDeClientes {
public:
    ListaDeClientes(int size);
    ListaDeClientes(ListaDeClientes& other);
    ListaDeClientes& operator=(const ListaDeClientes& other);
    ~ListaDeClientes();
    int getSize();
    Cliente& getCliente(int index);
    void addCliente (Cliente& cliente);
    ListaDeClientes buscarPorNombre(char* nombre);
    ListaDeClientes buscarPorDni(char* dni);
    ListaDeClientes buscarPorTelefono(char* telefono);
    void mostrar() const;


private:
    int size;
    Cliente *Lista;
    
    friend bool strcomp(char* str1, char* str2);
    friend bool strcontains(const char* cadenaPrincipal, const char* subcadena);
};

class Propietario {
public: 
    Propietario();
    Propietario(Propietario &original);
    Propietario& operator=(Propietario &original);
    ~Propietario();
    char* getNombre () const;
    char* getDni();
    char* getTelefono();
    void setNombre(char* nombre);
    void setDni(char* dni);
    void setTelefono(char* telefono);
    void print() const;
    char* getContrasena();
    void setContrasena(char* contrasena);

private:
    char* nombre;
    char dni[9];
    char telefono[10];
    char* contrasena;

    friend int strlen(char* string);
    friend void strcpy(char* destino, const char* original);
};

class ListaDePropietarios {
public:
    ListaDePropietarios(int size);
    ListaDePropietarios(ListaDePropietarios& other);
    ListaDePropietarios& operator=(const ListaDePropietarios& other);
    ~ListaDePropietarios();
    int getSize();
    Propietario& getPropietario(int index);
    ListaDePropietarios buscarPorNombre(char* nombre);
    ListaDePropietarios buscarPorDni(char* dni);
    ListaDePropietarios buscarPorTelefono(char* telefono);
    void addPropietario (Propietario& propietario);
    void mostrar() const;

    void leerPropietarios();
    void guardarPropietarios();
    Propietario* verificar(char* dni, char* contrasena);
private:
    int size;
    Propietario *Lista;
    
    friend bool strcomp(char* str1, char* str2);
    friend bool strcontains(const char* cadenaPrincipal, const char* subcadena);
};

#endif 
