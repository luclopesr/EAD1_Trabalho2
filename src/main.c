#include <stdio.h>
#include <stdlib.h>

void menu() {
    printf("\n_____| Menu de Opções |_____\n\n1. Carregar Arquivo de Dados\n2. Emitir Relatório\n3. Sair\n\n");
}

void carregaDados() {
    printf("Estou dentro da função CARREGADADOS\n");
}

void relatorio() {
    printf("Estou dentro da função RELATORIO\n");
}

void sair() {
    printf("Estou dentro da função SAIR\n");
}

int main() {   
    // Declarações
    int opcao;

    do {
        menu();
        printf("Digite a opção que deseja: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            carregaDados();

            // printf("Tecle para continuar.\n");
            // getchar();
            break;

        case 2:
            relatorio();

            // printf("Tecle para continuar.\n");
            // getchar();
            break;

        case 3:
            sair();
            break;
        
        default:
            printf("Por favor, digite uma opção válida.\n");

            // printf("Tecle para continuar.\n");
            // getchar();
            break;
        }
    } while (opcao != 3);
    
    return 0;
}
