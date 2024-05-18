/*
===========================================================================
Nombre del proyecto:    Matrices_CUDA
Autor:                  Kilian Armas Pérez
Titulación:             Ingeniería Informática
Asignatura:             Arquitectura de Computadores
Fecha:                  09/07/2023
Descripción:            Implementación del algoritmo de multiplicación de
                        matrices con números en coma flotante haciendo uso
                        de la librería de programación paralela CUDA.
===========================================================================
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <cstdlib>
#include <chrono>

// Kernel de multiplicación de matrices en CUDA
__global__ void multiplicar_matrices(double* a, double* b, double* c, int N, int M, int P) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < P) {
        double value = 0.0;
        for (int k = 0; k < M; ++k) {
            value += a[row * M + k] * b[k * P + col];
        }
        c[row * P + col] = value;
    }
}

int main() {
    const int N = 3000; // Filas de la matriz A y C
    const int M = 3000; // Columnas de la matriz A y filas de la matriz B
    const int P = 3000; // Columnas de la matriz B y C

    puts("\nMatriz x Matriz Paralelo - CUDA - BEGIN\n");

    // Definir las matrices de entrada y salida
    double* a = new double[N * M];
    double* b = new double[M * P];
    double* c = new double[N * P];

    // Inicializar las matrices de entrada
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i * M + j] = static_cast<double>(j);
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            b[i * P + j] = static_cast<double>(j);
        }
    }

    // Declarar punteros de dispositivo CUDA
    double* dev_a;
    double* dev_b;
    double* dev_c;

    // Iniciar el contador de tiempo
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    // Alojar memoria en el dispositivo CUDA
    cudaMalloc((void**)&dev_a, N * M * sizeof(double));
    cudaMalloc((void**)&dev_b, M * P * sizeof(double));
    cudaMalloc((void**)&dev_c, N * P * sizeof(double));

    // Copiar los datos de las matrices de entrada al dispositivo CUDA
    cudaMemcpy(dev_a, a, N * M * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, M * P * sizeof(double), cudaMemcpyHostToDevice);

    // Configurar la cuadrícula y el bloque de hilos para la ejecución del kernel
    dim3 blockSize(16, 16);
    dim3 gridSize((P + blockSize.x - 1) / blockSize.x, (N + blockSize.y - 1) / blockSize.y);

    // Ejecutar el kernel de multiplicación de matrices en CUDA
    multiplicar_matrices<<<gridSize, blockSize>>>(dev_a, dev_b, dev_c, N, M, P);

    // Copiar el resultado de vuelta desde el dispositivo CUDA a la memoria del host
    cudaMemcpy(c, dev_c, N * P * sizeof(double), cudaMemcpyDeviceToHost);

    // Detener el contador de tiempo y calcular la duración
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    // Imprimir las matrices y el resultado
    std::cout << "Matriz A (" << N << " x " << M << "):" << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cout << a[i * M + j] << " ";
        }
        std::cout << std::endl;
        if (N > 16 && i == 1) {
            std::cout << "..." << std::endl;
            break;
        }
    }

    std::cout << std::endl << "Matriz B(" << M << " x " << P << "):" << std::endl;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < P; ++j) {
            std::cout << b[i * P + j] << " ";
        }
        std::cout << std::endl;
        if (M > 16 && i == 1) {
            std::cout << "..." << std::endl;
            break;
        }
    }

    std::cout << std::endl << "Matriz Resultado C (" << N << " x " << P << "):" << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < P; ++j) {
            std::cout << c[i * P + j] << " ";
        }
        std::cout << std::endl;
        if (M > 16 && i == 1) {
            std::cout << "..." << std::endl;
            break;
        }
    }
    std::cout << std::endl << "Tiempo de ejecucion: " << duration.count() * 1000 << " milisegundos" << std::endl;

    puts("\nMatriz x Matriz Paralelo - CUDA - FINISH\n");

    // Liberar memoria en el dispositivo CUDA
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

    // Liberar memoria en el host
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}