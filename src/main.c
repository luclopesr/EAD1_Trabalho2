#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função para realizar ação com arquivo
//Passa nome do arquivo e oq deseja fazer
FILE *carregaArquivo(char *file_name, char *a){

    FILE *arquivo;

    arquivo = fopen(file_name, "r");

    if(arquivo != NULL){
        if(a=="r"){
            printf("Arquivo %s lido com sucesso!\n", file_name);
        } else if(a=="w"){
            printf("Arquivo %s criado com sucesso!\n", file_name);
        } else{
            printf("Arquivo %s localizado com sucesso!\n", file_name);
        }
        
        return arquivo;
    }else{
        printf("Erro ao carregar o arquivo!\n");
    }

    return 0;
}

typedef struct no{

    int valor;
    int linha;
    struct no *esquerda, *direita;

}No;

No* inserir(No *raiz, int num, int linha){
    if(raiz == NULL){
        No *novo = (No*)malloc(sizeof(No));
        novo->valor = num;
        novo->linha = linha;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    } else {
        if(num < raiz->valor)
            raiz->esquerda = inserir(raiz->esquerda, num, linha);
        if(num > raiz->valor)
            raiz->direita = inserir(raiz->direita, num, linha);
        
        return raiz;
    }
}

void imprimir(No *raiz){
    if(raiz != NULL){
        imprimir(raiz->esquerda);
        printf("%d|%d\n", raiz->valor, raiz->linha);
        imprimir(raiz->direita);
    }
}

No* lerLinhas(FILE *file){
    char linha[100], *pt;
    int i, contLinhas = 0;
    No *raiz = NULL;
    
    while(fscanf(file, "%s", linha) != EOF){
        i = 0;
        pt = strtok(linha, ",");
        while(pt) {
            if((contLinhas!=1 && contLinhas!=0) && (i==0))
                raiz = inserir(raiz, atoi(pt), contLinhas);
            i++;
            pt = strtok(NULL, ",");
        }
        contLinhas++;

    }
    printf("\nABP gerada com sucesso\n");
    return raiz;
}

No deletarABP(No *raiz)
{
    // Caso base: árvore vazia
    if (raiz == NULL) {
        return;
    }
 
    // exclui a subárvore esquerda e direita primeiro (Pós-ordem)
    deletarABP(raiz->esquerda);
    deletarABP(raiz->direita);
    //printf("Deletando nó: %d|%d\n", raiz->valor, raiz->linha);

    // exclui o nó atual após excluir sua subárvore esquerda e direita
    free(raiz);
 
    // define root como null antes de retornar
    raiz = NULL;
}


int main()
{

    int op;
    No *raiz = NULL;
    FILE *file;
    //char nome[100];
    //printf("Digite o nome de arquivo para leitura e a extensao: ");
    //scanf("%s", nome);
    file = carregaArquivo("car_data_teste.csv", "r");
    printf("\n");

    do{
        printf("------------------------------\n     |Menu de Opções|     \n1. Carregar Arquivo de Dados\n2. Emitir Relatório\n3. Sair\n\nDigite a opção que deseja: ");
        scanf("%d", &op);

        switch(op){
            

            case 1:
                printf("Carregando ABP...\n");
                raiz = lerLinhas(file);
                printf("\n");
                break;
            case 2:
                printf("\nEmitindo relatório...\n");

                if(raiz == NULL) {
                    printf("Arquivo vazio!\n");
                } else {
                    printf("ID|Linha\n");
                    imprimir(raiz);
                }

                printf("\n\n");
                break;

            case 3:
                deletarABP(raiz);
                printf("Saindo...\n");
                fclose(file);

                break;

            default:
                printf("Por favor, digite um opção válida!\n\n");
        }


    }while(op != 3);

    return 0;
}