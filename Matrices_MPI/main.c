/*
===========================================================================
Nombre del proyecto:    Matrices_MPI
Autor:                  Kilian Armas Pérez
Titulación:             Ingeniería Informática
Asignatura:             Arquitectura de Computadores
Fecha:                  09/07/2023
Descripción:            Implementación del algoritmo de multiplicación de
                        matrices con números en coma flotante haciendo uso
                        de la librería de programación paralela MS-MPI.
===========================================================================
*/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define M 10          // Número de filas de la matriz A y número de filas de la matriz C
#define N 10          // Número de columnas de la matriz A y número de filas de la matriz B
#define P 10          // Número de columnas de la matriz B y número de columnas de la matriz C

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

void multiplicar_matrices(double local_A[][M], double B[][P], double local_C[][P], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < P; j++) {
            double sum = 0.0;
            for (int k = 0; k < M; k++) {
                sum += local_A[i][k] * B[k][j];
            }
            local_C[i][j] = sum;
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

int main(int argc, char** argv) {
    int num_processes, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) puts("\nMatriz x Matriz Paralelo - OpenMP - BEGIN");

    int rows_per_process = N / num_processes;
    int extra_rows = N % num_processes;
    double local_A[N][M], local_C[N][P];

    double start, end;
    int tiempo_transcurrido;

    if (rank == 0) {
        start = MPI_Wtime();
        inicializar_matrices();
    }

    MPI_Scatter(A, rows_per_process * M, MPI_DOUBLE, local_A, rows_per_process * M, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Bcast(B, N * P, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    multiplicar_matrices(local_A, B, local_C, rows_per_process + (rank < extra_rows ? 1 : 0));

    MPI_Gather(local_C, (rows_per_process + (rank < extra_rows ? 1 : 0)) * P, MPI_DOUBLE, C,
               (rows_per_process + (rank < extra_rows ? 1 : 0)) * P, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        end = MPI_Wtime();
        tiempo_transcurrido = (end - start) * 1000;
    }

    if (rank == 0) {
        imprimir_matrices();
        // Imprimir el tiempo de ejecución
        printf("\nTiempo de ejecucion: %d milisegundos\n", tiempo_transcurrido);
    }

    MPI_Finalize();

    if (rank == 0) puts("\nMatriz x Matriz Paralelo - OpenMP - FINISH");

    return 0;
}

