#include "minish.h"

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
