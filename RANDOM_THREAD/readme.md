# Prueba de nivel práctico ( En C++ 11 o C++ 14)

# Procedimientos

En principio el tiempo estimado para el desarrollo eran 3 días. Sin embargo, en la práctica observé que no fue suficiente para corregir el paralelismo de los hilos.

Hice mucha lectura e investigación técnica en distintos foros y videos de youtube acerca del manejo de los procesos multihilos y la programación concurrente, además de aprender de las diferencias entre las versiones pasadas de C++ y las modernas.

De todos los canales de Youtube el que más destaco es el de Bo Qian: https://www.youtube.com/@BoQianTheProgrammer/playlists

# Resultados

La solución implementada se hizo a través de una lógica secuencial en la cuál se realizan de igual forma las tareas solicitadas por el problema.

Se utilizó gcc para compilar y la versión C++14 para el desarrollo.

Para compilar se debe hacer lo siguiente:

```
g++ -o main main.cpp -pthread
```

# Problemas

- Sincronización del daemon del hilo principal respecto a los demás hilos. Esto debe mejorarse.
- Consumo de tiempo superior al esperado para hacer el relevamiento de la información solicitada en el problema.
