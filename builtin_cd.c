#include "minish.h"

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
            char cwd[MAXBUF];
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
            char cwd[MAXBUF];
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
