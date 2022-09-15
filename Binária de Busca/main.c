#include "arvbin.h"

int main () {
    setlocale(LC_ALL, "Portuguese");
    ArvBin *arv;
    criarArvoreVazia_Bin(arv);
    No *aux;
    int op, num, opc;
    do {
        menu();
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("----- INSERINDO ELEMENTOS -----\n");
                printf("Elemento a ser inserido: ");
                scanf("%d", &num);
                inserir_Bin(arv,num);
                break;
            case 2:
                opc = 0;
                printf("----- LISTANDO ELEMENTOS -----\n");
                printf("1 - Prefix\n");
                printf("2 - Infix\n");
                printf("3 - Postfix\n");
                while (opc < 1 || opc > 3) {
                    scanf("%d", &opc);
                    if (opc < 1 || opc > 3) printf("Opção inválida!\n");
                }
                if (opc == 1) imprimirPrefix_Bin(arv->raiz);
                else if (opc == 2) imprimirInfix_Bin(arv->raiz);
                else imprimirPostfix_Bin(arv->raiz);
                printf("\n");
                break;
            case 3:
                arv->tam = tamanho_Bin(arv->raiz);
                printf("O tamanho da árvore é: %d\n", arv->tam);
                break;
            case 4:
                printf("----- BUSCANDO ELEMENTOS -----\n");
                printf("Insira o elemento a ser buscado: ");
                scanf("%d", &num);
                if (buscar_Bin(arv->raiz, num) == FALSE) printf("O elemento não está na árvore\n");
                else printf("O elemento %d está na árvore.\n", num);
                break;
            case 5:
                printf("----- REMOVENDO ELEMENTOS -----\n");
                printf("Insira o elemento a ser removido: ");
                scanf("%d", &num);
                // printf("%p", aux);
                remover_Bin(arv->raiz, num);
                break;
            case 99:
                clear_screen();
                break;
            default:
                if (op != 0) printf("Opção inválida!\n");
        }
    } while (op != 0);
    liberarArvore_Bin(arv->raiz);
    return 0;
}