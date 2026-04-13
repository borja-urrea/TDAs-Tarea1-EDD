# PLANIFICADOR DINAMICO DE TAREAS

Este programa tiene como fin la gestion de pendientes usando TDAs (tipos de datos abstractos). Principalmente se usa el tipo Cola (Quegue) para garantizar que el despacho de tareas respete el orden de llegada (FIFO), asi en vez de priorizar una tarea por sobre otra, seran atendidas en segun cuando fueron agregadas al programa.

## Compilacion

El archivo que contiene el programa es "tarea11.c", para ejecutarlo se usa el siguiente comando:

````
gcc tdas/*.c tarea11.c -Wno-unused-result -o tarea11
````

Y luego ejecutar:
````
./tarea11
````
## Funcionalidades Implementadas
1. Gestion de Categorias
2. Registros de Pendientes
3. Atencion de Tareas
4. Filtrado: consulta por categoria

### Problemas de funcionalidad
No fue encontrado ninguna lectura de datos que error/no funcionen. Asi que no hay nada que agregar en esta parte, ningun error, ni causas posibles

## Ejemplo (ingresado en el teclado)
1. Seleccionar '1' -> Registrar categoría "UNIVERSIDAD".
2. Seleccionar '1' -> Registrar categoría "TRABAJO".
3. Seleccionar '2' -> Eliminar "TRABAJO" (Se limpia la categoría y sus tareas).
4. Seleccionar '4' -> Agregar tarea a "UNIVERSIDAD" (Descripción: "Estudiar certamen").
5. Seleccionar '6' -> Atender tarea (Muestra la tarea de Universidad y limpia el sistema, y al ser la unica que existia, se muestra por pantalla el mensaje ¡Libre de pendientes!).
0. Salir.
