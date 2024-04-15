#include <stdio.h>  
#include <string.h>

#define TAMANHO_MAXIMO (10000)
#define TAMANHO_PALAVRA (50)

void merge(char palavra[TAMANHO_MAXIMO][TAMANHO_PALAVRA], int esq, int mid, int dir, int *passos) {
    int i, j, k;
    int a = mid - esq + 1;
    int b = dir - mid;

    char L[a][TAMANHO_PALAVRA];
    char R[b][TAMANHO_PALAVRA];

    for (i = 0; i < a; i++)
        strcpy(L[i], palavra[esq + i]);
    for (j = 0; j < b; j++)
        strcpy(R[j], palavra[mid + 1 + j]);

    i = 0;
    j = 0;
    k = esq;

    while (i < a && j < b) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(palavra[k], L[i]);
            i++;
        } else {
            strcpy(palavra[k], R[j]);
            j++;
        }
        k++;
        (*passos)++;
    }

    while (i < a) {
        strcpy(palavra[k], L[i]);
        i++;
        k++;
    }

    while (j < b) {
        strcpy(palavra[k], R[j]);
        j++;
        k++;
    }
}

void mergesort(char palavra[TAMANHO_MAXIMO][TAMANHO_PALAVRA], int esq, int dir, int *passos) {
    if (esq < dir) {
        int mid = esq + (dir - esq) / 2;
        mergesort(palavra, esq, mid, passos);
        mergesort(palavra, mid + 1, dir, passos);
        merge(palavra, esq, mid, dir, passos);
    }
}

void Insertion_Sort(char array[TAMANHO_MAXIMO][TAMANHO_PALAVRA], int tam, int *count) {
    *count = 0;
    for(int i = 1; i < tam; i++) {
        int j = i; 
        char temp[TAMANHO_PALAVRA];

        while (j > 0 && strcmp(array[j], array[j - 1]) < 0) {
            strcpy(temp, array[j]);
            strcpy(array[j], array[j - 1]);
            strcpy(array[j - 1], temp);
            j--;
            (*count)++;
        }
    }
}

int main(void) {
    FILE *in, *out1, *out2;
    char palavras[TAMANHO_MAXIMO][TAMANHO_PALAVRA];
    int tamanho = 0;
    int count = 0;
    int passos = 0;
    char palavra[TAMANHO_PALAVRA];

    in = fopen("arquivo.txt", "r");

    if(in == NULL) {
        printf("Erro ao abrir in.\n");
        return 1;
    }

    while(fscanf(in, "%s", palavra) != EOF && tamanho < TAMANHO_MAXIMO) {
        strcpy(palavras[tamanho], palavra);
        tamanho++;
    }

    Insertion_Sort(palavras, tamanho, &count);
    mergesort(palavras, 0, tamanho - 1, &passos);

    out1 = fopen("out1.txt", "w"); //Criando novo arquivo para colocar as palabras ordenadas InsertionSort
    out2 = fopen("out2.txt", "w"); //Criando novo arquivo para colocar as palavras ordenadas mergeSort

    if(out1 == NULL) {
        printf("Erro ao abrir o arquivo de destino"); //Caso de erro
    }

    if(out2 == NULL) {
        printf("Erro ao abrir o arquivo de destino"); //Caso de erro
    }

    for(int i = 0; i < tamanho; i++) {
        fputs(palavras[i], out1);
        fputc('\n', out1);
    }

    for(int i = 0; i < tamanho; i++) {
        fputs(palavras[i], out2);
        fputc('\n', out2);
    }

    fclose(in);
    fclose(out1);
    fclose(out2);

    printf("Número de passos Insertion Sort: %d\n", count);
    printf("Número de passos Merge Sort: %d", passos);

    return 0;
}