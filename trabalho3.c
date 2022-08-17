//Aluno: Nicholas de Araujo 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int valor;
    struct No *proximo;
} No;

typedef struct{
    No *inicio;
} Lista;

//Cria-se uma lista e aloca-se memória para ela
Lista* gera_lista(){
    Lista *lista = (Lista*)malloc(sizeof(No));
    lista -> inicio = NULL;
    return lista;
}  

//Coloca-se um valor no final da lista
void insere_fim(Lista *lista, int valor){
    No *no;
    No *novo = (No *)malloc(sizeof(No));
    novo -> valor = valor;
    novo -> proximo = NULL;
    //Se a lista está vazia, primeiro elemento é o "valor"
    if(lista -> inicio == NULL){
        lista -> inicio = novo;
    }
    //Percorre-se a lista até ela ficar vazia para inserir o "valor"
    else{
        no = lista -> inicio;
        while(no -> proximo != NULL){
            no = no -> proximo;
        }
        no -> proximo = novo;
    }
}

int main(void){
    int i, j = 0;
    int vertices, arestas, posicao = 0, pos, valor_lido, qtd_chars;
    char *linha = NULL;
    size_t tamanho_linha = 0;

    //Leitura dos dados

    scanf("%d%d\n", &vertices, &arestas);

    Lista * vetor_adjacente[vertices + 1];

    //Gerando uma lista para cada um dos vertices
    for(int i = 1; i <= vertices; i++){
        vetor_adjacente[i] = gera_lista();
    }
    
    //Lendo cada um dos valores conectados aos vértices
    for(int i = 1; i <= vertices; i++){
        getline(&linha, &tamanho_linha, stdin);
        pos = 0, valor_lido = 0;
        while (sscanf(&linha[pos], " %d %n", &valor_lido, &qtd_chars) > 0) {
            pos += qtd_chars;
            if(strlen(linha) != 0){
                insere_fim(vetor_adjacente[i], valor_lido);
            }
        }
    }

    //Busca Topológica

    int ordem[vertices];
    int grau_entrada[vertices + 1];

    //Todas as posições de grau de entrada passam a valer 0
    for(int i = 1; i <= vertices; i++){
        grau_entrada[i]=0;
    }

    No * auxiliar;
    auxiliar = (No*) malloc(sizeof(No*));

    //Calculando o grau dos vértices
    for(int i = 1; i <= vertices; i++){
        auxiliar = vetor_adjacente[i] -> inicio;
        while(auxiliar != NULL){
            grau_entrada[auxiliar -> valor]++;
            auxiliar = auxiliar -> proximo;
        }
    }

    //Vetor ordem pega o primeiro vértice da ordenação, ou seja, o de menor grau
    for(int i = 1; i <= vertices; i++){
        if(grau_entrada[i]==0){
            ordem[posicao] = i;
            posicao++;
        }
    }

    //Vetor ordem recebe o restante dos vértices
    while( j < posicao){
        auxiliar = vetor_adjacente[ordem[j]] -> inicio;
        while(auxiliar != NULL){
            grau_entrada[auxiliar -> valor]--;
            if(grau_entrada[auxiliar -> valor] == 0){
                ordem[posicao] = auxiliar -> valor; 
                posicao++;
            } 
            auxiliar = auxiliar -> proximo;
        }
        j++;
    } 

    //Printa o vetor ordenado 
    printf("Resultado da ordenacao: \n");
    for(int i = 0; i < vertices; i++){
        printf("%d ",ordem[i]);
    }
    return 0;
}
