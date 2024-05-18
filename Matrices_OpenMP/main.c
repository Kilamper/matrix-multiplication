/*
===========================================================================
Nombre del proyecto:    Matrices_OpenMP
Autor:                  Kilian Armas Pérez
Titulación:             Ingeniería Informática
Asignatura:             Arquitectura de Computadores
Fecha:                  09/07/2023
Descripción:            Implementación del algoritmo de multiplicación de
                        matrices con números en coma flotante haciendo uso
                        de la librería de programación paralela OpenMP.
===========================================================================
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define M 1000          // Número de filas de la matriz A y número de filas de la matriz C
#define N 1000          // Número de columnas de la matriz A y número de filas de la matriz B
#define P 1000          // Número de columnas de la matriz B y número de columnas de la matriz C

double A[M][N];
double B[N][P];
double C[M][P];

void inicializar_matrices() {
    // Inicializar la matriz A con los valores de j
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (double) j;
        }
    }
    // Inicializar la matriz B con los valores de j
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            B[i][j] = (double) j;
        }
    }
    // Inicializar la matriz C a 0
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0.0;
        }
    }
}

void multiplicar_matrices(double A[][N], double B[][P], double C[][P]) {
    #pragma omp parallel for
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

void imprimir_matrices() {
    // Imprimir la matriz A
    printf("\nMatriz A (%d x %d):\n", M, N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%0.f ", A[i][j]);
        }
        printf("\n");
        if (M > 16 && i == 1) {
            printf(".....\n");
            break;
        }
    }
    // Imprimir la matriz B
    printf("\nMatriz B (%d x %d):\n", N, P);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            printf("%0.f ", B[i][j]);
        }
        printf("\n");
        if (N > 16 && i == 1) {
            printf(".....\n");
            break;
        }
    }
    // Imprimir la matriz resultado C
    printf("\nMatriz resultado C (%d x %d):\n", M, P);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%0.f ", C[i][j]);
        }
        printf("\n");
        if (M > 16 && i == 1) {
            printf(".....\n");
            break;
        }
    }
}

int main() {
    int threads = 20;

    puts("\nMatriz x Matriz Paralelo - OpenMP - BEGIN\n");

    double start = omp_get_wtime();

    inicializar_matrices();
    omp_set_num_threads(threads);
    multiplicar_matrices(A, B, C);

    double end = omp_get_wtime();
    int tiempo_transcurrido = (end - start) * 1000;

    imprimir_matrices();

    // Imprimir el tiempo de ejecución
    printf("\nTiempo de ejecucion: %d milisegundos\n", tiempo_transcurrido);

    puts("\nMatriz x Matriz Paralelo - OpenMP - FINISH");

    return 0;
}
