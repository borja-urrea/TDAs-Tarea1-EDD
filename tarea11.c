#include <stdio.h>
//#include <stdlib>
#include <string.h>
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/queue.h"

void mostrarOpciones(){
  printf("=========================\n");
  printf("Selecciona una funcion\n");
  printf("=========================\n");
  printf("1. Agregar nueva categoria\n");
  printf("2. Eliminar una categoria\n");
  printf("3. Mostrar categorias almacenadas\n");
  printf("0. Terminar\n");
}

void mostrarLista(List *listaCategorias){
  if (listaCategorias == NULL) return;
  char *item = list_first(listaCategorias);
  while (item != NULL) {
    printf("%s\n", item);
    item = list_next(listaCategorias);
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

void recolectarDatos(List *listaCategorias){
  int dato;
  do {
    mostrarOpciones();
    scanf("%d", &dato);
    getchar();
    switch(dato){
      case 1: {
        char nombre[50];
        if(fgets(nombre, sizeof(nombre), stdin)){
          nombre[strcspn(nombre, "\n")] = 0;
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
        printf("Escriba la categoria que desea eliminar\n");
        char nombre[50];
        if(fgets(nombre, sizeof(nombre), stdin)){
          nombre[strcspn(nombre, "\n")] = 0;
          eliminarCategoria(nombre, listaCategorias);
        }
        //eliminar tareas
        
      }
      case 3: {
        mostrarLista(listaCategorias);
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
  //Quehue *colaTareas = list_create(NULL);
  recolectarDatos(listaCategorias);
  
  return 0;
}