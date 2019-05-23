#include "minish.h"

int builtin_status( int count, char* args[]  ) {
    if (count != 1) {
        struct builtin_struct * nodo = buscar("status");
        char* text = nodo->help_txt;
        printf("%s\n", text);
        return 1;
    } else {
        printf("Estado del último comando ejecutado: %d\n", globalstatret);
        return 0;
    }
}
