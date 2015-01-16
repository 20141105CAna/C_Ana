/* elemento.h
 */
#if !defined(_ELEMENTO_H)
#define _ELEMENTO_H


// Tipo Elemento (un elemento de la lista) ///////////////////////
typedef struct s
{
  void *datos;          // área de datos
  struct s *siguiente; // puntero al siguiente elemento
} Elemento;


#endif // _ELEMENTO_H 

