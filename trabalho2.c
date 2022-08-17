//Aluno: Nicholas de Araujo

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Crio o struct nó da inicio. É definido o tipo de dado e para onde cada nó aponta.
typedef struct no{
    float valor;
    struct no *proximo;
}No;

//É feito o processo empilhar a pilha
No* push(No *inicio, float numero){
    No *novo;
    novo = malloc(sizeof(No));

    if(novo){
        novo->valor = numero;
        novo->proximo = inicio;
        return novo;
    }
    else
        printf("\nNao foi possivel alocar memoria!\n");
    return NULL;
}

//É feito o processo de desempilhar a pilha
No* pop(No **inicio){
    No *remover;
    remover = NULL;

    if(*inicio){
        remover = *inicio;
        *inicio = remover->proximo;
    }
    else
        printf("\nA pilha está vazia!\n");
    return remover;
}
//Vai pegar os operandos e operadores e fazer as devidas operações
float operacao(float x, float y, char z){

    if (z == '+'){
        return x + y;
    }
    else if (z == '-'){
        return x - y;
    }
    else if (z == '*'){
        return x * y;
    }
    else if (z == '/'){ 
        return x/y;
    }
    else if (z == '^'){
        return pow(x,y);
    }
}

float calcular(char x[]){
    char *pt;
    float numero;
    No *numero1, *numero2, *inicio = NULL;

    //Função para quebrar um string sempre que houver um espaço.
    pt = strtok(x, " ");
    //Enquanto pt for diferente de nulo, vai verificar se é um sinal e passar a desempilhar números para fazer
    //as devidas operações.
    while(pt != NULL){
        if(pt[0] == '+' || pt[0] == '-' || pt[0] == '/' || pt[0] == '*' || pt[0] == '^'){
            numero1 = pop(&inicio);
            numero2 = pop(&inicio);
            numero = operacao(numero2->valor, numero1->valor, pt[0]);
            inicio = push(inicio, numero);
            free(numero1);
            free(numero2);
        }
        else{
            //Função para converter a parte numerica da string para inteiro e o resto deixa em string.
            //O 10 é devido a base decimal.
            numero = strtol(pt, NULL, 10);
            inicio = push(inicio, numero);
        }
        pt = strtok(NULL, " ");
    }
    numero1 = pop(&inicio);
    numero = numero1->valor;
    free(numero1);
    return numero;
}

//A main simplesmente pede para você inserir a expressão que deseja calcular seguindo essa regra como pedida.
int main(){

    char expressao[1000];
    printf("\nEsse codigo resolve a expressao no formato notacao polonesa reversa. São aceitos +, -, *, / e ^.\n");
    printf("\nEx.: 3 4 5 + ^ vai dar 3**9 que vale 19683.\n\n");
    scanf("%[^\n]", expressao);
    
    printf("Resultado de %s: ", expressao);
    printf("%.4f\n", calcular(expressao));
    return 0;
}
