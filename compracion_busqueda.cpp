//COMPARACION DE ALGORITMOS DE BUSQUEDA
#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

int busquedaSecuencial(int[], int, int);
int busquedaBinaria(int[], int, int);
void ordenar(int[], int);
int nuevosDatos(int[]);
void copia(int[], int[], int);

void realizarBusquedasAleatorias(int a[], int n, int tipoBusqueda, int numBusquedas);

int main() {
    int n = 0, op, dato, pos;
    const long long MAX_SIZE = 1000000000;
    int* a = new int[MAX_SIZE];
    int* b = new int[MAX_SIZE];
    srand(static_cast<unsigned int>(time(0)));

    do {
        cout << "Ingrese cuantos datos desea (max " << MAX_SIZE << "): ";
        cin >> n;
        if (n < 1 || n > MAX_SIZE) {
            cout << "Por favor, ingrese un número entre 1 y " << MAX_SIZE << ": ";
        }
    } while (n < 1 || n > MAX_SIZE);

    for (int i = 0; i < n; i++) {
        a[i] = 1 + i;
    }

    do {
        cout << "=== COMPARACION DE METODOS DE BUSQUEDA ===\n\n";
        cout << "1. Busqueda Secuencial\n";
        cout << "2. Busqueda Binaria\n";
        cout << "3. Elija la cantidad de datos\n";
        cout << "4. Realizar N busquedas aleatorias\n\n";
        cout << "5. SALIR\n";
        cout << "Escoja el metodo de busqueda: ";
        cin >> op;

        switch (op) {
            case 1:
                copia(a, b, n);
                cout << "Ingrese el dato a buscar: ";
                cin >> dato;
                {
                    auto inicio = high_resolution_clock::now();  // Iniciar cronómetro
                    pos = busquedaSecuencial(b, n, dato);
                    auto fin = high_resolution_clock::now();  // Finalizar cronómetro
                    duration<double> duracion = fin - inicio;  // Calcular duración

                    if (pos != -1) {
                        cout << "Dato encontrado en la posicion " << pos << ".\n";
                    } else {
                        cout << "Dato no encontrado.\n";
                    }
                    cout << "La busqueda tardo " << duracion.count() << " segundos en ejecutarse.\n";
                }
                break;
            case 2:
                copia(a, b, n);
                ordenar(b, n);
                cout << "Ingrese el dato a buscar: ";
                cin >> dato;
                {
                    auto inicio = high_resolution_clock::now();  // Iniciar cronómetro
                    pos = busquedaBinaria(b, n, dato);
                    auto fin = high_resolution_clock::now();  // Finalizar cronómetro
                    duration<double> duracion = fin - inicio;  // Calcular duración

                    if (pos != -1) {
                        cout << "Dato encontrado en la posicion " << pos << ".\n";
                    } else {
                        cout << "Dato no encontrado.\n";
                    }
                    cout << "La busqueda tardo " << duracion.count() << " segundos en ejecutarse.\n";
                }
                break;
            case 3:
                n = nuevosDatos(a);
                break;
            case 4:
                int tipoBusqueda, numBusquedas;
                cout << "Seleccione el tipo de busqueda: \n1. Secuencial\n2. Binaria\n";
                cin >> tipoBusqueda;
                cout << "Ingrese el numero de busquedas aleatorias: ";
                cin >> numBusquedas;
                realizarBusquedasAleatorias(a, n, tipoBusqueda, numBusquedas);
                break;
                
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            
            default:
                cout << "Elija una opcion valida\n";
                break;
        }
        system("pause");
    } while (op != 5);

    delete[] a;
    delete[] b;

    return 0;
}

int busquedaSecuencial(int A[], int n, int dato) {
    for (int i = 0; i < n; ++i) {
        if (A[i] == dato) {
            return i;
        }
    }
    return -1;
}

int busquedaBinaria(int a[], int n, int dato) {
    int izq = 0, der = n - 1;
    while (izq <= der) {
        int m = (izq + der) / 2;
        if (a[m] == dato) {
            return m;
        } else if (dato > a[m]) {
            izq = m + 1;
        } else {
            der = m - 1;
        }
    }
    return -1;
}

void ordenar(int a[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

int nuevosDatos(int a[]) {
    int m;
    cout << "Ingrese cuantos datos desea: ";
    cin >> m;
    while (m < 1 || m > 1000000000) {
        cout << "Por favor, ingrese un número entre 1 y 1000000000: ";
        cin >> m;
    }
    for (int i = 0; i < m; i++) {
        a[i] = rand() % 100000 + 1;
    }
    return m;
}

void copia(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

void realizarBusquedasAleatorias(int a[], int n, int tipoBusqueda, int numBusquedas) {
    int pos;
    double tiempoTotal = 0.0;  // Acumular el tiempo total de las búsquedas
    
    for (int i = 0; i < numBusquedas; ++i) {
        int datoAleatorio = rand() % n + 1;  // Genera un dato aleatorio
        
        // Iniciar cronómetro antes de realizar la búsqueda
        auto inicio = high_resolution_clock::now(); 
        
        // Realizar la búsqueda según el tipo seleccionado
        if (tipoBusqueda == 1) {
            pos = busquedaSecuencial(a, n, datoAleatorio);
        } else {
            pos = busquedaBinaria(a, n, datoAleatorio);
        }
        
        // Detener cronómetro después de realizar la búsqueda
        auto fin = high_resolution_clock::now();  
        
        // Calcular la duración de la búsqueda y acumularla
        duration<double> duracion = fin - inicio;  
        tiempoTotal += duracion.count();  
    }
    
    // Calcular el tiempo promedio en segundos
    double promedioTiempo = tiempoTotal * 1000/ numBusquedas;  
    
    // Imprimir el tiempo promedio en segundos
    cout << "\nEl tiempo promedio de las " << numBusquedas << " busquedas fue de " << promedioTiempo << " segundos.\n";
}
