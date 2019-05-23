#include "minish.h"

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


