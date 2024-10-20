#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// TAD para ordenação
typedef struct {
    int *vetor;           
    int tamanho;         
    int comparacoes;     
    int trocas;          
} TAD_Ordenacao;

// Função para criar o TAD e alocar a memória
TAD_Ordenacao* criar_tad(int tamanho) {
    TAD_Ordenacao tad = (TAD_Ordenacao) malloc(sizeof(TAD_Ordenacao));  
    tad->tamanho = tamanho;  
    tad->vetor = (int*) malloc(tamanho * sizeof(int));  
    tad->comparacoes = 0;    
    tad->trocas = 0;
    return tad;  // Retorna o TAD criado
}

// Função para liberar a memória do TAD
void destruir_tad(TAD_Ordenacao *tad) {
    free(tad->vetor);  
    free(tad);         
}

// Função para configurar o vetor com valores aleatórios ou decrescentes
void configurar_vetor(TAD_Ordenacao *tad, const char *ordem) {
    if (strcmp(ordem, "aleatorio") == 0) {
        for (int i = 0; i < tad->tamanho; i++) {
            tad->vetor[i] = rand() % 100;  // Gera números aleatórios entre 0 e 99
        }
    } else if (strcmp(ordem, "decrescente") == 0) {
        for (int i = 0; i < tad->tamanho; i++) {
            tad->vetor[i] = tad->tamanho - i;  // Preenche com valores decrescentes
        }
    }
}

// Função para mostrar o vetor
void mostrar_vetor(TAD_Ordenacao *tad) {
    for (int i = 0; i < tad->tamanho; i++) {
        printf("%d ", tad->vetor[i]);  
    }
    printf("\n");
}

// Função para zerar os contadores de comparações e trocas
void zerar_contadores(TAD_Ordenacao *tad) {
    tad->comparacoes = 0;  
    tad->trocas = 0;      
}

// Algoritmo de ordenação: Bubble Sort
void bubblesort(TAD_Ordenacao *tad) {
    for (int i = 0; i < tad->tamanho - 1; i++) {
        for (int j = 0; j < tad->tamanho - i - 1; j++) {
            tad->comparacoes++;  
            if (tad->vetor[j] > tad->vetor[j + 1]) {
                // Troca os elementos
                int temp = tad->vetor[j];
                tad->vetor[j] = tad->vetor[j + 1];
                tad->vetor[j + 1] = temp;
                tad->trocas++;  
            }
        }
    }
}

// Algoritmo de ordenação: Selection Sort
void selectionsort(TAD_Ordenacao *tad) {
    for (int i = 0; i < tad->tamanho - 1; i++) {
        int min_idx = i;  
        for (int j = i + 1; j < tad->tamanho; j++) {
            tad->comparacoes++;  
            if (tad->vetor[j] < tad->vetor[min_idx]) {
                min_idx = j;  
            }
        }
        // Troca o menor elemento encontrado com o primeiro elemento
        int temp = tad->vetor[min_idx];
        tad->vetor[min_idx] = tad->vetor[i];
        tad->vetor[i] = temp;
        tad->trocas++; 
    }
}

// Algoritmo de ordenação: Insertion Sort
void insertionsort(TAD_Ordenacao *tad) {
    for (int i = 1; i < tad->tamanho; i++) {
        int key = tad->vetor[i];  
        int j = i - 1;
        while (j >= 0 && tad->vetor[j] > key) {
            tad->comparacoes++;  
            tad->vetor[j + 1] = tad->vetor[j]; 
            j--;
            tad->trocas++;  
        }
        tad->vetor[j + 1] = key;  
        tad->trocas++;  
    }
}

// Algoritmo de ordenação: Merge Sort
void merge(int *vetor, int left, int mid, int right, TAD_Ordenacao *tad) {
    int n1 = mid - left + 1;  
    int n2 = right - mid;     
    int L = (int) malloc(n1 * sizeof(int));  
    int R = (int) malloc(n2 * sizeof(int));  

    for (int i = 0; i < n1; i++) L[i] = vetor[left + i];  
    for (int j = 0; j < n2; j++) R[j] = vetor[mid + 1 + j];  

    int i = 0, j = 0, k = left;  
    while (i < n1 && j < n2) {
        tad->comparacoes++;  
        if (L[i] <= R[j]) {
            vetor[k] = L[i];  
            i++;
        } else {
            vetor[k] = R[j];  
            j++;
        }
        k++;
        tad->trocas++;  
    }

    while (i < n1) {  
        vetor[k] = L[i];
        i++;
        k++;
        tad->trocas++;  
    }

    while (j < n2) {  
        vetor[k] = R[j];
        j++;
        k++;
        tad->trocas++;
    }

    free(L);  // Libera a memória do subvetor da esquerda
    free(R);  // Libera a memória do subvetor da direita
}

void mergesort(int *vetor, int left, int right, TAD_Ordenacao *tad) {
    if (left < right) {
        int mid = left + (right - left) / 2;  
        mergesort(vetor, left, mid, tad);     
        mergesort(vetor, mid + 1, right, tad); 
        merge(vetor, left, mid, right, tad);   
    }
}

// Algoritmo de ordenação: Quick Sort
int partition(int *vetor, int low, int high, TAD_Ordenacao *tad) {
    int pivot = vetor[high];  
    int i = (low - 1);  

    for (int j = low; j < high; j++) {
        tad->comparacoes++;  
        if (vetor[j] <= pivot) {
            i++;  
            int temp = vetor[i];  
            vetor[i] = vetor[j];
            vetor[j] = temp;
            tad->trocas++; 
        }
    }
    int temp = vetor[i + 1];  
    vetor[i + 1] = vetor[high];
    vetor[high] = temp;
    tad->trocas++;  
    return i + 1;   
}

void quicksort(int *vetor, int low, int high, TAD_Ordenacao *tad) {
    if (low < high) {
        int pi = partition(vetor, low, high, tad);  
        quicksort(vetor, low, pi - 1, tad);         
        quicksort(vetor, pi + 1, high, tad);        
    }
}

// Algoritmo de ordenação: Heap Sort
void heapify(int *vetor, int n, int i, TAD_Ordenacao *tad) {
    int largest = i;  
    int left = 2 * i + 1;  
    int right = 2 * i + 2; 

    if (left < n) {
        tad->comparacoes++;  
        if (vetor[left] > vetor[largest]) {
            largest = left;  
        }
    }

    if (right < n) {
        tad->comparacoes++;  
        if (vetor[right] > vetor[largest]) {
            largest = right;  
        }
    }

    if (largest != i) {
        int temp = vetor[i];  
        vetor[i] = vetor[largest];
        vetor[largest] = temp;
        tad->trocas++; 
        heapify(vetor, n, largest, tad);  
    }
}

void heapsort(TAD_Ordenacao *tad) {
    int n = tad->tamanho;

    // Constrói um heap máximo
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(tad->vetor, n, i, tad);
    }

    // Um a um extrai os elementos do heap
    for (int i = n - 1; i > 0; i--) {
        int temp = tad->vetor[0];  
        tad->vetor[0] = tad->vetor[i];
        tad->vetor[i] = temp;
        tad->trocas++;  
        heapify(tad->vetor, i, 0, tad);  
    }
}

// Função para contar e ordenar usando Counting Sort
void countingsort(TAD_Ordenacao *tad) {
    int max = tad->vetor[0];
    for (int i = 1; i < tad->tamanho; i++) {
        if (tad->vetor[i] > max) max = tad->vetor[i];  
    }

    int count = (int) calloc(max + 1, sizeof(int));  
    for (int i = 0; i < tad->tamanho; i++) {
        count[tad->vetor[i]]++;  
    }

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            tad->vetor[index++] = i;  
            count[i]--;
            tad->trocas++;  
        }
    }

    free(count);  // Libera memória
}

// Função principal
int main() {
    srand(time(NULL));  
    int opcao, tamanho;
    char ordem[20], algoritmo[20];

    // Menu de opções
    printf("Escolha a quantidade de valores:\n");
    printf("1. 10\n2. 100\n3. 1000\n4. 10000\n");
    scanf("%d", &opcao);
    
    // Define o tamanho com base na escolha do usuário
    if (opcao == 1) tamanho = 10;
    else if (opcao == 2) tamanho = 100;
    else if (opcao == 3) tamanho = 1000;
    else if (opcao == 4) tamanho = 10000;

    TAD_Ordenacao *tad = criar_tad(tamanho);  

    // Escolha da ordem do vetor
    printf("Escolha a ordem do vetor (aleatorio/decrescente):\n");
    scanf("%s", ordem);
    configurar_vetor(tad, ordem);  // Configura o vetor

    // Exibe o vetor antes da ordenação
    printf("Vetor antes da ordenação:\n");
    mostrar_vetor(tad);
    
    printf("Escolha o algoritmo de ordenação:\n");
    printf("1. Bubblesort\n2. Selectionsort\n3. Insertionsort\n");
    printf("4. Mergesort\n5. Quicksort\n6. Heapsort\n");
    printf("7. Countingsort\n");
    scanf("%s", algoritmo);

    // Zera os contadores
    zerar_contadores(tad);

    clock_t inicio = clock();  // Marca o tempo de início da ordenação


    if (strcmp(algoritmo, "1") == 0) {
        bubblesort(tad);
    } else if (strcmp(algoritmo, "2") == 0) {
        selectionsort(tad);
    } else if (strcmp(algoritmo, "3") == 0) {
        insertionsort(tad);
    } else if (strcmp(algoritmo, "4") == 0) {
        mergesort(tad->vetor, 0, tad->tamanho - 1, tad);
    } else if (strcmp(algoritmo, "5") == 0) {
        quicksort(tad->vetor, 0, tad->tamanho - 1, tad);
    } else if (strcmp(algoritmo, "6") == 0) {
        heapsort(tad);
    } else if (strcmp(algoritmo, "7") == 0) {
        countingsort(tad);
    }

    clock_t fim = clock();  // Marca o tempo de fim da ordenação
    double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;  // Calcula o tempo de execução

    printf("Vetor ordenado:\n");
    mostrar_vetor(tad);
    printf("Tempo de execução: %f segundos\n", tempo_execucao);
    printf("Número de comparações: %d\n", tad->comparacoes);
    printf("Número de trocas: %d\n", tad->trocas);

    destruir_tad(tad); 
    return 0;  
}
