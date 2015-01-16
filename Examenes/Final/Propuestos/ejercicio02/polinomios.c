//////////////////////////////////////////////////////////////////
// Trabajar con una lista lineal simplemente enlazada y ordenada.
// polinomios.c
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "interfaz_llseo.h"

//////////////////////////////////////////////////////////////////
// Tipo Termino: define una expresión de la forma a.x^n.y^m
//               a es el coeficiente de tipo double.
//               n y m son los exponentes enteros de x e y.
//
typedef struct
{
  double coeficiente; // coeficiente
  int exponenteDeX;   // exponente de x
  int exponenteDeY;   // exponente de y
} Termino;


void mostrarTermino(Termino t)
{
  if (t.coeficiente == 0) return;
  // Mostrar término
  // Signo
  t.coeficiente < 0 ? printf(" - ") : printf(" + ");
  // Coeficiente
  if (fabs(t.coeficiente) != 1)
    printf("%g", fabs(t.coeficiente));
  // Potencia de x
  if (t.exponenteDeX > 1 || t.exponenteDeX < 0)
    printf("x^%d", t.exponenteDeX);
  else if (t.exponenteDeX == 1)
    printf("x");
  // Potencia de y
  if (t.exponenteDeY > 1 || t.exponenteDeY < 0)
    printf("y^%d", t.exponenteDeY);
  else if (t.exponenteDeY == 1)
    printf("y");
}
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// Definir la función comparar según el prototipo especificado
// en interfaz_llseo.h, para adaptarlas a nuestras necesidades.
//
// Permite comparar los datos de dos elementos. datos1 es el
// término que se inserta y datos2 pertenece a la lista.
int comparar(void *datos1, void *datos2)
{
  int k = 10, a = 0, b = 0, r = 0;
  int expX1 = ((Termino *)datos1)->exponenteDeX;
  int expY1 = ((Termino *)datos1)->exponenteDeY;
  int expX2 = ((Termino *)datos2)->exponenteDeX;
  int expY2 = ((Termino *)datos2)->exponenteDeY;

  while (abs(expX1) > k || abs(expY1) > k ||
         abs(expX2) > k || abs(expY2) > k) k = k*10;
  a = expX1 * k + expY1;
  b = expX2 * k + expY2;

  // Orden descendente
  if (a > b) r = -1;
  if (a == b) r = 0;
  if (a < b) r = 1;

  return r;
}

void mostrarPolinomio(tllseo *poli)
{
  // Mostrar todos los términos del polinomio
  Termino *t = (Termino *)obtenerPrimero(poli);
  while (t)
  {
    mostrarTermino(*t);
    t = (Termino *)obtenerSiguiente(poli);
  }
  printf("\n\n");
}

void liberarMemoria(tllseo *poli)
{
  // Borrar todos los términos del polinomio
  Termino *t = (Termino *)borrarPrimero(poli);
  while (t)
  {
    free(t); // borrar el área de datos
    t = (Termino *)borrarPrimero(poli); // borrar elemento
  }
}


tllseo sumar(tllseo pA, tllseo pB)
{
  // pR = sumar(pA, pB).
  int k = 0;
  Termino *tA = NULL, *tB = NULL, *tR = NULL;
  tllseo pR; // polinomio resultante
  iniciarLista(&pR);

  tA = obtenerPrimero(&pA);
  tB = obtenerPrimero(&pB);
  // Sumar pA con pB
  while ( tA != NULL && tB != NULL )
  {
    k = comparar(tA, tB);
    tR = (Termino *)malloc(sizeof(Termino));
    if (!tR) error();

    if ( k == 0 )
    {
      tR->coeficiente = tA->coeficiente + tB->coeficiente;
      tR->exponenteDeX = tA->exponenteDeX;
      tR->exponenteDeY = tA->exponenteDeY;
      tA = obtenerSiguiente(&pA);
      tB = obtenerSiguiente(&pB);
    }
    else if ( k < 0 )
    {
      tR->coeficiente = tA->coeficiente;
      tR->exponenteDeX = tA->exponenteDeX;
      tR->exponenteDeY = tA->exponenteDeY;
      tA = obtenerSiguiente(&pA);
    }
    else
    {
      tR->coeficiente = tB->coeficiente;
      tR->exponenteDeX = tB->exponenteDeX;
      tR->exponenteDeY = tB->exponenteDeY;
      tB = obtenerSiguiente(&pB);
    }
    if (tR->coeficiente)
      anyadir(tR, &pR);
    else
      free(tR);
  }
  // Términos restantes en el pA
  while ( tA != NULL )
  {
    tR = (Termino *)malloc(sizeof(Termino));
    if (!tR) error();

    tR->coeficiente = tA->coeficiente;
    tR->exponenteDeX = tA->exponenteDeX;
    tR->exponenteDeY = tA->exponenteDeY;
    anyadir(tR, &pR);
    tA = obtenerSiguiente(&pA);
  }
  // Términos restantes en el pB
  while ( tB != NULL )
  {
    tR = (Termino *)malloc(sizeof(Termino));
    if (!tR) error();

    tR->coeficiente = tB->coeficiente;
    tR->exponenteDeX = tB->exponenteDeX;
    tR->exponenteDeY = tB->exponenteDeY;
    anyadir(tR, &pR);
    tB = obtenerSiguiente(&pB);
  }

  return pR;
}


Termino *leerTermino()
{
  Termino *t = NULL;

  // Crear un objeto de tipo Datos
  t = (Termino *)malloc(sizeof(Termino));
  if (!t) error();
  // Datos por error
  t->coeficiente = 0.0; t->exponenteDeX = 1; t->exponenteDeY = 1;
  // Leer datos
  printf("\nCoeficiente:    ");
  scanf("%lf", &t->coeficiente);
  printf("Exponente de X: ");
  scanf("%d", &t->exponenteDeX);
  printf("Exponente de Y: ");
  scanf("%d", &t->exponenteDeY); fflush(stdin);

  return t;
}

main()
{
  char resp = 's';
  Termino *termino = NULL, *aux = NULL;

  // Definir una lista lineal vacía
  tllseo polinomioA;
  tllseo polinomioB;
  tllseo polinomioR;

  iniciarLista(&polinomioA);
  iniciarLista(&polinomioB);
  iniciarLista(&polinomioR);

  // Leer datos y añadirlos a la lista
  printf("Polinomio A:");
  while (resp == 's')
  {
    termino = leerTermino();
    if (buscar(termino, &polinomioA))
    {
      aux = obtenerActual(&polinomioA);
      aux->coeficiente += termino->coeficiente;
      free(termino);
    }
    else
      anyadir(termino, &polinomioA);

    printf("¿desea insertar otro? (s/n) ");
    resp = getchar(); fflush(stdin);
  } 

  printf("\nPolinomio B:");
  resp = 's';
  while (resp == 's')
  {
    termino = leerTermino();
    if (buscar(termino, &polinomioA))
    {
      aux = obtenerActual(&polinomioA);
      aux->coeficiente += termino->coeficiente;
      free(termino);
    }
    else
      anyadir(termino, &polinomioA);

    printf("¿desea insertar otro? (s/n) ");
    resp = getchar(); fflush(stdin);
  } 

  // Sumar polinomios
  polinomioR = sumar(polinomioA, polinomioB);

  // Mostrar polinomio
  printf("\nLista:\n");
  mostrarPolinomio(&polinomioR);

  // Borrar la lista
  liberarMemoria(&polinomioA);
  liberarMemoria(&polinomioB);
  liberarMemoria(&polinomioR);
}

