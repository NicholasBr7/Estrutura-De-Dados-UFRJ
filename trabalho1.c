//Aluno: Nicholas de Araujo Figueira
//DRE: 121 088 218

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//Algoritmo do Bubble Sort
void bubble_sort(int array[], int tamanho) {

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
        if (array[j] > array[j + 1]) {
        
            int temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
        }
    }
}
    for (int k = 0; k < tamanho; k++) {
        printf("%d  ", array[k]);
    }
    printf("\n");
free(array);
}

//Algoritmo para realizar a ordenação com merge sort
int merge(int *array, int inicio, int meio, int fim){

    int *temp, esquerda = 0, direita = 0, tamanho = 0, k, j;
    int fim1 = 0, fim2 = 0;
    tamanho = (fim - inicio) + 1;
    esquerda = inicio;
    direita = meio + 1;
    temp = (int *) malloc(tamanho * sizeof(int));
    if(temp != NULL){
        for(int i = 0; i < tamanho; i++){
            if(!fim1 && !fim2){
                if(array[esquerda] < array[direita]){
                    temp[i] = array[esquerda++];
                }
                else{
                    temp[i] = array[direita++];
                }
                if(esquerda > meio){
                    fim1 = 1;
                }
                if(direita > fim){
                    fim2 = 1;
                }
            }
            else{
                if(!fim1){
                    temp[i] = array[esquerda++];
                }
                else{
                    temp[i] = array[direita++];
                }
            }
        }
        for(j = 0, k = inicio; j < tamanho; j++, k++){
            array[k] = temp[j];
        }
    }
    free(temp);
    return 0;
}
//Algoritmo para, recursivamente, ir partindo o array
int merge_sort(int *array, int inicio, int fim){

    int meio = 0;
    if(inicio < fim){
        meio = floor((inicio + fim) / 2);
        merge_sort(array, inicio, meio);
        merge_sort(array, meio + 1, fim);
        merge(array, inicio, meio, fim);
    }
    return 0;
}

//Serve para fazer troca do conteúdo do inteiro. É usado na funçao particionar para fazer
//as trocas depois de comparar com o pivô.
void trocar(int *a, int *b) {
  int c = *a;
  *a = *b;
  *b = c;
}
//Irá fazer as devidas trocas de posição quando realizar a comparação do pivô e do elemento.
int particionar(int array[], int inicio, int fim) {
    
    int pivo = array[fim];
    int a = (inicio - 1);
    for (int i = inicio; i < fim; i++) {
        if (array[i] <= pivo) {
        a++;
        trocar(&array[a], &array[i]);
    }
}
    trocar(&array[a + 1], &array[fim]);
    return (a + 1);
}
//Algorimo para determinar a posição dos elementos com base no pivô.
//Menores do que o pivô, vão para a esquerda dele e maiores, para a direita.
void quick_sort(int array[], int inicio, int fim) {

    if (inicio < fim) {
    int pivo = particionar(array, inicio, fim);
    quick_sort(array, inicio, pivo - 1);
    quick_sort(array, pivo + 1, fim);
  }
}

//Chama as funções, lê os argumentos e registra o tempo.
int main(int argc, char *argv[]) {

    int quantidade;
    
    double tempo;

    quantidade = atoi(argv[2]);

    int array[quantidade];

    srand(0); srand(time(NULL));

    for (int j = 0; j < atoi(argv[2]); j++){
        array[j] = rand() % 1000;
    }
    int tamanho = sizeof(array)/sizeof(array[0]);

    printf("\nElementos do array: \n");

    for (int k = 0; k < tamanho; k++){
        printf("%d  ", array[k]);
    }

    int fim = sizeof(array);

    if (!strcmp(argv[1], "-b") || !strcmp(argv[1], "-B") ){
        printf("\n\nAlgoritmo ordenado com o Bubble sort:\n");
        tempo = clock();
        bubble_sort(array, tamanho);
        tempo = clock() - tempo;
        printf("\nTempo gasto: %.6fs\n", (tempo)/((CLOCKS_PER_SEC)));

    } else if (!strcmp(argv[1], "-m") || !strcmp(argv[1], "-M")){
        printf("\n\nAlgoritmo ordenado com o Merge sort:\n");
        tempo = clock();
        merge_sort(array, 0, tamanho);
        for(int i = 0; i < tamanho; i++){
            printf("%d  ", array[i]);
        }
        printf("\n");
        tempo = clock() - tempo;
        printf("\nTempo gasto: %.6fs\n", (tempo)/((CLOCKS_PER_SEC)));

    } 
    else if (!strcmp(argv[1], "-q") || !strcmp(argv[1], "-Q")) {
        printf("\n\nAlgoritmo ordenado com o Quick sort:\n");
        tempo = clock();
        quick_sort(array, 0, tamanho - 1);
        for(int i = 0; i < tamanho; i++){
            printf("%d  ", array[i]);
        }
        printf("\n");
        tempo = clock() - tempo;
        printf("\nTempo gasto: %.6fs\n", (tempo)/((CLOCKS_PER_SEC)));

    }
    else{
        printf("\n\nPrecisa inserir um parametro valido no argv[1]. Eh aceito -b, -B, -m, -M, -q, -Q.\n");
    }
}
