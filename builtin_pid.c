#include "minish.h"

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
