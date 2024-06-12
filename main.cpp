#include <iostream>
#include "Hotel.hpp"
using namespace std;

void menuCliente(ListaDeInmuebles& TodosInmuebles);
void menuPropietario(ListaDeInmuebles& TodosInmuebles);
void guardarInmuebles(ListaDeInmuebles& inmuebles);

int main() {   
    ListaDeInmuebles TodosInmuebles(0);
    TodosInmuebles.leerInmuebles();
    ListaDePropietarios TodosPropietarios(0);
    int opcion = 0;
    
    while (opcion != 3) {
        cout << "\n----Menu Principal----\n";
        cout << "1. Cliente" << endl;
        cout << "2. Propietario" << endl;
        cout << "3. Salir" << endl;
        cout << "Como desea ingresar? ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                menuCliente(TodosInmuebles);
                break;
            case 2:
                menuPropietario(TodosInmuebles);
                break;
            case 3:
                cout << "Saliendo ..." << endl;
                break;
            default: 
                cout << "Opcion no valida. Intente de nuevo" << endl;
        }
    }
    
    guardarInmuebles(TodosInmuebles);
    return 0;
}

void menuCliente(ListaDeInmuebles& TodosInmuebles) {
    int op = 0;

    while (op != 5) { 
        cout << "\n---- Menu del Cliente ----" << endl;
        cout << "1. Ver todos los inmuebles" << endl;
        cout << "2. Buscar por direccion" << endl;
        cout << "3. Buscar por numero de cuartos" << endl;
        cout << "4. Buscar por precio" << endl;
        cout << "5. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> op;

        switch(op) {
            case 1:
                cout << "\nLista de Inmuebles\n";
                TodosInmuebles.mostrar();
                break;
            case 2: {
                char direccion[128];
                cout << "Ingrese la direccion a buscar: ";
                cin.ignore();
                cin.getline(direccion, 128);

                ListaDeInmuebles resultado = TodosInmuebles.buscarPorDireccion(direccion);
                cout << "Resultados de la busqueda: " << endl;
                resultado.mostrar();
                break;
            }
            case 3: {
                int minCuartos = -1;
                int maxCuartos = -1;
                cout << "Ingrese el numero minimo de cuartos (o -1 para ignorar): ";
                cin >> minCuartos;
                cout << "Ingrese el numero maximo de cuartos (o -1 para ignorar): ";
                cin >> maxCuartos;

                ListaDeInmuebles resultado = TodosInmuebles.buscarPorNumCuartos(minCuartos, maxCuartos);
                cout << "\nResultado de la busqueda: \n";
                resultado.mostrar();
                break;
            }
            case 4: {
                float precioMin = -1;
                float precioMax = -1;
                cout << "Ingrese el precio minimo (o -1 para ignorar): ";
                cin >> precioMin;
                cout << "Ingrese el precio maximo (o -1 para ignorar): ";
                cin >> precioMax;
                ListaDeInmuebles resultado = TodosInmuebles.buscarPorPrecio(precioMin, precioMax);
                cout << "\nResultado de la busqueda:\n";
                resultado.mostrar();
                break;
            }
            case 5:
                cout << "Saliendo ..." << endl;
                break;
            default: 
                cout << "opcion no valida";
        }
    }
}

void menuPropietario(ListaDeInmuebles& TodosInmuebles) {
    ListaDeInmuebles misInmuebles(0);
    int op = 0;
    
    while (op != 5){
        cout << "\n---- Menu del Propietario ----" << endl;
        cout << "1. Agregar inmuebles" << endl;
        cout << "2. Modificar inmueble" << endl;
        cout << "3. Eliminar inmueble" << endl;
        cout << "4. Mostrar mis inmuebles" << endl;
        cout << "5. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> op;

        switch(op) {
            case 1: {
                int numInmuebles = 0;
                cout << "Inmuebles a ingresar: ";
                cin >> numInmuebles;
                for (int i = 0; i < numInmuebles; i++) {
                    char direccion[100];
                    int numCuartos;
                    float precio;
                    cout << "Ingrese la direccion del inmueble: ";
                    cin.ignore();
                    cin.getline(direccion, 100);
                    cout << "Ingrese el numero de cuartos: ";
                    cin >> numCuartos;
                    cout << "Ingrese el precio del inmueble: ";
                    cin >> precio;

                    Inmueble nuevoInmueble;
                    nuevoInmueble.setDireccion(direccion);
                    nuevoInmueble.setNumCuartos(numCuartos);
                    nuevoInmueble.setPrecio(precio);

                    misInmuebles.addInmueble(nuevoInmueble);
                    TodosInmuebles.addInmueble(nuevoInmueble);
                }
                break;
            }
            case 2:
                cout << "Opcion 2";
                break;
            case 3:
                cout << "Opcion 3";
                break;
            case 4:
                cout << "\nMis inmuebles: " << endl; 
                misInmuebles.mostrar();
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Default";
        }
    }
}

void guardarInmuebles(ListaDeInmuebles& inmuebles) {
    FILE* archivo = fopen("inmuebles.txt","w");

    if (archivo != NULL) {
        for (int i = 0; i < inmuebles.getSize(); i++) {
            Inmueble& inmueble = inmuebles.getInmueble(i);
            fprintf(archivo, "%s\n%d\n%f\n\n", inmueble.getDireccion(), inmueble.getNumCuartos(), inmueble.getPrecio());
        }

        fclose(archivo);
    } else {
        cout << "No se pudo abrir 'inmuebles.txt'" << endl;
    }
}