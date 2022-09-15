#include "arvbin.h"

void menu() {
    printf("ÁRVORES\n");
    printf("1  ->  INSERIR\n");
    printf("2  ->  LISTAR ELEMENTOS\n");    
    printf("3  ->  TAMANHO DA ÁRVORE\n");    
    printf("4  ->  BUSCAR ELEMENTO\n");
    printf("5  ->  REMOVER ELEMENTOS\n");
    printf("99 ->  CLEAR/CLS\n");
    printf("0  ->  SAIR\n");
}

void criarArvoreVazia_Bin(ArvBin *arv) {
    arv->raiz = NULL;
}

void inserir_Bin(ArvBin *arv, int valor) {
    No *novo;
    if (!arv->raiz) {
        No *novo = (No *) malloc(sizeof(No));
        novo->dado = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arv->raiz = novo;
        printf("Elemento inserido com sucesso!\n");
    }
    else {
        if (valor < arv->raiz->dado) inserirEsq(arv->raiz, valor);
        else if (valor > arv->raiz->dado) inserirDir(arv->raiz, valor);
        else {
            printf("Elemento já está na arvore.\n");
            return;
        }
    }  
}

void inserirEsq(No *no, int valor) {
    No *novo;
    if (!no->esquerda) {
        No *novo = (No *) malloc(sizeof(No));
        novo->dado = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->esquerda = novo;
        printf("Elemento inserido com sucesso!\n");
    }
    else {
        if (valor < no->esquerda->dado) inserirEsq(no->esquerda, valor);
        else if (valor > no->direita->dado) inserirDir(no->esquerda, valor);
        else printf("Elemento já está na arvore.\n");
    }
}

void inserirDir(No *no, int valor) {
    No *novo;
    if (!no->direita) {
        No *novo = (No *) malloc(sizeof(No));
        novo->dado = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->direita = novo;
        printf("Elemento inserido com sucesso!\n");
    }
    else {
        if (valor > no->direita->dado) inserirDir(no->direita, valor);
        else if (valor < no->direita->dado) inserirEsq(no->direita, valor);
        else printf("Elemento já está na árvore!\n");
    }
}

void imprimirPrefix_Bin(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        imprimirPrefix_Bin(raiz->esquerda);
        imprimirPrefix_Bin(raiz->direita);
    }
}

void imprimirInfix_Bin(No *raiz) {
    if (raiz != NULL) {
        imprimirInfix_Bin(raiz->esquerda);
        printf("%d ", raiz->dado);
        imprimirInfix_Bin(raiz->direita);
    }
}

void imprimirPostfix_Bin(No *raiz) {
    if (raiz != NULL) {
        imprimirPostfix_Bin(raiz->esquerda);
        imprimirPostfix_Bin(raiz->direita);
        printf("%d ", raiz->dado);
    }
}

int buscar_Bin(No * raiz, int valor) {
    if (raiz == NULL) return FALSE;
    else {
        if (raiz->dado == valor) return raiz->dado;
        else if (raiz->dado > valor) return buscar_Bin(raiz->esquerda, valor);
        else return buscar_Bin(raiz->direita, valor);
    }
}

int tamanho_Bin(No *raiz) {
    if (raiz == NULL) return 0;
    else return 1 + tamanho_Bin(raiz->esquerda) + tamanho_Bin(raiz->direita);
}

No *remover_Bin(No *raiz, int valor) {
    No *aux;
    if (raiz == NULL) { // se a raiz da árvore é vazia ou se não encontrar o dado.
        printf("Valor não encontrado!\n");
        return NULL; // não removeu nada
    }
    else {
        if (raiz->dado == valor) {
            if(raiz->esquerda == NULL && raiz->direita == NULL) { // se o nó é um nó folha (sem filhos)
                free(raiz);
                return NULL; // o nó passa a ser NULL
            }
            else { // remove nós que possuem apenas um filho
                if(raiz->esquerda == NULL || raiz->direita == NULL) {
                    if (raiz->esquerda != NULL) aux = raiz->esquerda;
                    else aux = raiz->direita;
                    free(raiz);
                    return aux; // o raiz->direita ou esquerda receberá esse aux
                }
                else {
                    aux = raiz->esquerda; // substituir por um nó da esquerda
                    while (aux->direita != NULL) aux = aux->direita; // substituir pelo nó mais a direita do nó a esquerda
                    raiz->dado = aux->dado; // trocar os conteúdos dos nós para remover um nó do final
                    aux->dado = valor;
                    raiz->esquerda = remover_Bin(raiz->esquerda, valor);
                    return raiz; // a raiz em que estávamos trabalhando
                }
            }
        }
        else {
            if (raiz->dado > valor) raiz->esquerda = remover_Bin(raiz->esquerda,valor);
            else raiz->direita = remover_Bin(raiz->direita, valor);
            return raiz;
        }
    }
}

void liberarArvore_Bin(No *raiz) {
    if (raiz != NULL) {
        liberarArvore_Bin(raiz->esquerda);
        liberarArvore_Bin(raiz->direita);
        free(raiz);
    }
}

void clear_screen() {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}
