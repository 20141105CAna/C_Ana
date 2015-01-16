/* Ordenación alfabética de frases de un documento
 * procedente de stdin
 * ejercicio4.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
                                                       
typedef struct datos
{
  char *linea;
  struct datos *izq, *der;
} nodo;

nodo *crear_nodo(void);
nodo *crear_arbol(void);
nodo *poner_nodo(nodo *raiz, char *cadena);
void imprimir_arbol(nodo *a, char orden);
void borrar_arbol(nodo *a);

int main(int argc, char *argv[])
{                        
  nodo *raiz;

  if( argc > 2 || (argc == 2 && argv[1][1] != 'r'))
  {
    // Comprobación de la sintaxis de llamada
    printf("Sintaxis:\n\tPara mostrar ascendentemente:\n%s\n\t"
      "Para mostrar descendentemente:\n%s -r\n", argv[0], argv[0]);
    exit(-1);  
  }                                          
  puts("Escriba varias cadenas de texto. Finalice con EOF.");
  raiz = crear_arbol(); // creación del árbol

  if(argc == 1)
  {
    puts("");
    puts("Las cadenas ordenadas ascendentemente:\n");
    imprimir_arbol(raiz, 'a'); 
  }
  else
  {
    puts("");
    puts("Las cadenas ordenadas descendentemente:\n");
    imprimir_arbol(raiz, 'b');
  }
  
  borrar_arbol(raiz);

  return 0;
}

nodo *crear_arbol(void)
{
  // Crea un árbol según se van tecleando los datos
  nodo *raiz = NULL;  
  char cadena[250];

  if (gets(cadena)!= NULL)
    raiz = poner_nodo(raiz, cadena);
  while (gets(cadena) != NULL)
    poner_nodo(raiz, cadena);
  return raiz;
}

nodo *poner_nodo(nodo *raiz, char *cadena)
{
  // Añade un nuevo nodo
  if ( raiz != NULL )
  {                   
    if ( strcmp( cadena, raiz->linea) < 0 ) // cadena es menor
      raiz->izq = poner_nodo(raiz->izq, cadena);
    else               
      raiz->der = poner_nodo( raiz->der, cadena );
  }
  else
  {
    raiz = crear_nodo();
    if ((raiz->linea = (char *) malloc(strlen(cadena) + 1)) == NULL)
    {
      perror("poner_nodo");
      exit(-1);
    }
    strcpy( raiz->linea, cadena );
    
  } 
  return raiz;
}

void imprimir_arbol(nodo *a, char orden)
{
  //clearerr(stdin);
  if(a != NULL)
  {
    if(orden == 'a')
    {
      imprimir_arbol(a->izq, 'a');
      puts(a->linea);
      imprimir_arbol(a->der, 'a');
    }
    else 
    {
      imprimir_arbol(a->der, 'b');
      puts(a->linea);
      imprimir_arbol(a->izq,'b');
    }
  }
}

nodo *crear_nodo()
{
  /* Crear un nodo del árbol binario */
  nodo *aux;

  if ((aux = (nodo *)malloc(sizeof(nodo))) == NULL)
  {
    perror("crear_nodo");
    exit(-1);
  }
  aux->izq = aux->der = NULL;
  return aux;
}               

void borrar_arbol(nodo *a)
{
  /* Liberar la memoria asignada a cada uno de los nodos del árbol
   * direccionado por a. Se recorre el árbol en postorden.
   */
  if (a != NULL)
  {
    borrar_arbol(a->izq);
    borrar_arbol(a->der);
    free(a->linea);
    free(a);
  }
}               

