#include "minish.h"

int builtin_uid(int count, char* args[]) {

    if(count == 1) {
        int id = getuid();
        char* name = getpwuid(id)->pw_name;
        printf("User ID: %d\nUsername: %s\n", id, name);
        return 0;
    } else {
        struct builtin_struct * nodo = buscar("uid");
        char* text = nodo->help_txt;
        printf("%s\n", text);
        return 1;
    }

}
