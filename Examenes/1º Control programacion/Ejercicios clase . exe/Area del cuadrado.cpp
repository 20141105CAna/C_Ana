/*Calcular el �rea del cuadrado*/
#include <stdio.h>
int main()
{
    int lado, area;
    
    printf("Introduce el lado del cuadrado: ");
    scanf("%d", &lado);
    
    area = lado*lado;
    printf("El �rea del cuadrado es: %d", area);
    
    getchar ();
    getchar ();
    return 0;
    
}
