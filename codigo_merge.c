#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Função Merge Sort
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Divide o array em duas metades
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // Mescla as duas metades
        int n1 = mid - left + 1;
        int n2 = right - mid;
        int L[n1], R[n2];

        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
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
        list[i] = rand() % 10000000 + 1;
    }

    // Calcula o tempo de execução
    clock_t start = clock();
    merge_sort(list, 0, tam - 1); 
    clock_t end = clock();


    double tempo_execucao = (double)(end - start) / CLOCKS_PER_SEC;


    printf("%.6f\n", tempo_execucao);

    free(list);

    return 0;
}

