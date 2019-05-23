#include "minish.h"

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
