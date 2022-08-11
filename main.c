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
    ArvAVL *arv = criarArvoreVazia_AVL();
    clear_screen(); // limpando terminal
    
    do {
        menu();
        scanf("%d", &op);
        opc = FALSE;
        printf("\n");
        switch (op) {
            case 1:
                printf("INSERÇÃO\n");
                printf("Valor a ser inserido: ");
                scanf("%d", &valor);
                arv->raiz = inserir_AVL(arv->raiz, valor);
                printf("\n");
                break;
            case 2:
                printf("IMPRESSÃO\n");
                printf("1 - Representação horizontal\n");
                printf("2 - Elementos pré fixados\n");
                printf("3 - Elementos fixados no meio\n");
                printf("4 - Elementos pós fixados\n");
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
                printf("O tamanho da árvore é '%d'\n\n", arv->tam);
                break;
            case 4:
                printf("BUSCA\n");
                printf("Valor a ser buscado: ");
                scanf("%d", &valor);
                if (buscar_ARV(arv->raiz,valor) != FALSE) printf("O elemento '%d' está na árvore :)\n\n", valor);
                else printf("O elemento '%d' não está na árvore :(\n\n", valor);
                break;
            case 5:
                printf("REMOÇÃO\n");
                printf("Elemento a ser removido: ");
                scanf("%d", &valor);
                arv->raiz = remover_AVL(arv->raiz,valor);
                printf("\n");
                break;
            case 99:
                clear_screen();
                break;
            default:
                if (op != 0) printf("Operação inválida!\n\n");
                break;
        }
    } while (op != 0);
    liberarNos_ARV(arv->raiz);
    liberarArvore_ARV(arv);
    return 0;
}
