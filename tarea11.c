#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
#include <ctype.h>
#include <time.h>

typedef struct {
  char descripcion[50];
  char ncategoria[50];
  char tiempoF[20];
} tarea;

void aMayusculas(char *cadenaAmayus){
  for (int i = 0; cadenaAmayus[i]; i ++){
    cadenaAmayus[i] = toupper((unsigned char)cadenaAmayus[i]);
  }
}

void mostrarOpciones(){
  printf("\n\n=========================\n");
  printf("Selecciona una funcion\n");
  printf("=========================\n");
  printf("1. Agregar nueva categoria\n");
  printf("2. Eliminar una categoria\n");
  printf("3. Mostrar categorias almacenadas\n");
  printf("4. Ingresar tarea\n");
  printf("5. Mostrar listado de tareas\n");
  printf("6. Atender tarea\n");
  printf("7. Filtrar tareas por categoria\n");
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
  printf("---- LISTA DE TAREAS Y SU CATEGORIA ----\n");
  if (colaTareas == NULL){
    printf("Cola vacia\n");
    return;
  }
  tarea *tareaMostrar = (tarea*) queue_front(colaTareas);
  while (tareaMostrar != NULL){
    printf("Tarea: %15s || Categoria: %15s || Hora: %s \n", tareaMostrar -> descripcion, tareaMostrar -> ncategoria, tareaMostrar -> tiempoF);
    tareaMostrar = (tarea*) queue_next(colaTareas);
  }
  printf("\n\n");
}

void mostrarColaF(Queue *colaTareas){
  if (colaTareas == NULL) return;
  tarea *tareaMostrar = (tarea*) queue_front(colaTareas);
  while(tareaMostrar != NULL){
    printf("Tarea: %20s\n", tareaMostrar -> descripcion);
    tareaMostrar = (tarea*) queue_next(colaTareas);
  }
}

void eliminarCategoria(char *nombre, List *listaCategorias){
  char *eliminar = list_first(listaCategorias);
  while (eliminar != NULL){
    if (strcmp(eliminar, nombre) == 0){
      char *eliminado = list_popCurrent(listaCategorias);
      free(eliminado);
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
  
  queue_clean(aux);
  free(aux);
}

int existeCategoria(List *listaCategoria, char *categoria){
  char *aux = list_first(listaCategoria);
  while (aux != NULL){
    if (strcmp(aux, categoria) == 0){
      return 1;
    }
    aux = list_next(listaCategoria);
  }
  return 0;
}

void filtrarCategorias(char *categoria, Queue *colaTareas){
  if (colaTareas == NULL) return;
  Queue *colaAux = queue_create(NULL); 
  tarea *tareaE = queue_front(colaTareas);

  while(tareaE != NULL){
    if (strcmp(tareaE -> ncategoria, categoria) == 0){
      queue_insert(colaAux, tareaE);
    }
    tareaE = (tarea*) queue_next(colaTareas);
  }
  
  printf("--- Listado de Tareas Categoria: %s ---\n", categoria);
  mostrarColaF(colaAux);
  queue_clean(colaAux);
}

void mostrarTareaMasAntigua(tarea *tareaMostrar){
  printf("--- TAREA A PROCESAR ---\n\n");
  printf("Atendiendo : %s | Categoria : %s | Hora Registro : %s\n"
    , tareaMostrar -> descripcion, tareaMostrar -> ncategoria, tareaMostrar -> tiempoF);
  printf("Tarea procesada ya fue eliminada de tu lista de pendientes.\n");
  return;
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
        if (list_first(listaCategorias) == NULL){
          printf("\nNo hay categorias para eliminar\n");
          break;
        }
        
        printf("Escriba la categoria que desea eliminar: \n");
        char nombre[50];
        if(fgets(nombre, sizeof(nombre), stdin)){
          aMayusculas(nombre);
          nombre[strcspn(nombre, "\n")] = 0;
        }

        if (existeCategoria(listaCategorias, nombre) == 0) {
          printf("Categoria no existe\n");
        } else{
          eliminarCategoria(nombre, listaCategorias);
          printf("Categoria eliminada\n");
        }
        
        if(queue_front(colaTareas) != NULL){
          eliminarTareasCategoria(nombre, colaTareas);
        }
        break;
      }
      
      case 3: {
        if (list_first(listaCategorias) == NULL){
          printf("\nNo hay categorias registradas\n");
          break;
        }
        mostrarLista(listaCategorias);
        break;
      }

      case 4: {
        if (list_first(listaCategorias) == NULL){
          printf("\nIngresa una categoria antes\n");
          break;
        }
        tarea *tareaNueva = (tarea*) malloc(sizeof(tarea));

        mostrarLista(listaCategorias);
        printf("Ingrese categoria a la que pertenece su tarea\n");
        if (fgets(tareaNueva -> ncategoria, 50, stdin)){
          tareaNueva -> ncategoria[strcspn(tareaNueva -> ncategoria, "\n")] = 0;
          aMayusculas(tareaNueva -> ncategoria);
        }
        while(existeCategoria(listaCategorias, tareaNueva -> ncategoria) == 0){
          printf("Categoria NO valida, ingresar otra\n");
          fgets(tareaNueva -> ncategoria, 50, stdin);
          tareaNueva -> ncategoria[strcspn(tareaNueva -> ncategoria, "\n")] = 0;
          aMayusculas(tareaNueva -> ncategoria);
        }
        
        printf("Ingrese el nombre de su tarea\n");
        if (fgets(tareaNueva -> descripcion, 50, stdin)){
          tareaNueva -> descripcion[strcspn(tareaNueva -> descripcion, "\n")] = 0;

          time_t t = time(NULL);
          t -= 14400;
          struct tm *tm_info = localtime(&t);
          strftime(tareaNueva -> tiempoF, 20, "%H:%M:%S", tm_info);
          
          queue_insert(colaTareas, tareaNueva);
        } else{
          free(tareaNueva);
        }
        break;
      }

      case 5: {
        if (queue_front(colaTareas) == NULL){
          printf("\nNo hay tareas ingresadas\n");
          break;
        }
        mostrarCola(colaTareas);
        break;
      }

      case 6: {
        //como almacene las tareas en una cola, la mas antigua ingresada coincide con el front de la misma
        //por eso no "buscare"
        if (queue_front(colaTareas) == NULL){
          printf("\nLibre de pendientes\n");
          break;
        }
        mostrarCola(colaTareas);

        tarea *tareaMasAntigua = queue_remove(colaTareas);
        mostrarTareaMasAntigua(tareaMasAntigua);
        if(queue_front(colaTareas) == NULL){
          printf("¡LIBRE DE PENDIENTES!\n");
        }
        break;
      }
      
      case 7: {
        if (queue_front(colaTareas) == NULL){
          printf("\nNo hay categorias para filtrar \n");
          break;
        }
        printf("Ingrese la categoria para mostrar sus tareas \n");
        mostrarLista(listaCategorias);
        char categoria[50];
        if(fgets(categoria, sizeof(categoria), stdin)){
          categoria[strcspn(categoria, "\n")] = 0;
          aMayusculas(categoria);

          while(existeCategoria(listaCategorias, categoria) == 0){
            printf("Categoria no existe, ingresa otra\n");
            fgets(categoria, 50, stdin);
            categoria[strcspn(categoria, "\n")] = 0;
            aMayusculas(categoria);
          }
          
          filtrarCategorias(categoria, colaTareas);
        }
        
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
    
  }while(dato != 0);
}      
    
int main(){

  List *listaCategorias = list_create();
  Queue *colaTareas = queue_create(NULL);
  recolectarDatos(listaCategorias, colaTareas);
  return 0;
}