# Trabajo Práctico 3
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

## Implementación en un multicomputador usando OpenMPI y evaluación de prestaciones

Debido a la falta de interés y de gente para mantenerlo, se suspendió el soporte de OpenMPI en Windows. Por eso, en vez de usar OpenMPI, se ha hecho uso de la librería MS-MPI para realizar la implementación de la multiplicación de matrices en un multicomputador. Microsoft MPI (MS-MPI) es una implementación de Microsoft del estándar de interfaz de paso de mensajes para desarrollar y ejecutar aplicaciones paralelas en la plataforma Windows. Al igual que para OpenMP se ha elegido CodeBlocks como el entorno de desarrollo principal. Aunque el programa debe ser ejecutado desde línea de comandos para poder compartir el trabajo con otro computador.

**Configuración del entorno:** Para poder utilizar la librería MS-MPI en el entorno de desarrollo de CodeBlocks, lo primero es descargar tanto la interfaz MS-MPI (Microsoft Message Passing Interface) desde la página oficial de Microsoft como MinGW y, a continuación, realizar los siguientes ajustes en CodeBlocks para su correcto funcionamiento.

1. Entrar a “Settings”, “Compiler”, en “Selected Compiler”, seleccionar GNU GCC Compiler y en “Linker settings”, “Linker libraries”, añadir los siguientes archivos contenidos en el directorio Lib:

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/695d0fe2-d4d5-4379-9dbd-2e6c6e862bd4)

2. En “Search directories”, “Compiler”, añadir el directorio Include:

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/1671e62a-cbc0-4119-afb2-50925c797a56)

3. Y por último en “Toolchain executables”, “Compiler’s installation directory”, seleccionar el directorio en el que se encuentra MinGW.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/e3f5bef0-5327-4517-b51c-9258b3e8c3cf)

Al haber terminado los pasos anteriores, el entorno del CodeBlocks debería estar listo para el desarrollo del programa de multiplicación de matrices paralelo con MS-MPI. Para la ejecución en multicomputador se han usado dos ordenadores, uno de sobremesa y otro portátil. El primero es el mismo que se usó en la ejecución del programa paralelo creado con OpenMP, por lo que su procesador es el anteriormente nombrado Intel Core i5 13500, en cambio, el procesador del segundo ordenador, el portátil, es un Intel Core i7 10510U que posee 4 cores y 8 threads.

Los resultados de la evaluación de prestaciones no están disponibles debido a la imposibilidad de ejecutar dicho código en paralelo en ambos computadores. Durante los numerosos intentos de solucionar los problemas hallados a la hora de la ejecución desde el cmd de Windows se han probado distintas configuraciones y arreglos que han ido solucionando algunos de los errores encontrados. Pero el error “mpiexec is unable to connect the smpd service on computer_IP” se ha mantenido y ha sido lo que finalmente ha impedido la finalización de este apartado.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/f4aaf7fe-6ab2-4f87-a1d5-c227db95e26c)

Al igual que en el programa de OpenMP, la función “inicializar_matrices()” se encarga de inicializar las matrices A y B con los valores de las columnas correspondientes, y la matriz C a 0.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/87fb4f0f-5fef-4089-a169-e9d3a399387c)

La función “multiplicar_matrices(A, B, C, rows)” multiplica las matrices A y B, y almacena el resultado en C. Para paralelizar el cálculo se ha utilizado la variable rows para seleccionar el intervalo de filas que le pertenecen a cada proceso.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/891a71bc-3221-4e02-b774-38cc067c516e)

La función “imprimir_matrices()” se encarga de imprimir los elementos de las matrices A, B y C. Al igual que en el caso anterior, se ha incluido una condición para no imprimir matrices muy grandes.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/3a70761b-8884-4557-9c8f-46000e5c0302)

El programa principal “main(argc, argv)” se encarga de controlar la parelización de la multiplicación mediante las funciones de la librerío MS-MPI y de realizar un conteo del tiempo transcurrido entre el inicio y el final de la ejecución de la operación.

## Implementación en un coprocesador de tipo GPU usando CUDA y evaluación de prestaciones

CUDA es una plataforma de computación paralela que permite aprovechar el paralelismo masivo de las GPUs. Para la implementación de la multiplicación de matrices en un coprocesador de tipo GPU se ha optado por no utilizar nuevamente el entorno de desarrollo de CodeBlocks, sino el de Visual Studio, por su fácil implementación con el compilador y la librería CUDA.

**Configuración:** Para poder empezar a trabajar con CUDA, lo primero que hace falta es descargar CUDA Toolkit y los controladores de CUDA compatibles con la tarjeta gráfica que se vaya a utilizar. A diferencia de CodeBlocks, en Visual Studio no hace falta hacer ningún ajuste en especial, ya que al descargar CUDA se configura en el entorno automáticamente.

1. Al crear un nuevo proyecto, bajar hasta ver la opción “CUDA X.X Runtime”, seleccionarla y pulsar en siguiente.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/6bf64e50-d76f-48cd-8ee2-4e48d52ddeab)

Después de terminar de crear el proyecto, ya está todo preparado para comenzar a trabajar con CUDA. El PC utilizado para la implementación en un coprocesador GPU de la multiplicación de matrices es el mismo utilizado para OpenMP, cuya tarjeta gráfica es una Nvidia RTX 3060 que posee 3584 núcleos CUDA.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/8a2b114d-6ff7-4511-a2ec-41ac869c8a6b)

La tabla anterior representa la comparación entre la ejecución secuencial del programa de multiplicación de matrices frente a la ejecución paralalela utilizando la GPU como coprocesador. Como se puede observar, la diferencia es muy amplia entre ambas, con tiempos que pasan de los 94206 milisegundos en matrices de 3000 x 3000 elementos a unos increíbles 0,0623 milisegundos. Esto nos deja unos descomunales valores del Speed-Up, de entre 72800X y 1512000X.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/3c2087ad-1fbc-4b26-b1ab-b53d3987202f)

Al igual que en los dos casos anteriores, la función “multiplicar_matrices(a, b, c, N, M, P)” se encarga de completar la multiplicación de las matrices A y B, y de almacenar su resultado en C. Se utilizan las variables “row” y “col” para determinar la posición actual dentro de la matriz.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/ddab7eaf-580c-4245-8ac6-adc7dd9660e3)
![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/a642ab6a-0f64-451e-9887-5514d6bc3bc4)
![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/77cffb2a-7087-48c9-9112-77306c0794ad)

En el programa principal “main()” se inicializan las matrices A y B con los valores de las columnas correspondientes, se reparte la ejecución de la operación de multiplicación con el coprocesador de tipo GPU, se imprimen las matrices A, B y C, y se realiza un conteo del tiempo transcurrido entre el inicio y el final de la multiplicación de las matrices.

## Comparación de prestaciones entre multiprocesadores, multicomputadores y GPUs

Al no haber podido obtener los resultados de la ejecución en multicomputadores, solo se realizará la comparación de prestaciones entre la implementación en un mutiprocesador y en un coprocesador de tipo GPU.

![image](https://github.com/Kilamper/matrix-multiplication/assets/73082382/fd6d0322-122e-4eee-860b-4c7f187deaca)

Aunque al utilizar todos los hilos disponibles en el programa desarrollado con OpenMP, el tiempo de ejecución mejora considerablemente, este resultado no se acerca al proporcionado por CUDA. Además, como se puede observar el Speed-Up entre la paralelización usando la GPU frente a la paralelización mediante multiples procesadores es muy grande, estando entre 8110X (en el caso de matrices 1000 x 1000) y 127290X (en matrices 3000 x 3000). Esto se debe a que la GPU posee un número de núcleos ampliamente superior al número de núcleos localizados dentro del procesador.
