#include "minish.h"

int builtin_history( int count, char* args[]) {
    
    int qItems;
    if(count == 1){
        qItems = 10;
    }else{
        qItems = atoi(args[1]);
    }
    char* items[qItems];
    char line[MAXBUF];

    char rutaLog[MAXBUF];
    snprintf(rutaLog, MAXBUF, "%s/.minish_history", getenv("HOME"));
    setbuf(stdout, NULL);

    FILE *logHistorial = fopen(rutaLog, "r");
    

    int estado = 6;
    int current = 0;
    int isFull = 0;

    switch(count) {
    case 1:
    case 2:
        //voy a llenarlo circulamente e imprimir de mas viejo a mas nuevo

        while( fgets(line, MAXBUF, logHistorial) != NULL ) {
            items[current] = strdup(line);
            if(current >= qItems-1) {
                current = 0;
                isFull = 1;
            }else{
                current++;
            }
            //vuelvo al comienzo si me paso
        }

        //ahora imprimo
        //primero chequeo si hay suficientes comandos en historial
        if(isFull) {
            int toPrint = current;
            do {
                printf("%s", items[toPrint]);
                toPrint = (toPrint >= qItems-1)? 0 : toPrint+1; //vuelvo al comienzo si me paso
            }while(current!=toPrint);
            estado = 0;
        } else { //hay pocos comandos
            int i=0;
            while( i < current ) {
                printf("%s", items[i]);
                i++;
            }
            estado = 0;
        }
        fclose(logHistorial);
        return estado;
        break;
    default:
    {
        struct builtin_struct *  nodo = buscar("history");
        printf("%s", nodo->help_txt);
        fclose(logHistorial);
        return 1;
    }
    break;
    }
}
