#include "AVL.h"

/*
gcc -c AVL.c -o AVL.o
gcc AVL.o main.c -o AVL.exe
./AVL.exe
*/

int main () {
    int op; // operador
    int opc = FALSE; // opção
    int valor;
    int i; // variável auxiliar
    int qtd; // quantidade
    ArvAVL *arv = criarArvoreVazia_AVL();
    clear_screen(); // limpando terminal
    
    do {
        menu();
        scanf("%d", &op);
        opc = FALSE;
        qtd = FALSE;
        printf("\n");
        switch (op) {
            case 1:
                printf("INSERCAO\n");
                // printf("Valor a ser inserido: ");
                while (qtd <= 0) {
                    printf("Quantidade de elementos a serem inseridos: ");
                    scanf("%d", &qtd);
                    if (qtd <= 0) printf("Quantidade invalida!\n");
                }
                for(i = 1; i <= qtd; i++) {
                    printf("%dº valor: ", i);
                    scanf("%d", &valor);
                    if (buscar_ARV(arv->raiz,valor) == FALSE) arv->raiz = inserir_AVL(arv->raiz,valor); // se o valor não estiver na árvore, posso inserir
                    else {
                        printf("O elemento ja esta na arvore!\nInsira outro valor!\n");
                        i--;
                    }
                }
                printf("\n");
                break;
            case 2:
                printf("IMPRESSAO\n");
                printf("1 - Representacao horizontal\n");
                printf("2 - Elementos pre fixados\n");
                printf("3 - Elementos fixados no meio\n");
                printf("4 - Elementos pos fixados\n");
                while (opc < 1 || opc > 4) {
                    scanf("%d", &opc);
                    if (opc < 1 || opc > 4) printf("Opção inválida!\n");
                }
                switch (opc) {
                    case 1:
                        imprimirRepresentacao_ARV(arv->raiz, 1);
                        printf("\n\n\n\n");
                        break;
                    case 2:
                        imprimirPrefix_ARV(arv->raiz);
                        printf("\n\n");
                        break;
                    case 3:
                        imprimirInfix_ARV(arv->raiz);
                        printf("\n\n");
                        break;
                    case 4:
                        imprimirPostfix_ARV(arv->raiz);
                        printf("\n\n");
                        break;
                }
                break;
            case 3:
                arv->tam = tamanho_ARV(arv->raiz);
                printf("Tamanho da arvore: '%d'\n\n", arv->tam);
                break;
            case 4:
                printf("Altura da arvore: %i\n\n", alturaNo(arv->raiz));
                break;
            case 5:
                printf("BUSCA\n");
                printf("Valor a ser buscado: ");
                scanf("%d", &valor);
                if (buscar_ARV(arv->raiz,valor) != FALSE) printf("O elemento '%d' esta na arvore :)\n\n", valor);
                else printf("O elemento '%d' nao esta na arvore :(\n\n", valor);
                break;
            case 6:
                printf("REMOCAO\n");
                printf("Elemento a ser removido: ");
                scanf("%d", &valor);
                arv->raiz = remover_AVL(arv->raiz,valor);
                printf("\n");
                break;
            case 99:
                clear_screen();
                break;
            default:
                if (op != 0) printf("Operacao invalida!\n\n");
                break;
        }
    } while (op != 0);
    liberarNos_ARV(arv->raiz);
    liberarArvore_ARV(arv);
    return 0;
}
