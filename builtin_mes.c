#include "minish.h"
#include <time.h>

#define WIDTH 3

char* meses[] = {
    "Enero",
    "Febrero",
    "Marzo",
    "Abril",
    "Mayo",
    "Junio",
    "Julio",
    "Agosto",
    "Setiembre",
    "Octubre",
    "Noviembre",
    "Diciembre"
};

#define AMOUNT_OF_DAYS 7
char* dias[] = {
    "do",
    "lu",
    "ma",
    "mi",
    "ju",
    "vi",
    "sa"
};

int max[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void printBlanco(int largo){
    for(int i = 0; i < largo; i++){
        printf(" ");
    }
}

int builtin_mes( int count, char* argv[]  ){
    
    time_t tiempo = time(0);
//    printf("Tiempo: %ld\n", tiempo);

    struct tm* datos = localtime(&tiempo);
//    printf("Dia de mes: %d\n", datos->tm_mday);
//    printf("Mes: %d\n", datos->tm_mon);
//    printf("Año: %d\n", datos->tm_year);
//    printf("Dia de semana: %d\n", datos->tm_wday);

    char* mes = meses[datos->tm_mon];
    int year = 1900 + datos->tm_year;
    char titulo[21];
    snprintf(titulo, 21, "%s %d\n", mes, year);
    int largo = strlen(titulo);
    int largoBlanco = (21-largo)/2;
    printBlanco(largoBlanco);
    printf("%s", titulo);

    for(int i = 0; i < AMOUNT_OF_DAYS; i++){
        printf("%3s", dias[i] );
    }
    printf("\n");

    int columna = 0;

    int arrancarDesde = (datos->tm_wday)%7;
//    printf("%d. %s\n", arrancarDesde, dias[arrancarDesde]);
    
    int diaAImprimir = -arrancarDesde+1;
//    printf("Primer dia: %d", diaAImprimir);

    while(diaAImprimir<max[datos->tm_mon]+1){
        if(diaAImprimir>0){
            printf("%3d", diaAImprimir);
        }else{
            printf("%3s", "");
        }
        columna++;
        if(columna>6){
            printf("\n");
            columna = 0;
        }
        diaAImprimir++;

    }
    printf("\n");
    return 0;
}

