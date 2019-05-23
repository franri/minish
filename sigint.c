#include "minish.h"


void handler(int signum){
    printf("\n");
    // setbuf(stdout, NULL);
    return;
}

void enableSigint(){
    struct sigaction act;
    if(sigaction(SIGINT, NULL, &act) == -1){
        int number = errno;
        printf("Error getteando struct original de SIGINT. Detalle: %s.\n", strerror(number));
        return;
    }else{
        act.sa_handler = handler;
        if(sigaction(SIGINT, &act, NULL) == -1){
            int number = errno;
            printf("Error setteando nuevo struct para SIGINT. Detalle: %s.\n", strerror(number));
            return;
        }else{
            printf("Cambio de reacción frente a SIGINT exitoso.\n");
            return;
        }
    }
}
    
void disableSigint(){
    struct sigaction act;
    if(sigaction(SIGINT, NULL, &act) == -1){
        int number = errno;
        printf("Error getteando struct original de SIGINT. Detalle: %s.\n", strerror(number));
        return;
    }else{
        act.sa_handler = SIG_DFL;
        if(sigaction(SIGINT, &act, NULL) == -1){
            int number = errno;
            printf("Error setteando nuevo struct para SIGINT. Detalle: %s.\n", strerror(number));
            return;
        }else{
           printf("Reacción frente a SIGINT devuelta al por defecto.\n");
            return;
        }
    }
}

