#include "funcoes.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

int Procura_Num(int TAM_BaseX, char **BaseX, char c){
    int j;
    for(j=0; j<TAM_BaseX; j++){
        if(BaseX[j][0] == c)
            return j;
    }
    return -1;
}

void trataNum (char str[], int a, int TAM_BaseX, char **BaseX) {
    int i, j, bases[2], expoente, procurado;
    double soma=0;
    for (i=1; str[i]!=' '; i++);
    int aux=i;
    for (j=0; j<2; j++) {
        i++;
        if (str[i] == '1') {
            bases[j]=str[i+1] - '0' + 10;
        }else if(str[i] == '-'){
            bases[j] = -1;
        }
        else {
            bases[j]=str[i] - '0';
        }
        for (; str[i]!=' '; i++);
    }
    for (j=aux; str[j]!='.'; j--);
    if(bases[0] != -1){
        for (i=j-1; i>=1; i--) {
            if (str[i] > '9') {
                soma+=(str[i]-'0'-7)*pow(bases[0],j-1-i);
            } else {
                soma+=(str[i]-'0')*pow(bases[0],j-1-i);
            }
        }
        for (i=j+1; i<aux; i++) {
            if (str[i] > '9') {
                soma+=(str[i]-'0'-7)*pow(bases[0],j-i);
            } else {
                soma+=(str[i]-'0')*pow(bases[0], j-i);
            }
        }
    }else{
        for(i=j-1, expoente = 0; i>=1; i--){
            procurado = Procura_Num(TAM_BaseX, BaseX, str[i]);
            if(procurado != -1)
                soma+=(procurado)*pow(TAM_BaseX, expoente++);
        }
        for(i=j+1, expoente = -1; i<aux; i++){
            procurado = Procura_Num(TAM_BaseX, BaseX, str[i]);
            if(procurado != -1)
                soma+=(procurado)*pow(TAM_BaseX, expoente--);
        }
    }
    if (str[0] == '-') {
        soma*=-1;
    }
    numeros[a][0]=soma;
    numeros[a][1]=bases[1];
}

void converteNum (FILE *saida, double v[], int TAM_BaseX, char **BaseX) {
    int i, T;
    char str[192], mat[192][10];
    if (v[0]<0) {
        fprintf(saida, "-");
        v[0]*=-1;
    } else {
        fprintf(saida, "+");
    }
    int parte_inteira=floor(v[0]);
    float parte_decimal=v[0]-parte_inteira;
    if(v[1] != -1){
        for (i=0; parte_inteira>=v[1]; i++, parte_inteira/=(int)v[1]) {
            str[i]=(parte_inteira%((int)v[1]))+'0';
            if (str[i] > '9') {
                str[i]+=7;
            }
        }
        str[i]=parte_inteira+'0';
        if (str[i] > '9') {
            str[i]+=7;
        }
        for (; i>=0; i--) {
            fprintf(saida, "%c", str[i]);
        }
        fprintf(saida, ".");
    }else{
        for(i = 0; parte_inteira>=TAM_BaseX; i++, parte_inteira/=(int)TAM_BaseX){
            sprintf(mat[i], "%s", (BaseX[(parte_inteira%TAM_BaseX)]));
        }
        for (; i>=0; i--) fprintf(saida, "%s", mat[i]);
    }
    if(v[1] != -1){
        for (i=-1; parte_decimal != 0.0; i--) {
            T=parte_decimal*(int)v[1];
            if (T>9) {
                fprintf(saida, "%c", T+'0'+7);
            } else {
                fprintf(saida, "%d", T);
            }
            parte_decimal = (parte_decimal*(int)v[1]) - T;
        }
    }else{
        for(i=-1; parte_decimal != 0.0; i--){
            T=parte_decimal*TAM_BaseX;
            fprintf(saida, "%s", BaseX[T]);
            parte_decimal = (parte_decimal*TAM_BaseX) - T;
        }
    }
    fprintf(saida, "\n");
}
