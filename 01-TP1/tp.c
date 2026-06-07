//TESTING, NO TOCAR (a menos que quieran hacer el tp no)

#include <stdio.h>
#include <ctype.h>
int i = 0;

int verifica(char s[])
{
    int h;
    for(h=0;s[h];h++)
    {
        if(!(s[h]=='+'||s[h]=='-'||isdigit(s[h])||s[h]=='*'))
        {
            return 0;
        }
    }
    return 1;
}

int atoi (char s[]){ //LIBRO DE DANI RICHI O COMO SE LLAME
    int n = 0, sign = 1;
    while (isspace(s[i])) { 
        i++; 
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') i++; // ignora el signo
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

int atoi2 (char s[]){
    int numero = 0;
    i = 0; // Reiniciar el índice
    if(!verifica(s))
    {
        printf("HAY CARACTERES QUE NO PERTENECEN AL ALFABETO \n");
        return 0;
    }
    numero = atoi(s);
    while(s[i] != '\0')
    {
        if (s[i] == '*')
        {
            i++;
            numero = numero * atoi(s);
        } 
        else if (s[i] == '+' || s[i] == '-') 
        {
            numero = numero + atoi(s);
        }
        else
        {
            i++; 
        }
    }
    return numero;
}


int columna(int c)
{
    switch(c)
    {
        case '+':
            return 1;
        case '-':
            return 2;
        default:
            return 0;
    }
}
int esPalabra(char s[])
{
    static int tt[4][3]={
                          { 2,1,1 },
                          { 2,3,3 },
                          { 2,3,3 },
                          { 3,3,3 },
                        };
    int e = 0;
    int i = 0;
    int c = s[0];
    while(c!='\0')
    {
        e = tt[e][columna(c)];
        c = s[i++];
    }
    if(e==2)
        return 1;
    return 0;
}



/*int main()
// Dada una cadena que contenga varios números que pueden ser decimales, octales o hexadecimales, con o sin signo para
// el caso de los decimales, separados por el carácter ‘@’ , reconocer los tres grupos de constantes enteras, indicando si
// hubo un error léxico , en caso de ser correcto contar la cantidad de cada grupo.
{
    char palabra[]="g98+5652";
    //verificar si todos los caracteres 
    //pertenecen al alfabeto
    if(!verifica(palabra))
    {
        printf("HAY CARACTERES QUE NO PERTENECEN AL ALFABETO");
    }
    else
    {
        if(esPalabra(palabra))
        {
            printf("se reconoce");
        }
        else
        {
            printf("no se reconoce");
        }
    }
    return 0;
}*/

int main(){
    char palabra[]="5656+52*50000";
    printf("%d",atoi2(palabra));
    return 0;
}