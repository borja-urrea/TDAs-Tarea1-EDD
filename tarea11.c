#include <stdio.h>
//#include <stdlib>
#include <string.h>
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
#include <ctype.h>

typedef struct {
  char descripcion[50];
  char ncategoria[50];
} tarea;

void aMayusculas(char *cadenaAmayus){
  for (int i = 0; cadenaAmayus[i]; i ++){
    cadenaAmayus[i] = toupper((unsigned char)cadenaAmayus[i]);
  }
}

void mostrarOpciones(){
  printf("=========================\n");
  printf("Selecciona una funcion\n");
  printf("=========================\n");
  printf("1. Agregar nueva categoria\n");
  printf("2. Eliminar una categoria\n");
  printf("3. Mostrar categorias almacenadas\n");
  printf("4. Ingresar tarea\n");
  printf("5. Mostrar cola tareas\n");
  printf("0. Terminar\n");
}

void mostrarLista(List *listaCategorias){
  printf("----- LISTA DE CATEGORIAS -----\n");
  if (listaCategorias == NULL) return;
  char *item = list_first(listaCategorias);
  while (item != NULL) {
    printf("%s\n", item);
    item = list_next(listaCategorias);
  }
}

void mostrarCola(Queue *colaTareas){
  printf("----- LISTA DE PENDIENTES Y SU CATEGORIA -----\n");
  if (colaTareas == NULL) return;
  tarea *tareaMostrar = (tarea*) queue_front(colaTareas);
  while (tareaMostrar != NULL){
    printf("Tarea: %20s || Categoria: %s \n", tareaMostrar -> descripcion, tareaMostrar -> ncategoria);
    tareaMostrar = (tarea*) queue_next(colaTareas);
  }
}

void eliminarCategoria(char *nombre, List *listaCategorias){
  char *eliminar = list_first(listaCategorias);
  while (eliminar != NULL){
    if (strcmp(eliminar, nombre) == 0){
      list_popCurrent(listaCategorias);
      return;
    }
    eliminar = list_next(listaCategorias);
  }
}

void eliminarTareasCategoria (char *categoria, Queue *colaTareas){
  if (colaTareas == NULL) return;
  Queue *aux = queue_create(NULL);
  printf("Tareas de la categoria %s eliminadas\n", categoria);
  tarea *tareaEliminar = (tarea*) queue_front(colaTareas);
  while(tareaEliminar != NULL){
    if (strcmp(tareaEliminar -> ncategoria, categoria) != 0){
      queue_insert(aux, tareaEliminar);
    }else{
      free(tareaEliminar);
    }
    tareaEliminar = (tarea*) queue_next(colaTareas);
  }
  queue_clean(colaTareas);
  tarea *auxTareas = (tarea*) queue_front(aux);
  while(auxTareas != NULL){
    queue_insert(colaTareas, auxTareas);
    auxTareas = (tarea*) queue_next(aux);
  }
  free(aux);
}

void recolectarDatos(List *listaCategorias, Queue *colaTareas){
  int dato;
  do {
    mostrarOpciones();
    scanf("%d", &dato);
    getchar();
    switch(dato){
      case 1: {
        printf("Ingrese el nombre de su categoria: \n");
        char nombre[50];
        if(fgets(nombre, sizeof(nombre), stdin)){
          nombre[strcspn(nombre, "\n")] = 0;
          aMayusculas(nombre);
          char *nombreAux = (char*)malloc((strlen(nombre)+1) * sizeof(char));
          if(nombreAux != NULL){
            strcpy(nombreAux, nombre);
            list_pushBack(listaCategorias, nombreAux);
          }
        }
        break;
      }
      case 2: {
        //e.c
        printf("Escriba la categoria que desea eliminar: \n");
        char nombre[50];
        if(fgets(nombre, sizeof(nombre), stdin)){
          aMayusculas(nombre);
          nombre[strcspn(nombre, "\n")] = 0;
          eliminarCategoria(nombre, listaCategorias);
        }
        if(queue_front(colaTareas) != NULL){
          eliminarTareasCategoria(nombre, colaTareas);
        }
        break;
      }
      case 3: {
        mostrarLista(listaCategorias);
        break;
      }

      case 4: {
        tarea *tareaNueva = (tarea*) malloc(sizeof(tarea));
        
        printf("Ingrese categoria a la que pertenece su tarea\n");
        fgets(tareaNueva -> ncategoria, 50, stdin);
        tareaNueva -> ncategoria[strcspn(tareaNueva -> ncategoria, "\n")] = 0;
        aMayusculas(tareaNueva -> ncategoria);
        
        printf("Ingrese el nombre de su tarea\n");
        if (fgets(tareaNueva -> descripcion, 50, stdin)){
          tareaNueva -> descripcion[strcspn(tareaNueva -> descripcion, "\n")] = 0;
          queue_insert(colaTareas, tareaNueva);
        }
        break;
      }

      case 5: {
        mostrarCola(colaTareas);
        break;
      }
      
      case 0: {
        return;
      }
      default: {
        printf("Opcion no valida\n");
        break;
      }
    }
    
  }while(1);
}      
    
int main(){
  List *listaCategorias = list_create();
  Queue *colaTareas = queue_create(NULL);
  recolectarDatos(listaCategorias, colaTareas);
  
  return 0;
}