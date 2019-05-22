#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "minish.h"

#define MAXARG 100

#define HELP_MES "Muestra calendario de mes actual" 

extern int builtin_mes(int, char**);

struct builtin_struct * buscar( char* cmd);

int status = 0;
char cwd[MAXBUF];
char promptcompleto[MAXBUF];

int builtin( int, char** );
int ejecutar( int, char** );
int isInterno( char* );

int builtin_exit( int count, char* args[] ) {
    if(count == 2) {
        exit( atoi(args[1]) );
    } else if(count == 1) {
        exit(0);
    } else {
        struct builtin_struct * nodo = buscar("exit");
        char* text = nodo->help_txt;
        printf("%s\n", text);
        return 1;

    }
}

int builtin_status( int count, char* args[]  ) {
    if (count != 1) {
        struct builtin_struct * nodo = buscar("status");
        char* text = nodo->help_txt;
        printf("%s\n", text);
        return 1;
    } else {
        printf("Estado del último comando ejecutado: %d\n", status);
        return 0;
    }
}

int builtin_help( int count, char* args[]) {
    if(count==1) {
        struct builtin_struct * nodo = buscar("help");
        printf("%s\n", nodo->help_txt);
        return 0;
    } else if(count==2) {
        struct builtin_struct * pointer = buscar(args[1]);
        if(pointer == NULL) {
            printf("No existe esa función. Escriba help para ver las disponibles.\n");
            return 1;
        } else {
            printf("%s\n", pointer->help_txt);
            return 1;
        }
    } else {
        printf("Help no admite esa cantidad de argumentos.\n");
        return 1;

    }
    return 0;
}



int builtin_pid(int count, char* args[]) {

    if(count == 1) {
        printf("Process ID: %d\n", getpid());
        return 0;
    } else {
        struct builtin_struct * nodo = buscar("pid");
        char* text = nodo->help_txt;
        printf("%s\n", text);
        return 1;
    }

}

int builtin_uid(int count, char* args[]) {

    if(count == 1) {
        int id = getuid();
        char* name = getpwuid(id)->pw_name;
        printf("User ID: %d\nUsername: %s\n", id, name);
        return 0;
    } else {
        struct builtin_struct * nodo = buscar("uid");
        char* text = nodo->help_txt;
        printf("%s\n", text);
        return 1;
    }

}

int builtin_getenv( int count, char* args[]  ) {
    if(count == 1) {
        struct builtin_struct * nodo = buscar("getenv");
        char* text = nodo->help_txt;
        printf("%s\n", text);
        return 1;
    } else {
        int i = 1;
        while(args[i] != NULL) {
            char* variable = getenv(args[i]);
            if(variable != NULL) {
                printf("%s=%s\n", args[i], variable);
            } else {
                printf("No existe la variable %s\n", args[i]);
            }
            i++;
        }
        return 0;
    }
}

int builtin_setenv( int count, char* args[] ) {
    if(count != 3) {
        struct builtin_struct * nodo = buscar("setenv");
        char* text = nodo->help_txt;
        printf("%s\n", text);
        return 1;
    } else {
        return setenv(args[1], args[2], 1);
    }
}

int builtin_cd( int count, char* args[] ) {
    if(count==1) {
        errno = 0;
        char* home = getenv("HOME");
        int estado = chdir(home);
        if(estado == -1) {
            int number = errno;
            printf( "Error en cd al cambiar a '%s': %s\n", home, strerror(number));
            return number;
        } else {
            getcwd( cwd, MAXBUF);

            snprintf( promptcompleto, MAXBUF, "minish %s > ", cwd );
            setbuf(stdout,NULL);

            return 0;
        }
    } else if(count == 2) {
        errno = 0;
        int estado = chdir(args[1]);
        if(estado == -1) {
            int number = errno;
            printf( "Error en cd al cambiar a '%s': %s\n", args[1], strerror(number));
            return number;
        } else {
            getcwd( cwd, MAXBUF);
            snprintf( promptcompleto, MAXBUF, "minish %s > ", cwd );
            setbuf(stdout,NULL);
            return 0;
        }
    } else {
        struct builtin_struct * nodo = buscar("cd");
        printf("%s", nodo->help_txt);
        return 1;
    }
}

int builtin_dir(int count, char* args[] ) {
    if(count!=1 && count!=2) {
        struct builtin_struct *  nodo = buscar("dir");
        printf("%s", nodo->help_txt);
        return 1;
    } else {
        DIR *dirp;
        struct dirent *dp;

        if ((dirp = opendir(".")) == NULL) {
            int number = errno;
            printf("Error en dir: %s\n", strerror(number));
            return number;
        }

        int modoSinFiltro = (count == 1) ? 1 : 0 ;

        errno = 0;
        char* word;
        while( (dp = readdir(dirp)) != NULL && errno == 0 ) {
            word = dp->d_name;
            if( modoSinFiltro || strstr(word, args[1])!=NULL ) {
                printf( "%s\n", word );
            }
        }
        if( errno != 0) {
            printf("Error en dir: %s\n", strerror(errno));
            return errno;
        }
        return 0;
    }
}

int builtin_history( int count, char* args[]) {
    
    int qItems;
    if(count == 1){
        qItems = 10;
    }else{
        qItems = atoi(args[1]);
    }
    printf("%s=%d\n", args[1],  qItems);
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
        return estado;
        break;
    default:
    {
        struct builtin_struct *  nodo = buscar("history");
        printf("%s", nodo->help_txt);
        return 1;
    }
    break;
    }
}

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

    char input[MAXBUF];
    char* args[MAXARG];
    int count = 0;

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
        fgets( input, MAXBUF, stdin );

        fprintf( logHistorial, "%s", input);

        count = linea2argv(input, args);
    
        /*
        printf("Cantidad de argumentos: %d\n", count);

        
        int pepe = count;
        while(pepe-->0) {
            printf("%s\n", args[pepe]);
        }
        printf("listo\n");
        */

        status = ejecutar(count, args);
    }
    return 0;
}

int ejecutar( int count, char* args[] ) {
    if( isInterno(args[0]) ) {
        //printf("%s es interno\n", args[0]);
        return builtin(count, args);
    } else {
        int id = fork();
        int statusRetorno = 0;
        if(id==0) {
            execvp( args[0], args );
            printf("Error corriendo proceso forkeado.\n");
            exit(1);
        } else if(id>0) {
            printf("Comando externo forkeado\n");
            int pid = waitpid(id, &statusRetorno, 0);
            if(pid == -1){
                printf("Error esperando al proceso hijo.\n");
                return 1;
            }
            if(WIFEXITED(status)==1){
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
    }
    return 1;
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

