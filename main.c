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

        int status = ejecutar(count, args);
        
        if(status != 0){
            print error
        }
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

struct builtin_struct * buscar( char* cmd){
    builtin_struct* puntero = builtin_arr;
    while( *puntero.cmd != NULL  ){
        if(strcmp(cmd, *puntero.cmd) == 0){
            return puntero;
        }
    }
    return NULL;
}
