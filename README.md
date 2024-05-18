# Trabajo Práctica 3
## Programación paralela de la multiplicación de matrices

Este trabajo práctico se centra en la programación paralela de la multiplicación de matrices utilizando diferentes tecnologías paralelas, como OpenMP, OpenMPI y CUDA. El objetivo principal del trabajo es implementar el algoritmo de multiplicación de matrices con números en coma flotante en las librerías paralelas mencionadas, aprovechando la capacidad de paralelismo de un ordenador de sobremesa.

## Implementación en un multiprocesador usando OpenMP y evaluación de prestaciones

OpenMP permite la programación paralela en sistemas multiprocesador de memoria compartida. Para este trabajo, se ha utilizado el entorno de desarrollo integrado CodeBlocks, que proporciona una interfaz amigable y herramientas de compilación para desarrollar y ejecutar programas en C/C++.
## Características

- **Conversión de Divisas:** Permite a los usuarios ingresar una cantidad, seleccionar las divisas de origen y destino, y calcular la conversión utilizando las tasas de cambio actuales o pasadas.

* **Selección de Fecha**: La aplicación permite a los usuarios seleccionar una fecha específica para comprobar tasas de cambio históricas. Esto ha sido implementado mediante la utilización de la librería externa "JCalendar".

+ **Interfaz Gráfica Intuitiva**: Diseño amigable que facilita la navegación y el uso de la aplicación, presentando un teclado numérico muy sencillo para que cualquier persona pueda utilizarlo.

## Integración con la API

La aplicación utiliza una API sencilla y ligera conocida como Fixer para obtener tasas de cambio precisas entre 170 divisas de todo el mundo, actualizadas cada 60 segundos y con datos históricos desde 1999.
