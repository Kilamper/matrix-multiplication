# Trabajo Práctica 3
## Programación paralela de la multiplicación de matrices

Este trabajo práctico se centra en la programación paralela de la multiplicación de matrices utilizando diferentes tecnologías paralelas, como OpenMP, OpenMPI y CUDA. El objetivo principal del trabajo es implementar el algoritmo de multiplicación de matrices con números en coma flotante en las librerías paralelas mencionadas, aprovechando la capacidad de paralelismo de un ordenador de sobremesa.

## Implementación en un multiprocesador usando OpenMP y evaluación de prestaciones

OpenMP permite la programación paralela en sistemas multiprocesador de memoria compartida. Para este trabajo, se ha utilizado el entorno de desarrollo integrado CodeBlocks, que proporciona una interfaz amigable y herramientas de compilación para desarrollar y ejecutar programas en C/C++.

**Configuración del entorno:** Para poder hacer uso de la librería OpenMP en CodeBlocks, ha sido necesario descargar MinGW (la implementación de los compiladores GCC para Windows) y realizar los siguientes ajustes en el entorno.

1. Entrar a “Settings”, “Compiler”, en “Selected compiler”, seleccionar GNU GCC Compiler y en “Compiler settings”, “Other compiler options”, escribir la opción -fopenmp.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/539179da-7cf7-4327-add5-2e576756be27)

2. En “Linker settings”, “Other linker options”, escribir las opciones -lgomp y -pthread.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/ab7736e3-d8ff-4a14-bdd1-6aa5e90d3663)

3. Y por último en “Toolchain executables”, “Compiler’s installation directory”, seleccionar el directorio en el que se encuentra MinGW.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/aa5edc0a-ab6a-4c31-b886-668482e78587)

Después de haber completado estos pasos, el entorno ya está preparado para ejecutar la multiplicación de matrices de forma paralela, lo único que haría falta sería importar la librería OpenMP (#include <omp.h>). Por lo que ya se puede comenzar con la evaluación de prestaciones mediante el uso de los contadores hardware proporcionados por OpenMP. El PC utilizado para la ejecución del programa tiene de procesador un Intel Core i5 13500 de 6 núcleos P-Core (Performance Core) y 8 núcleos E-Core (Efficient Core), que en total conforman 14 núcleos y 20 hilos.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/9e7cc5d0-2f67-46a4-aba5-c02e014953a6)

La tabla anterior muestro los resultados obtenidos de la ejecución del programa de multiplicación de matrices usando tres tamaños distintos de matrices (1000 x 1000, 2000 x 2000 y 3000 x 3000) y alternando el número de hilos empleados en el cálculo del resultado. En esta tabla también se pueden observar el Speed-Up de cada una de las ejecuciones paralelas con respecto a la ejecución secuencial inicial, así como la eficiencia del paralelismo (100% * Speed-Up/Nº hilos).

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/99f63748-8f8c-4cfe-8508-839c611c6081)

Como se puede ver, al ir cambiando el tamaño de las matrices de 1000 x 1000 a 2000 x 2000 y a 3000 x 3000, se observa un vertiginozo aumento del tiempo total. En cambio, al aumentar el número de hilos, el tiempo total disminuye de manera considerable, por lo que el tiempo de ejecución es inversamente proporcional al número de hilos y directamente proporcional al tamaño de las matrices. Esto se ve reflejado en que si duplicamos el número de hilos de 1 a 2 o de 8 a 16, el tiempo de ejecución total resulta ser aproximadamente la mitad, pasando de 1975 ms a 1054 y de 377 ms a 250, respectivamente, tanto en el caso de usar matrices de tamaño 1000 x 1000 como en este ejemplo, como al usar matrices de otras dimensiones.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/bdaf81c2-f562-4637-9ca0-85edb1973c2f)

La función “inicializar_matrices()” inicializa las matrices A y B con el valor de la columna a la que pertenece cada uno de sus elementos y la matriz resultado C con todos sus elementos a 0.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/878f585b-4970-4b1b-a795-4e85b4094e7a)

La función “multiplicar_matrices(A, B, C)” se encarga de multiplicar las matrices A y B y guardar el resultado en la matriz C. Se utiliza la sentencia #pragma omp parallel for para paralelizar el bucle que realiza la operación y dividirlo entre el número de hilos seleccionado para la ejecución.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/23f6a9ef-b61c-48e4-967d-42b5f9601485)

El propósito de la función “imprimir_matrices()” es el de imprimir las matrices A y B, y la matriz resultado C. Se ha implementado una condición para imprimir solo las dos primeras filas de las matrices cuando el tamaño de estas es muy grande.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/48ac1730-69e3-4edf-96f2-a3cbbd27084d)

En el programa principal, “main()”, se selecciona el número de hilos deseado por medio de la variable “threads” y la función “omp_set_num_threads()”. Además, a partir de un contador hardware perteneciente a la librería OpenMP se realiza un conteo del tiempo de ejecución de la operación.

## Integración con la API

La aplicación utiliza una API sencilla y ligera conocida como Fixer para obtener tasas de cambio precisas entre 170 divisas de todo el mundo, actualizadas cada 60 segundos y con datos históricos desde 1999.
