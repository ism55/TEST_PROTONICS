# Conocimientos de C++

## 1_A- Programación de aplicaciones multi-threading. ¿Qué utilizarías para proteger dos hilos que utilicen un mismo recurso de una condición de carrera? ¿Como transmitirías mensajes de un hilo al otro para que el segundo los vaya atendiendo según el orden de envío?. ¿Que problemáticas podríamos encontrar al utilizar mutex?, nombra un posible caso y posible solución.

### R:

Se puede utilizar bloqueos mutex, el cuál permite proteger datos compartidos y eso evita condiciones de carrera en entornos multi procesos.

los subprocesos bloquea un mutex antes de modificar o leer cualquier dato y luego de realizar la operación cada proceso es desbloqueado.

- Para esto se utiliza las promesas para el envío de datos y las promesas para obtener o recibir el valor (Revisar)

- Una de las problematicas que se puede encontrar es que no se libere el bloqueo de un subproceso y esto hace que los demás subprocesos delprogrma queden en espera (deadlock), para solucionarlo se utiliza la plantilla lock_guard, envuelve al mutex dentro de su objeto y lo bloquea en su constructor, luego al terminar el proceso y llamar al destructor hace que se libere el mutex

## 2_A- Conocimientos sobre Design Patterns. ¿Por qué es beneficioso su uso?

### R:

Porque son patrones reutilizables que brindan soluciones habituales en el diseño de software

## ¿Diferencia entre Behavioral Patterns y Structural Patterns?

### R:

Structural Patterns se trata de plantillas ya listas que utilizan relaciones entre clases.

Behavioral patterns permite modelar el comportamiento del software, se utiliza para simplificar los proceso de control.

## ¿Para qué se utiliza un Abstract Factory?.

### R:

Abstract Factory se utiliza para crear un diseño que resuelve el problema de crear familias enteras de productos sin especificar clases concretas

## 3_A- Conocimientos sobre compiladores (A bajo nivel a ser posible). ¿Qué compiladores has utilizado?

### R:

1. XCode
2. GCC
3. Microsoft Visual C++

## 4_A- Cross-compilado: herramientas.

### R:

Visual studio

## 5_A- CI/CD: ¿nivel de testing y y de integración continua? Herramientas de ayuda.

### R:

No he estado en proyectos que implementen bien el CI/CD, entonces poseo un nivel basico en este tema.

## 6_A- C/C++: Uso de memoria dinámica, ¿qué es y como lo utilizarías? Alternativas para evitar ciertas desventajas.

### R:

la memoria dinámica permite reservar espacios de memoria en la zona 'Heap' con el operador 'new', el cuál tiene la función de reservar posiciones de memoria, la desventaja es que la memoria debe ser liberada de manera manual una vez que ya no se necesite mas ya que en C++ no hay una herramienta que lo haga de manera automática, existen dos soluciones para este problema, el primero es el uso de las palabras reservadas 'delete' y el segundo para versiones de C++ más nuevas es el uso de las clases especiales 'Smart Pointers' que permiten automatizar el proceso

## 7_A- C/C++: ¿Qué es una clase abstracta?, ¿Qué es el polimorfismo y la herencia?

### R:

Una clase abstracta es un método que se define en una clase padre y obliga a que las clases hijas se definan de esta manera, es decir, no se pueden declarar objetos de una clase abstracta.

-Polimorfismo: Capacidad de manejar varias clases heredadas que vienen de una clase base y existen dos clases polimorfismo estático (es reservada en tiempo de compilacion) y polimorfismo dinámico (sucede en tiempo de ejecución de la aplicación)

- Herencia: permite crear nuevas clases partiendo de clases que ya existen, esto permite poder reusar variables y funciones definidas en otras clases

## 8_B- C/C++: Comunicación entre threads y gestión de las mismas. Pon un ejemplo de comunicación asíncrona.

### R:

Utilizando conditional variables y mutex para un hilo que genere números y otro hilo que los procese.

## 9_C- Modificadores en C/C++: ¿Para que sirve el especificador "inline"?

R: Sirve para indicar al compilador que sustituya o reemplace cualquier llamada a la función por el contenido actual de la función, es importante tomar en cuenta que la función debe estar definida antes de ser llamada.

## ¿Para que utilizarías el modificador "volatile"?

### R:

El modificador "volatile" se utiliza para poder modificar en varios procesos diferentes del programa actual, esto permite tener acceso a posiciones de memoria utilizadas en procesos asíncronos.

## ¿y el modificador "mutable"?

### R:

Es un modificador de tipos de variable y sirve para que un miembro siga siendo variable aunque la instancia de su clase sea declarada como 'const' y una de sus funciones es para bloquear por ejemplo una lista cuando hay una comunicación multihilos
