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

    // Preenche o array com números aleatórios
    srand(time(NULL));
    for (int i = 0; i < tam; i++) {
        list[i] = rand() % 10000000 + 1;
    }

    // Calcula o tempo de execução
    clock_t start = clock();
    bubble_sort(list, tam);
    clock_t end = clock();

    // Calcula o tempo total de execução
    double tempo_execucao = (double)(end - start) / CLOCKS_PER_SEC;

    // Exibe o tempo de execução
    printf("%.6f\n", tempo_execucao);

    // Libera a memória alocada
    free(list);

    return 0;
}

