//Grupo D
//Fonte de dados: Cars - Purchase Decision Dataset
//Campo Chave: User ID
//Nome	                        Matrícula
//Henrique Pucci da Silva Pinto	202016506
//João Pedro Costa	            190030801
//Lucas Caldas Barbosa de Souza	190091606
//Lucas Lopes Rocha	            202023903
//Lucas Soares Barros	        202017700
//Sidney Fernando F. Lemes      190037997

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função para realizar ação com arquivo
//Passa nome do arquivo e oq deseja fazer
FILE *carregaArquivo(char *file_name, char *a){

    FILE *arquivo;

    arquivo = fopen(file_name, a);

    if(arquivo != NULL){
        if(comparaString("r",a)==0){
            printf("Arquivo %s lido com sucesso!\n", file_name);
        } else{
            printf("Arquivo %s localizado com sucesso!\n", file_name);
        }
        
        return arquivo;
    }else{
        printf("Erro ao carregar o arquivo!\n");
    }

    return 0;
}

FILE *abreArquivo(){
    FILE *file = NULL;
    char *nome;
    nome = malloc(100*sizeof(char));

    while(file == NULL){
        printf("\nPara sair digite '3'\nDigite o nome de arquivo para leitura e a extensao: ");
        scanf("%s", nome);
        if(comparaString(nome, "3")==0){
            return NULL;
        }

        file = carregaArquivo(nome, "r");
        
        if(file == NULL){
            printf("Nome invalido!\n");
        }
    }
    free(nome);
    return file;
}

int comparaString(char str1[], char str2[])
{
    int ctr=0;

    while(str1[ctr]==str2[ctr])
    {
        if(str1[ctr]=='\0'||str2[ctr]=='\0')
            break;
        ctr++;
    }
    if(str1[ctr]=='\0' && str2[ctr]=='\0')
        return 0;
    else
        return -1;
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

void imprimir(No *raiz, FILE *file){
    FILE *arquivo;
    int i=0;
    char *leitura;
    leitura = malloc(100*sizeof(char));

    if(raiz != NULL){
        imprimir(raiz->esquerda, file);
        while (i<=raiz->linha)
        {
            fscanf(file, "%s", leitura);
            i++;
        }
        printf("%s\n", leitura);
        imprimir(raiz->direita, file);
    }
    fseek(file, 0, SEEK_SET);
    free(leitura);
}

No* montaABP(FILE *file){
    char *pt;
    char *linha;
    linha = malloc(100*sizeof(char));
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
    free(linha);
    return raiz;
}

void deletarABP(No *raiz)
{
    // Caso base: árvore vazia
    if (raiz == NULL) {
        return;
    }
 
    // exclui a subárvore esquerda e direita primeiro (Pós-ordem)
    deletarABP(raiz->esquerda);
    deletarABP(raiz->direita);
    printf("Deletando no: %d|%d\n", raiz->valor, raiz->linha);

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
    
    file = abreArquivo();
    if(file == NULL){
        printf("Saindo...");
        return 0;
    }

    do{
        printf("------------------------------\n     |Menu de Opcoes|     \n1. Carregar Arquivo de Dados\n2. Emitir Relatorio\n3. Sair\n\nDigite a opcao que deseja: ");
        scanf("%d", &op);

        switch(op){
            

            case 1:
                printf("Carregando ABP...\n");
                raiz = montaABP(file);
                printf("\n");
                break;
            case 2:
                
                if(raiz == NULL) {
                    printf("Arquivo vazio!\n");
                } else {
                    printf("\nEmitindo relatorio...\n\n");
                    printf("UserID,Gender,Age,AnnualSalary,Purchased\n");
                    imprimir(raiz, file);
                }

                printf("\n\n");
                break;

            case 3:
                deletarABP(raiz);
                printf("Saindo...\n");
                fclose(file);

                break;

            default:
                printf("Por favor, digite um opcao valida!\n\n");
        }


    }while(op != 3);

    return 0;
}
