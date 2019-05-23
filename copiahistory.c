#include "minish.h"

int builtin_history( int count, char* args[]) {

    char rutaLog[MAXBUF];
    snprintf(rutaLog, MAXBUF, "%s/.minish_history", getenv("HOME"));


    int parsedNumber = atoi(args[1]);
    int qItems = (count == 1)? 10 : parsedNumber;
    char* items[qItems];
    char* line = malloc(MAXBUF);
    FILE* historial = fopen ( rutaLog, "r" );

    char* text;

    int estado = 6;
    int current = 0;
    int isFull = 0;

    switch(count) {
    case 1:
    case 2:
        //voy a llenarlo circulamente e imprimir de mas viejo a mas nuevo


        while( fgets( line, MAXBUF, historial ) != NULL) {
            items[current++] = line;
            if(current > qItems-1) {
                current = 0;
                isFull = 1;
            } //vuelvo al comienzo si me paso
        }

        //ahora imprimo
        //primero chequeo si hay suficientes comandos en historial
        if(isFull) {
            int toPrint = current+1;
            while(current!=toPrint) {
                printf("%s\n", items[toPrint++]);
                toPrint = (toPrint > qItems-1)? 0 : toPrint; //vuelvo al comienzo si me paso
            }
            estado = 0;
        } else { //hay pocos comandos
            int i = 0;
            while( items[i] != NULL) {
                printf("%s\n", items[i]);
                i++;
            }
            estado = 0;
        }
    }
