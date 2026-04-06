TAREA11
"tarea11.c" es el archivo en el cual hice mi codigo, para ejecutarlo en shell se usa el siguiente comando:
````
gcc tdas/*.c tarea11.c -Wno-unused-result -o tarea11
````

Y luego ejecutar:
````
./tarea11
````
(estas siguientes lineas no las he editado, son parte del replit de ejemplo que fue compartido)
## TDAs
En la carpeta `tdas` se encuentran implementados distintos TDAs que puedes utilizar (lista, pila, cola, cola con prioridad y mapas). 

Las implementaciones no son las más eficientes (todas usan como estructura de datos una **lista enlazada**), por lo que puedes reemplazarlas por las que has realizado en los labs.

## Otros códigos (en carpeta examples)
Para ejecutar los distintos ejemplos que hay en la carpeta `examples`, primero debes compilarlos. Si estamos en la carpeta raíz:
````
gcc tdas/*.c examples/example2_menu.c -Wno-unused-result -o example
````
Y luego ejecutarlos:
````
./example
````
