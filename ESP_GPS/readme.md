# Prueba Técnica Firmware

# Procedimientos

Ir a la web de Adafruit para ubicar el sensor Adafruit Ultimate GPS Module (Product ID 790)

Link: https://www.adafruit.com/product/790

Leer datasheet y documentación de Adafruit
Luego de verificar la documentación, me fijo que poseer una librería integrada con Arduino y algunos ejemplos
Por efectos de rapidez, me inclino a utilizar un ESP32 a través de Arduino

Para la realización de este proyecto estimo un máximo de 1 día a dedicación exclusiva, ya que hay que leer detalladamente el uso correcto de la librería.

Creo el proyecto en Arduino e instalo el SDK del ESP32 y la librería Adafruit GPS para utilizar el GPS.

Adafruit GPS Library v1.7.1

Para realizar el código se debe definir el modo de conexión. En el cuál escojo serial, utilizando el hardware del ESP32 ya que dispone de varios puertos.

Seguido de esto, reviso el ejemplo recomendado por Adafruit en

https://github.com/adafruit/Adafruit_GPS/tree/master/examples/GPS_HardwareSerial_Parsing

Ya que ofrece un buen punto de partida para estructurar el código deseado

En el ejemplo se puede ver cómo obtener la Latitud y la Longitud de las coordenadas obtenidas. Por lo que ahora es necesario hacer la lógica para medir la distancia. Para ello utilizaré la fórmula de Heaversine, que ya conozco de un proyecto anterior.

Esta fórmula permite calcular la distancia de acuerdo al radio de la tierra. Como me encuentro cercano al Ecuador, elegiré el radio ecuatorial de 6378 Km. Sin embargo, decido documentarme más y encuentro una información en
https://rosettacode.org/wiki/Haversine_formula

Allí recomiendan utilizar 6371Km debido a una referencia de la IUGG.

En Rosetta Code también encuentro una implementación válida para la fórmula de Heaversine en lenguaje C.

https://rosettacode.org/wiki/Haversine_formula#C

Antes de proceder a modificar el código de ejemplo, debo comprobar que el código de la fórmula de Heaversine funciona correctamente. Ya que las modificaciones que hago, debo verificarlas. No ocurre así con el ejemplo, ya que confío en que ha pasado una revisión previa.

Para eso compilo el código con un print en la consola que me devuelva un número ya comprobado, como ya aparece en Rosetta Code

Después que compruebo que funciona mediante el print en la línea 48, modifico el código del ejemplo para el cálculo de la distancia.

Para una distancia fija, tomaré una plaza de Caracas como referencia:

Plaza Bolivar de Caracas
https://goo.gl/maps/Xh9KSQGFLiMSNacc6

Latitud: 10.5060384
Longitud: -66.9146525

Después de hacer estas modificaciones, se compila el código en Arduino y el resultado es exitoso.

Tiempo total dedicado: 4 horas.
