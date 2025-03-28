// insertion_sort.cpp
#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// bubble_sort.cpp
#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// selection_sort.cpp
#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// merge_sort.cpp
#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// quick_sort.cpp
#include <iostream>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// heap_sort.cpp
#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// shell_sort.cpp
#include <iostream>
using namespace std;

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
using namespace std;

// Declaraciones de los algoritmos
void insertionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void mergeSort(int arr[], int left, int right);
void quickSort(int arr[], int low, int high);
void heapSort(int arr[], int n);
void shellSort(int arr[], int n);

const int NUM_PRUEBAS = 1000;
const int TAM_ARREGLO = 100;

void medirTiempo(void (*sortFunction)(int[], int), const string &nombreArchivo) {
    vector<double> tiemposEjecucion(NUM_PRUEBAS);
    srand(time(0));

    for (int prueba = 0; prueba < NUM_PRUEBAS; prueba++) {
        int arreglo[TAM_ARREGLO];
        for (int i = 0; i < TAM_ARREGLO; i++) {
            arreglo[i] = rand() % 1000 + 1;
        }

        auto inicio = chrono::high_resolution_clock::now();
        sortFunction(arreglo, TAM_ARREGLO);
        auto fin = chrono::high_resolution_clock::now();

        double tiempo = chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count();
        tiemposEjecucion[prueba] = tiempo;
        cout << "Tiempo de ejecución: " << tiempo << " nanosegundos" << endl;
    }

    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (double tiempo : tiemposEjecucion) {
            archivo << tiempo << endl;
        }
        archivo.close();
        cout << "Resultados guardados en " << nombreArchivo << endl;
    } else {
        cout << "Error al abrir el archivo para guardar los resultados." << endl;
    }
}

int main() {
    medirTiempo(insertionSort, "insertion_sort.csv");
    medirTiempo(bubbleSort, "bubble_sort.csv");
    medirTiempo(selectionSort, "selection_sort.csv");
    medirTiempo(heapSort, "heap_sort.csv");

    return 0;
}