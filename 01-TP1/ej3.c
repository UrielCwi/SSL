#include <stdio.h>
#include <ctype.h>
#define MAX 500 /* máx tamaño de operando u operador */
#define NUMBER '0' /* señal de que un número se encontró */
#define MAXVAL 100 /* máximo tamaño de la pila de val */

//FUNCION GEMINI
int columna(int c)
{
    if (isdigit(c)) c = NUMBER;
    switch(c)
    {
        case NUMBER:
            return 0;
        case '+' || '-':
            return 1;
        case '*':
            return 2;
        default:
            return 3;
    }
}

//FUNCION GEMINI
int validarExpresion(const char *s) {
    /*AFD PARA VERIFICAR NUMEROS*/
    static const int tt[4][4] = {
        /* Dig,  +/-,  *,   Otro */
        {   1,    2,   3,    3  },  /* Estado 0: Inicio */
        {   1,    2,   2,    3  },  /* Estado 1: Leyendo número (ACEPTACIÓN) */
        {   1,    3,   3,    3  },  /* Estado 2: Tras operador */
        {   3,    3,   3,    3  }   /* Estado 3: Error / Sumidero */
    };

    int estado = 0;
    int i = 0;

    if (s[0] == '\0')
        return 0;

    while (s[i] != '\0') {
        int col = columna((unsigned char)s[i]);
        estado = tt[estado][col];
        i++;
    }
    /* El estado 1 es el único estado de aceptación */
    return (estado == 1);
}

//FUNCION GEMINI
int precedencia(char op) {
    if (op == '*') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

//FUNCION GEMINI
/*La funcion de transformacion de infijo a postfijo basicamente recorre la cadena, apila los numeros en una pila y los operadores en otra,
cuando encuentra un operador con precedencia menor o igual al operador en la cima de la pila, desapila los operadores y los agrega a la salida
hasta que encuentra un operador con menor precedencia o la pila queda vacia. Al final, vacia la pila de operadores a la salida.*/
void infijoARPN(const char *infijo, char *postfijo) {
    char pilaOp[MAX];
    int top = 0;
    int k = 0;
    int i = 0;

    while (infijo[i] != '\0') {
        if (isdigit(infijo[i])) {
            /* Copia el número completo y agrega un espacio separador */
            while (isdigit(infijo[i])) {
                postfijo[k++] = infijo[i++];
            }
            postfijo[k++] = ' ';
        } else {
            char op = infijo[i];
            /* Desapila operadores de mayor o igual precedencia hacia la salida */
            while (top > 0 && precedencia(pilaOp[top - 1]) >= precedencia(op)) {
                postfijo[k++] = pilaOp[--top];
                postfijo[k++] = ' ';
            }
            pilaOp[top++] = op;
            i++;
        }
    }

    /* Vacía los operadores restantes al final */
    while (top > 0) {
        postfijo[k++] = pilaOp[--top];
        postfijo[k++] = ' ';
    }
    postfijo[k] = '\0';
}

//KERNIGHAN Y RITCHIE
int sp = 0;
int val[MAXVAL];

//KERNIGHAN Y RITCHIE
void push(int f) {
    if (sp < MAXVAL) val[sp++] = f;
}

//KERNIGHAN Y RITCHIE
int pop(void) {
    if (sp > 0) return val[--sp];
    return 0;
}

//KERNIGHAN Y RITCHIE
//CALCULADORA POLACA INVERSA (ESTA EN EL LIBRO)
int calculadoraRPN(char *rpn) {
    char *token;
    int op2;
    sp = 0;

    token = strtok(rpn, " \t\n");
    while (token != 0) {
        if (isdigit(token[0])) {
            push(atoi(token));
        } else {
            switch (token[0]) {
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            }
        }
        token = strtok(0, " \t\n");
    }
    return pop();
}

//FUNCION GEMINI (es el main ya fue no es para tanto)
int main(void) {
    char infijo[MAX];
    char rpn[MAX];

    printf("Ingrese la operacion (ej: 3+4*7+3-5): ");
    gets(infijo);

    if (!validarExpresion(infijo)) {
        printf("Error: La cadena no pertenece al lenguaje.\n");
        return 1;
    }

    infijoARPN(infijo, rpn);
    printf("Notacion Polaca Inversa: %s\n", rpn);

    int resultado = calculadoraRPN(rpn);
    printf("Resultado: %d\n", resultado);

    return 0;
}

