#include <stdio.h>
#include <stdlib.h>

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

FILE *abreArquivo(){
    FILE *file = NULL;
    char *nome;
    nome = malloc(100*sizeof(char));

    while(file == NULL){
        printf("\nPara sair digite '3'\nDigite o nome de arquivo para leitura e a extensao: ");
        scanf("%s", nome);
        if(comparaString(nome, "3")){
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

//Função para comparar duas strings
int comparaString(char *a, char *b)
{
    int i;
    int resp;

    if (strlen(a) == strlen(b)) {
        for (i = 0; i < strlen(a); i++) {
            if (a[i] == b [i]) {
                resp = 1;
            } else {
                return 0;
            }
        }
    } else {
        resp = 0;
    }

    return resp;
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
