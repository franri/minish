#include "minish.h"


int globalstatret;
char promptcompleto[MAXBUF];

int builtin( int, char** );
int isInterno( char* );
int ejecutar(int, char**);


struct builtin_struct builtin_arr[] = {
    { "exit", builtin_exit, HELP_EXIT },
    { "pid", builtin_pid, HELP_PID },
    { "uid", builtin_uid, HELP_UID },
    { "getenv", builtin_getenv, HELP_GETENV },
    { "setenv", builtin_setenv, HELP_SETENV },
    { "cd", builtin_cd, HELP_CD },
    { "status", builtin_status, HELP_STATUS },
    { "help", builtin_help, HELP_HELP },
    { "dir", builtin_dir, HELP_DIR },
    { "history", builtin_history, HELP_HISTORY },
    { "mes", builtin_mes, HELP_MES},
    { NULL, NULL, NULL }
};


int main( void ) {

    enableSigint();

    char input[MAXBUF];
    char* args[MAXARG];
    int count = 0;

    globalstatret = -999;

    char cwd[MAXBUF];
    getcwd( cwd, MAXBUF);

    snprintf( promptcompleto, MAXBUF, "minish %s > ", cwd );
    setbuf(stdout,NULL);

    char rutaLog[MAXBUF];
    char* myhomedir = getenv("HOME");
    snprintf(rutaLog, MAXBUF, "%s/.minish_history", myhomedir);
    setbuf(stdout,NULL);

    FILE *logHistorial = fopen(rutaLog, "a+");

    while(1) {

        write(2, promptcompleto, strlen(promptcompleto));
        // read( 0, input, MAXBUF );
      
        char* p;
        do{
        p = fgets( input, MAXBUF, stdin );
        if( p == NULL){
            errno = 0;
            break;
        }
        }while( errno == EINTR);
        
        if( p == NULL){
            continue;
        }

        fprintf( logHistorial, "%s", input);
        fflush( logHistorial );

        count = linea2argv(input, args);
    
        /*
        printf("Cantidad de argumentos: %d\n", count);

        
        int pepe = count;
        while(pepe-->0) {
            printf("%s\n", args[pepe]);
        }
        printf("listo\n");
        */

        globalstatret = ejecutar(count, args);

    }
    return 0;
}

int ejecutar( int count, char* args[] ) {
    if( isInterno(args[0]) ) {
        //printf("%s es interno\n", args[0]);
        return builtin(count, args);
    } else {
        return externo(count, args);
    }
}


int isInterno( char* comando ) {
    struct builtin_struct * pointer = builtin_arr;
    while( pointer->cmd != NULL ) {
        if(strcmp(comando, pointer->cmd)==0) {
            return 1;
        }
        pointer++;
    }
    return 0;
}

int builtin( int count, char* args[]  ) {
    struct builtin_struct * pointer = builtin_arr;
    int resultado;
    while( pointer->cmd != NULL ) {
        if(strcmp(args[0], pointer->cmd)==0) {
            resultado = (pointer->func)(count, args);
            return resultado;
        }
        pointer++;
    }
    return 4;
}


struct builtin_struct * buscar( char* cmd) {
    struct builtin_struct* puntero = builtin_arr;
    while( puntero->cmd != NULL  ) {
        if(strcmp(cmd, puntero->cmd) == 0) {
            return puntero;
        }
        puntero++;
    }
    return NULL;
}

int linea2argv( char* input, char* argv[] ) {
    int count = 0;
    char* punteroAComienzo = input;
    char* iterator = input;

    while( *iterator != '\n' && *iterator != '\0' ) {
        if(*iterator != ' ' && *iterator != '\t') {
            iterator++;
        }
        if( *iterator == ' ' || *iterator == '\t' || *iterator == '\n' ) {
            *iterator = '\0';
            argv[count] = punteroAComienzo;
            punteroAComienzo = iterator + 1;
            count++;
            iterator++;
        }
    }

    argv[count] = NULL;
    return count;
}

