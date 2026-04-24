# TETRIS

<img width="250" height="188" alt="CarTetrisGIF" src="https://github.com/user-attachments/assets/d47fad22-90f6-476b-a22d-9e83b6018ad8" />

### TP - Tópicos de Programación, 1C 2026.
### Deadline: Miércoles 27 de Mayo de 2026 a las 23:59

### Desarrolladores:
- Cardozo, Gonzalo. 43777470.
- Apellido, Nombre. DNI.
- Apellido, Nombre. DNI.

---
## Objetivo del TP

Desarrollar un videojuego equivalente al juego TETRIS utilizando la biblioteca GBT en ANSI C implementando contenidos vistos en la materia.

---
## Condiciones para el nombre del grupo y entrega

- El nombre de cada grupo debe ser una palabra, y no se puede repetir con otro grupo.  
- El nombre del grupo debe ser una palabra que figure en el diccionario de la RAE (https://dle.rae.es/).  
- El nombre del grupo debe estar formado por letras cuyo valor ASCII esté comprendido entre 0x41 y 0x5a (inclusive). Eso implica que no se admiten espacios, letras en minúscula, tildes, números, etc.

- Se deberá entregar un archivo con el siguiente formato:  
  - TP_TOPICOS_2026_1C_JUEVES_{NOMBRE_DE_GRUPO}.zip.
  - El archivo.zip no debe contener carpetas ni subcarpetas mas que /doc (*carpeta de documentación*) y /img (*carpeta de imagenes*).
  - La entrega únicamente debe contener archivos con extensiones .c y .h y las carpetas mencionadas en el punto anterior.
 
- El archivo main.c debe contener un comentario al comienzo con información sobre sus integrantes en el siguiente formato:
  - Apellido(s), nombre(s):  
    DNI: (sólo números, sin puntos)
    Usuario: (Usuario de GitHub)  
    Entrega: Sí/No  

> [!IMPORTANT]
> El trabajo entregado debe funcionar correctamente, sin warnings y cumplir con todas las funcionalidades requeridas.

---
## Modalidad de juego: Tetris clásico
- El tablero debe tener un tamaño de 20 filas visibles por 10 columnas. Debe tenerse en cuenta que en el Tetris existen filas adicionales invisibles para la generación del tetromino actual.
- Deberá constar, como mínimo, de una paleta de color propia para este modo de juego
- En caso de querer trasladar horizontalmente o rotar el tetrominó y el mismo no entre sin salirse de los bordes, no se debe permitir el movimiento.
 
---
## Checklist
### Funcionalidades minimas

- [ ] Pantalla de presentación.
- [ ] Documentación en el formato de nuestra preferencia explicando todo lo necesario para que un usuario pueda compilar, ejecutar y jugar.
- [ ] Resoluciones lógicas: CGA: 320x200 y VGA: 640x480.
- Sistema de puntuación
   - [ ] Puntos por limpiar una fila, con bonificación por filas extras eliminadas al mismo tiempo.
   - [ ] Puntos por casilleros bajados manualmente.
   - [ ] Puntos visibles en la interfaz gráfica.
- Establecer al menos una dificultad en la cual se alteren los parametros mencionados a continuación.
   - [ ] Velocidad de la caída del tetrominó, la cual debe aumentar un 3% por cada 10 fichas caídas
   - [ ] Velocidad de fijación del tetrominó
   - [ ] A mayor velocidad, mayor los puntos obtenidos por el jugador.
- [ ] Selección del tetrominó de forma aleatoria por algoritmo sin tendencias hacia ciertos tipos.
- [ ] Solicitar nombre del jugador a través de interfaz gráfica.
- [ ] Mostrar estadísticas del juego por nombre del jugador.
- [ ] Crear al menos dos sets de fuentes con diferentes tamaños.
- [ ] Ejecución con argumentos a main para iniciar con diferentes factores de escala y una resolución logica específica.
- [ ] Implementar todos los tetrominós originales.
- [ ] Rotación de piezas tanto a izquierda como a derecha.
- [ ] Menú gráfico para guardar configuraciones perdurables entre sesiones.
- Configuraciones del menu
   - [ ] Paleta de colores a utilizar.
   - [ ] Resolución lógica a utilizar.
   - [ ] Velocidad de caída de tetrominós.
- [ ] Pausa, pantalla de salida y volver a jugar al perder.

### Características opcionales (necesarias para promocionar)

- [ ] Seleccionar modo de juego a "Clásica" o "DX (Deluxe)".
- [ ] Realizar una fuente que no sea monoespaciada.
- [ ] Resolver el tablero mediante un array de punteros a filas, y utilizarlo al momento de limpiar lineas realizando un intercambio de punteros.
- [ ] Realizar nuestra implementación de todas las primitivas de TDA Vector que necesitemos usar.
- [ ] Guardar el estado actual de la partída para retormarla luego (archivo binario).
- [ ] Habilitar algun tipo de cheat.

---
## Modalidad de juego: Tetris DX (Deluxe)

- El tablero, además del tamaño clásico, debe poder ser redimensionado en su ancho variando de 8 a 16 casilleros, para aumentar y disminuir la dificultad respectivamente. Esta opción debe estar disponible en el menú de opciones.
- En caso de querer rotar o mover una pieza estando la misma en un borde, en lugar de imposibilitar la acción, se debe implementar un tablero circular; es decir, que los minos que excedan el límite del tablero, aparezcan del otro lado. Esto permite, por ejemplo, girar una I vertical a horizontal, estando pegada al extremo.
- Deberá, además de los tetrominos correspondientes al Tetris, implementar las siguientes piezas (denominadas en minúscula para diferenciarlas de las originales):
  - x: Consta de un solo mino.
  - c: Consta de cinco minos en forma de c.
  - p: Consta de cinco minos en forma de p.
  - *: Implementar una letra que al grupo le guste, con la cantidad de minos que sea necesaria.

---
> [!WARNING]
> El uso de memoria RAM y CPU deben ser óptimos. El programa no debe superar el 10% de uso de la CPU y como máximo deberá usar 256MB de memoria RAM. Como referencia de CPU se debe utilizar las computadoras de los laboratorios de la Universidad.

> [!NOTE]
> La solución principal del juego debe ser matricial. Se admitirá el uso de matrices estáticas en las funcionalidades mínimas, pero la implementación requerida para la promoción será con las matrices dinámicas vistas en clase, reordenando el array de punteros; evitando así la reescritura de toda la matriz.

> [!NOTE]
> Se valorará el uso de las estructuras vistas en la materia: memoria dinámica, punteros a funciones, recursividad, etc.

> [!NOTE]
> Se valorará particularmente la capacidad de investigación y creatividad del grupo. Lograr una gráfica superadora puede hacer que el producto sea mucho más interesante para cualquier cliente.
