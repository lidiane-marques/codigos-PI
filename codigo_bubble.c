#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Função Bubble Sort
void bubble_sort(int list[], int len) {
    int aux;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - 1; j++) {
            if (list[j] > list[j + 1]) {
                aux = list[j];
                list[j] = list[j + 1];
                list[j + 1] = aux;
            }
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Uso: %s <tamanho_do_array>\n", argv[0]);
        return 1;
    }

    int tam = atoi(argv[1]);

    if (tam <= 0) {
        printf("Erro: O tamanho do array deve ser maior que 0.\n");
        return 1;
    }

    int *list = malloc(tam * sizeof(int));
    if (list == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

  
    srand(time(NULL));
    for (int i = 0; i < tam; i++) {
        list[i] = rand() % 99 + 1;
    }

    
    clock_t start = clock();
    bubble_sort(list, tam);
    clock_t end = clock();

    
    double tempo_execucao = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%.6f\n", tempo_execucao);

 
    free(list);

    return 0;
}

