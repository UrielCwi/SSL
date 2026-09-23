#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

int atoi(char s[])
{
    int i, n, sign;
    for (i = 0; isspace(s[i]); i++) //BORRAR ESPACIOS
        ;
    // Convierte los caracteres numéricos
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');

    return sign * n;
}

int main(void)
{
    char line[MAXLINE];

    printf("Ingrese un numero entero: ");
    gets(line);

    int numero = atoi(line);

    printf("Numero convertido a entero: %d\n", numero);

    return 0;
}