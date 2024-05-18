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

|Ejecución|Hilos|Dimensiones|Tiempo total (ms)|Speed-Up|Eficiencia Paralelismo|
|:----|:----|:----|:----|:----|:----|
| |1|1000 x 1000|1975|1|100%|
|Secuencial|1|2000 x 2000|20682|1|100%|
| |1|3000 x 3000|94206|1|100%|
| |2|1000 x 1000|1054|1,87|93,69%|
|Paralela (Multihilo)|2|2000 x 2000|10595|1,95|97,60%|
| |2|3000 x 3000|49318|1,91|95,51%|
| |4|1000 x 1000|574|3,44|86,02%|
|Paralela (Multihilo)|4|2000 x 2000|5649|3,66|91,53%|
| |4|3000 x 3000|25144|3,75|93,67%|
| |8|1000 x 1000|377|5,24|65,48%|
|Paralela (Multihilo)|8|2000 x 2000|3489|5,93|74,10%|
| |8|3000 x 3000|14852|6,34|79,29%|
| |16|1000 x 1000|250|7,9|49,38%|
|Paralela (Multihilo)|16|2000 x 2000|2340|8,84|55,24%|
| |16|3000 x 3000|9134|10,31|64,46%|
| |20|1000 x 1000|220|8,98|44,89%|
|Paralela (Multihilo)|20|2000 x 2000|2052|10,08|50,39%|
| |20|3000 x 3000|7930|11,88|59,40%|


+ **Interfaz Gráfica Intuitiva**: Diseño amigable que facilita la navegación y el uso de la aplicación, presentando un teclado numérico muy sencillo para que cualquier persona pueda utilizarlo.

## Integración con la API

La aplicación utiliza una API sencilla y ligera conocida como Fixer para obtener tasas de cambio precisas entre 170 divisas de todo el mundo, actualizadas cada 60 segundos y con datos históricos desde 1999.
