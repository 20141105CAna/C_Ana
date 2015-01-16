// crear_alums.c
//
#include <stdio.h>
#include <stdlib.h>
                                                       
typedef struct
{
  char nombre[60];
  unsigned long dni;
} alumno;

main()
{                        
  FILE *pf = NULL;
  alumno a;

  // Abrir el fichero
  if ((pf = fopen("dni.dat", "wb")) == NULL)
  {
    printf("Error al crear el fichero\n");
    exit(-1);
  } 

  printf("nombre: ");
  while (gets(a.nombre) != NULL)
  {
    printf("dni:    ");
    scanf("%ld", &a.dni); fflush(stdin);
    fwrite(&a, sizeof(alumno), 1, pf);
    printf("nombre: ");
  }
  fclose(pf);    
}
