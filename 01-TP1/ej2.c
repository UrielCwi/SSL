#include <ctype.h>

double atof(char cadena[]){
    double val, power;
    int i, sign;
    
    for(i=0; isspace(cadena[i]); i++) //Ignora los espacios en blanco
        ;
        sign = (cadena[i] == '-') ? -1 : 1;
        
    if(cadena[i] == '+' || cadena[i] == '-')
            i++;
    for(val = 0.0; isdigit(cadena[i]); i++)
                val = 10.0 * val + (cadena[i] - '0');
    if(cadena[i] == '.')
        i++;
    for(power = 1.0; isdigit(cadena[i]); i++){
        val = 10.0 * val +(cadena[i] - '0');
        power *= 10.0;
    }
return sign * val / power;
    }


#define MAXLINE 100

int main( )
{
double sum, atof(char [ ]);
char line[MAXLINE];
int getline(char line[ ], int max);
sum= 0;
while (getline(line, MAXLINE) > 0)
printf("\t%g\n", sum += atof(line));

return 0;
}