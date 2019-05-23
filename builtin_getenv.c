#include "minish.h"


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
