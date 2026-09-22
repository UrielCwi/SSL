#include <stdio.h>
#include <string.h>

#define MAX 500

/* Mapea cada carácter a la columna de la tabla */
int columna(int c) {
    if (c == '+' || c == '-') return 0;
    if (c == '0') return 1;
    if (c >= '1' && c <= '7') return 2;
    if (c == '8' || c == '9') return 3;
    if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return 4;
    if (c == 'x' || c == 'X') return 5;
    if (c == '@') return 6;
    return 7; /* Fuera del alfabeto */
}

/* Estados de aceptación según la tabla */
int esEstadoAceptacion(int estado) {
    return (estado == 2 || estado == 4 || estado == 5 || estado == 6 || estado == 7);
}

/* Validador general de la cadena con el autómata */
// AUTOMATA HECHO A MANO TABLA HECHA A MANO
int esPalabra(const char *s) {
    static const int tt[7][8] = {
        /* [+-]  0  1-7 8-9 A-F  x   @  otro */
        {   1,   2,  4,  4,  6,  6,  6,   6 }, /* 0: Inicial    */
        {   6,   6,  4,  4,  6,  6,  6,   6 }, /* 1: CheckSigno */
        {   6,   5,  5,  6,  6,  3,  0,   6 }, /* 2: CheckDel0  */
        {   6,   3,  3,  3,  3,  6,  0,   6 }, /* 3: Hexa2      */
        {   6,   5,  5,  5,  6,  6,  0,   6 }, /* 4: Decimal    */
        {   6,   5,  5,  6,  6,  6,  0,   6 }, /* 5: Octal      */
        {   6,   6,  6,  6,  6,  6,  6,   6 }  /* 6: Fallo      */
    };

    int estado = 0, i = 0;
    if (!s || !s[0]) return 0;

    while (s[i] != '\0') {
        int col = columna((unsigned char)s[i]);
        estado = tt[estado][col];
        if (estado == 6) return 0;
        i++;
    }

    return esEstadoAceptacion(estado);
}

/* Procesa y cuenta los grupos si la cadena es léxicamente válida */
//FUNCION GEMINI
void clasificarYContar(char *cadena) {
    int cantDecimales = 0;
    int cantOctales = 0;
    int cantHexadecimales = 0;

    char *token = strtok(cadena, "@"); //SEPARA EN TOKENS (CADENAS DE CADA GRUPO) Y DESPUES CUENTA CADA TOKEN POR GRUPO
    while (token != 0) {
        /* Identifica el tipo por prefijo característico */
        if (token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) {
            cantHexadecimales++;
        } else if (token[0] == '0' && token[1] != '\0') {
            cantOctales++;
        } else {
            cantDecimales++;
        }
        token = strtok(0, "@");
    }

    printf("\n--- Conteo de constantes enteras ---\n");
    printf("Decimales:      %d\n", cantDecimales);
    printf("Octales:        %d\n", cantOctales);
    printf("Hexadecimales:  %d\n", cantHexadecimales);
}

/* --- MAIN --- */
int main(void) {
    char palabra[MAX];
    char copia[MAX];

    printf("Ingrese la cadena de numeros separados por '@' (ej: +45@077@0x1F@120): ");
    gets(palabra);

    if (esPalabra(palabra)) {
        printf("Resultado: La cadena SE RECONOCE (pertenece al lenguaje).\n");
        strcpy(copia, palabra);
        clasificarYContar(copia);
    } else {
        printf("Resultado: ERROR LEXICO (la cadena NO se reconoce).\n");
    }

    return 0;
}