#include "minish.h"

int externo(int count, char* args[]){
        int id = fork();
        int statusRetorno = 0;
        if(id==0) {
            execvp( args[0], args );
            printf("Error corriendo proceso forkeado en el execvp.\n");
            exit(1);
        } else if(id>0) {
            disableSigint();
            printf("Comando externo forkeado\n");
            enableSigint();
            int pid = waitpid(id, &statusRetorno, 0);
            if(pid == -1){
                printf("Error esperando al proceso hijo.\n");
                return 1;
            }
            if(WIFEXITED(statusRetorno)==1){
                int estadoFinal = WEXITSTATUS(statusRetorno);
                if( estadoFinal == 0 ){
                    printf("Comando externo terminó exitosamente con status: %d.\n", estadoFinal);
                    return estadoFinal;
                }else{
                    printf("Comando externo terminó con errores, código: %d.\n", estadoFinal);
                    return estadoFinal;
                }
        } else if(id<0) {
            int number = errno;
            printf( "Error al forkear: %s\n", strerror(number));
            return number;
        }
        return 0;
        }
        return 1;
}
