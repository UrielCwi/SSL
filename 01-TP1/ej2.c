#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

int atoi(char s[])
{
    int i, n;
    for (i = 0; isspace(s[i]); i++) //BORRAR ESPACIOS
        ;
    // Convierte los caracteres numéricos
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');

    return n;
}
int esValido(char s[])
{
    int i;
    int valido = 1;

    for (i = 0; s[i] != '\0'; i++) {
        /* Cualquier caracter que no sea digito corta el proceso */
        if (!isdigit((unsigned char)s[i])) {
            valido = 0;
            break;
        }
    }

    return valido;
}

int main(void)
{
    char line[MAXLINE];

    printf("Ingrese un numero entero: ");
    gets(line);

     if (!esValido(line)) {
        printf("Error: caracter no reconocido, se corta el proceso.\n");
        return 1;
    }

    int numero = atoi(line);

    printf("Numero convertido a entero: %d\n", numero);

    return 0;
}