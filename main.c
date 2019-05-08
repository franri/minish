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

int main( void ){
    char* prompt = "minish> ";
    char* input[MAXLINE];
    char* args[MAXARG];
    int count = 0;
    
    while(1){
        write(2, prompt, strlen(prompt));
        read( 0, input, MAXLINE );

        count = linea2argv(input, args);
       
        while(count-->0){
            printf("%s\n", args[count]);
        }

        ejecutar(count, args);

    }

}

int ejecutar( int count, char* args[] ){
    if( isInterno(args[0]) ){
        return builtin(count, args);
    }else{
        return 
    }

}

int builtin( int count, char* args[]  ){
    for(int i=0, i<10, i++){
        if(strcmp(args[0], builtin_arr[i].cmd)){
            return builtin_arr[i].func(count, args);
        }
    }
}

int isInterno( char* comando ){
    for(int i=0, i<10, i++){
        if(strcmp(comando, builtin_arr[i].cmd)){
            return 1;
        }
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


