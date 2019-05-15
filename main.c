#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024
#define MAXARG 100

struct builtin_struct builtin_arr[] = {
  { "exit", builtin_exit, HELP_exit },
  { "pid", builtin_pid, HELP_PID },
  { "uid", builtin_uid, HELP_UID },
  { "getenv", builtin_getenv, HELP_GETENV },
  { "setenv", builtin_setenv, HELP_SETENV },
  { "cd", builtin_cd, HELP_CD },
  { "status", builtin_status, HELP_STATUS },
  { "help", builtin_help, HELP_HELP },
  { "dir", builtin_dir, HELP_DIR },
  { "history", builtin_history, HELP_HISTORY },
  { NULL, NULL, NULL }
        };

int status = 0;
char* cwd[MAX];

char promptcompleto[MAXLINE];

FILE* log;

int main( void ){

    char* input[MAXLINE];
    char* args[MAXARG];
    int count = 0;

    getcwd( cwd, MAXLINE  );

    snprintf( promptcompleto, MAXLINE, "minish %s > ", cwd );

    char* rutaLog[MAXLINE];
    snprintf(rutaLog, MAXLINE, "%s/.minish_history", getenv("HOME"));
 
    log = fopen(rutaLog, "a");
    if (!log) log = fopen(rutaLog, "w");

    while(1){

        write(2, promptcompleto, strlen(promptcompleto));
        read( 0, input, MAXLINE );
        
        fprintf( log, "%s\n", input);

        count = linea2argv(input, args);
       
        while(count-->0){
            printf("%s\n", args[count]);
        }

        status = ejecutar(count, args);
        
        if(status != 0){
            print error
        }
    }

}

int ejecutar( int count, char* args[] ){
    if( isInterno(args[0]) ){
        return builtin(count, args);
    }else{
        return externo 
    }

}

int builtin( int count, char* args[]  ){
    struct builtin_struct * pointer = builtin_arr;
    while( pointer->cmd != NULL ){
        if(strcmp(args[0], builtin_arr[i].cmd)){
            return pointer->func(count, args);
        }
        pointer++;
    }
    return NULL;
}

int builtin_history( int count, char* args[]){
    switch(count){
        case 1:

        break;
        case 2:

        break;
        default:
            char* text = buscar("history").help_txt;
            write(2, text, strlen(text));
            return 1;
        break;




    }

}

int isInterno( char* comando ){
    struct builtin_struct * pointer = builtin_arr;
    while( pointer->cmd != NULL ){
        if(strcmp(args[0], builtin_arr[i].cmd)){
            return 1;
        }
        pointer++;
    }
    return 0;
}

int linea2argv( char* input, char* argv[] ){
   int count = 0;
   char* punteroAComienzo = input;
   char* iterator = input;

   

   while( *iterator != '\n' && *iterator != '\0' ){
        if(*iterator != ' ' && *iterator != '\t'){
            iterator++;
        }
        if( *iterator == ' ' || *iterator == '\t' || *iterator == '\n' ){
            *iterator = '\0';
            argv[count] = punteroAComienzo;
            punteroAComienzo = iterator + 1;
            count++;
            iterator++;
        }
   }

   argv[count] == NULL;
   return count;
}

int builtin_exit( int count, char* args[] ){
    if(count == 2){
        return exit( atoi(args[1]) );
    }else if(count == 1){
        return exit();
    }else{
        char* text = buscar("exit").help_txt;
        write(2, text, strlen(text));
        return 1;
    {
}

int builtin_status( int count, char* args[]  ){
    if (count != 1){
        char* text = buscar("status").help_txt;
        write(2, text, strlen(text));
        return 1;
    }else{
        printf("Estado del último comando ejecutado: %d\n", status);
        return 0;
    }
}

int builtin_help( int count, char* args[]){
    switch(count){
        case 1:
           printf((*buscar("help")).help_txt); 
        break;
        case 2:
            struct builtin_struct * pointer = buscar(args[1]);
            if(pointer == NULL){
                printf("No existe esa función. Escriba help para ver las disponibles.\n");
            }else{
                printf(pointer->help_txt);
            }
        break;
        default:
            printf("Help no admite esa cantidad de argumentos.\n");        
            return 1;
        break;
        }
    return 0;
    }
}



int builtin_getpid(int count, char* args[]){

    if(count == 1){
        printf("Process ID: %d\n", getpid());
        return 0;
    }else{
        char* text = buscar("getpid").help_txt;
        write(2, text, strlen(text));
        return 1;
    {

}

int builtin_getuid(int count, char* args[]){

    if(count == 1){
        int id = getuid();
        char* name = getpwuid(id).pw_name;
        printf("User ID: %d\nUsername: %s\n", id, name);
        return 0;
    }else{
        char* text = buscar("getuid").help_txt;
        write(2, text, strlen(text));
        return 1;
    }

}

int builtin_getenv( int count, char* args[]  ){
   if(count == 1){
        char* text = buscar("getenv").help_txt;
        write(2, text, strlen(text));
        return 1;
   }else{
        int i = 1;
        while(args[i] != NULL){
            char* variable = getenv(args[i]);
            if(variable != NULL){
                printf("%s=%s\n", args[i], variable);
            }else{
                printf("No existe la variable %s\n", args[i]);
            }
        }
        return 0;
   }
}

int builtin_setenv( int count, char* args[] ){
    if(count != 3){
        char* text = buscar("setenv").help_txt;
        write(2, text, strlen(text));
        return 1;
    }else{
        return setenv(args[1], args[2], 1);
    }
}

int builtin_cd( int count, char* args[] ){
    switch(count){
        case 1:
            char* home = getenv("HOME");
            int estado = chdir(home);

            getcwd( cwd, MAXLINE  );

            strcpy(promptcompleto, prompti);
            strcat(promptcompleto, cwd);
            strcat(promptcompleto, promptf);

            return 0;
        break;
        case 2:
            int estado = chdir(args[1]);
            if(estado == -1){
                int number = errno;
                printf( "Error en cd al cambiar a '%s': %s", args[1], strerror(number));
                return number;
                }else{
                    char* olddir = cwd;
                    cwd = getcwd();
    
                    strcpy(promptcompleto, prompti);
                    strcat(promptcompleto, cwd);
                    strcat(promptcompleto, promptf);

                    return 0;
                }
        break;
        default:
            struct builtin_struct nodoCd = &buscar("cd");
            printf("%s", nodoCd.help_txt);
            return 1;
        break;
    }

}

int builtin_dir(int count, char* args[] ){
    
    switch(count){
    case 1:
        dirent* elemento;
        errno = 0;
        while( (elemento = readdir()) != NULL && errno == 0 ){
           printf( elemento.d_name );
        }
        if( errno != 0){
            printf("Error en dir: %s/n", strerror(errno));
            return errno;
        }
        return 0;
        break;
    case 2:
        dirent* elemento;
        errno = 0;
        char* word;
        while( (elemento = readdir()) != NULL && errno == 0 ){
           word = elemento.d_name;
           if(strstr(word, args[1])!=NULL){
            printf( word );
           }
        }
        if( errno != 0){
            printf("Error en dir: %s/n", strerror(errno));
            return errno;
        }
        return 0;
        break;
    default:
        struct builtin_struct nodoCd = &buscar("dir");
        printf("%s", nodoCd.help_txt);
        return 1;
        break;
    }
}   




struct builtin_struct * buscar( char* cmd){
    builtin_struct* puntero = builtin_arr;
    while( *puntero.cmd != NULL  ){
        if(strcmp(cmd, *puntero.cmd) == 0){
            return puntero;
        }
    }
    return NULL;
}
