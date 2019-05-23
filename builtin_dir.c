#include "minish.h"

#define TEMPCOSO 15

void ordenar( int, char**);
void freeLista(char**, int);

int builtin_dir(int count, char* args[] ) {
    if(count!=1 && count!=2) {
        struct builtin_struct *  nodo = buscar("dir");
        printf("%s", nodo->help_txt);
        return 1;
    } else {
        DIR *dirp;
        struct dirent *dp;

        if ((dirp = opendir(".")) == NULL) {
            int number = errno;
            printf("Error en dir: %s\n", strerror(number));
            return number;
        } else {

            int modoSinFiltro = (count == 1) ? 1 : 0 ;

            errno = 0;
            char* word;
            int contador = 0;
            int cantidadInicial = 10;
            int limite = cantidadInicial;
            char** lista = malloc(sizeof(char*)*100);
            while( (dp = readdir(dirp)) != NULL && errno == 0 ) {
                word = dp->d_name;
                if( modoSinFiltro || strstr(word, args[1])!=NULL ) {
                    if(contador == limite) {
                        int newLimite = limite + cantidadInicial;
                        char** newLista = realloc( lista, (sizeof(char*))*newLimite );
                        if( newLista ) {
                            lista = newLista;
                            limite = newLimite;
                            lista[contador++] = strdup(word);
                        } else {
                            printf("Error redimensionando, indtente más tarde.\n");
                            freeLista(lista, limite);
                            return 1;
                        }
                    } else {
                        lista[contador++] = strdup(word);
                    }
                }
            }
            if( errno != 0) {
                printf("Error en dir: %s\n", strerror(errno));
                return errno;
            }
            ordenar( contador, lista );
            while( contador-- > 0 ) {
                printf("%s\n", lista[contador]);
            }
            freeLista(lista, limite);
            return 0;
        }
        return 1;
    }
}

void freeLista(char** lista , int limite) {
    for(int i = 0; i < limite; i++) {
        free(lista[i]);
    }
    free(lista);
}

void ordenar( int contador, char** lista ) {

    int n = contador - 1;

   for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1-i; j++ ){
            if( strcasecmp( lista[j], lista[j+1] ) < 0  ){
            char* temp;
            temp = lista[j];
            lista[j] = lista[j+1];
            lista[j+1] = temp;
            }
        }
    }
    return;
}
