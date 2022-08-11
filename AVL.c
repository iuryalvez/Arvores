#include "AVL.h"

void menu() {
    printf("ÁRVORE AVL\n");
    printf("1  ->  INSERIR\n");
    printf("2  ->  IMPRIMIR ELEMENTOS\n");    
    printf("3  ->  TAMANHO DA ÁRVORE\n");    
    printf("4  ->  BUSCAR ELEMENTO\n");
    printf("5  ->  REMOVER ELEMENTOS\n");
    printf("99 ->  CLEAR/CLS\n");
    printf("0  ->  SAIR\n");
    printf("\n");
}

ArvAVL *criarArvoreVazia_AVL() {
    ArvAVL *arv = NULL;
    arv = (ArvAVL *) malloc(sizeof(ArvAVL));
    arv->raiz = NULL;
    return arv;
}

No *novoNo (int valor) {
    No *novo = NULL;
    novo = (No *) malloc(sizeof(No));
    if (novo) {
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
        printf("Elemento inserido com sucesso!\n");
    }
    else printf("Erro ao alocar memória para um novo nó\n");
    return novo; // retornando nó alocado
}

No *inserir_AVL(No *raiz, int valor) {
    if (!raiz) raiz = novoNo(valor);
    else { // inserindo ordenadamente
        if (valor < raiz->valor) raiz->esq = inserir_AVL(raiz->esq, valor);
        else if (valor > raiz->valor) raiz->dir = inserir_AVL(raiz->dir, valor);
        else {
            printf("Elemento já está na arvore.\n");
            return NULL;
        }
    }
    raiz->altura = maior(alturaNo(raiz->esq),alturaNo(raiz->dir)) + 1;  
    raiz = balancear_AVL(raiz);
    return raiz; // nova raiz
}

short maior(short a, short b) {
    return (a > b) ? a: b;
}

short alturaNo(No *no) {
    if (no == NULL) return -1; // se não existe no->dir ou no->esq, então retornamos -1 porque não há filho desse lado
    else return no->altura;
}

short fatorDeBalanceamento_AVL(No *no) {
    if (no) return (alturaNo(no->esq) - alturaNo(no->dir));
    else return 0;
}

No *balancear_AVL(No *no) {
    if (fatorDeBalanceamento_AVL(no) <= -2) { // rotações do lado direito
        // verificando se há necessidade de rotação dupla, se o da esquerda estiver desbalanceado
        if (fatorDeBalanceamento_AVL(no->dir) >= 1) no = rotacaoDuplaDE_AVL(no);
        // se a árvore estiver completamente desbalanceada à direita fb < -1 e fb do direito <= 0
        else no = rotacaoEsquerda_AVL(no);
    }
    else if (fatorDeBalanceamento_AVL(no) >= 2) { // rotações do lado esquerdo
        // verificando se há necessidade de rotação dupla do lado esquerdo
        if (fatorDeBalanceamento_AVL(no) <= -1) no = rotacaoDuplaED_AVL(no);
        // se estiver completamente desbalanceada á esquerda, ou seja fb > 1 e fb do esquerdo >= 0
        else no = rotacaoDireita_AVL(no);
    }
    return no;
}

No *rotacaoEsquerda_AVL(No *r) {
    No *y = NULL, *f = NULL;
    y = r->dir;
    f = y->esq;

    y->esq = r;
    r->dir = f;

    r->altura = maior(alturaNo(r->esq),alturaNo(r->dir)) + 1;
    y->altura = maior(alturaNo(y->esq),alturaNo(y->dir)) + 1;
    
    return y;
}

No *rotacaoDireita_AVL(No *r) {
    No *y = NULL, *f = NULL;
    y = r->esq;
    f = y->dir;

    y->dir = r;
    r->esq = f;

    r->altura = maior(alturaNo(r->esq),alturaNo(r->dir)) + 1; // a altura do nó é a altura do maior nó filho +1
    y->altura = maior(alturaNo(y->esq),alturaNo(y->dir)) + 1;
    
    return y;
}

No *rotacaoDuplaDE_AVL(No *r) {
    r->dir = rotacaoDireita_AVL(r->dir);
    return rotacaoEsquerda_AVL(r);
}

No *rotacaoDuplaED_AVL(No *r) {
    r->esq = rotacaoEsquerda_AVL(r->esq);
    return rotacaoDireita_AVL(r);
}

void imprimirRepresentacao_ARV(No *raiz, int nivel) { // árvore deitada
    int i;
    if (raiz) {
        imprimirRepresentacao_ARV(raiz->dir, nivel+1);
        printf("\n");
        for (i = 0; i < nivel; i++) {
            printf("\t");
        }
        printf("%d", raiz->valor);
        imprimirRepresentacao_ARV(raiz->esq, nivel + 1);
    }
}

void imprimirPrefix_ARV(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        imprimirPrefix_ARV(raiz->esq);
        imprimirPrefix_ARV(raiz->dir);
    }
}

void imprimirInfix_ARV(No *raiz) {
    if (raiz != NULL) {
        imprimirInfix_ARV(raiz->esq);
        printf("%d ", raiz->valor);
        imprimirInfix_ARV(raiz->dir);
    }
}

void imprimirPostfix_ARV(No *raiz) {
    if (raiz != NULL) {
        imprimirPostfix_ARV(raiz->esq);
        imprimirPostfix_ARV(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

int buscar_ARV(No * raiz, int valor) {
    if (raiz == NULL) return FALSE;
    else {
        if (raiz->valor == valor) return raiz->valor;
        else if (raiz->valor > valor) return buscar_ARV(raiz->esq, valor);
        else return buscar_ARV(raiz->dir, valor);
    }
}

int tamanho_ARV(No *raiz) {
    if (raiz == NULL) return 0;
    else return 1 + tamanho_ARV(raiz->esq) + tamanho_ARV(raiz->dir);
}

No *remover_AVL(No *raiz, int valor) {
    No *aux = NULL;
    if (raiz == NULL) { // se a raiz da árvore é vazia ou se não encontrar o valor.
        printf("Valor não encontrado!\n");
        return NULL; // não removeu nada
    }
    else {
        if (raiz->valor == valor) {
            if(raiz->esq == NULL && raiz->dir == NULL) { // se o nó é um nó folha (sem filhos)
                free(raiz);
                // printf("Elemento folha removido: %d\n", valor);
                printf("Elemento removido: %d\n", valor);
                return NULL; // o nó passa a ser NULL
            }
            else {
                if(raiz->esq == NULL || raiz->dir == NULL) { // remove nós que possuem apenas um (1) filho
                    if (raiz->esq != NULL) aux = raiz->esq;
                    else aux = raiz->dir;
                    free(raiz);
                    // printf("Elemento com um nó filho removido: %d\n", valor);
                    printf("Elemento removido: %d\n", valor);
                    return aux; // o raiz->dir ou esq receberá esse aux
                }
                else { // remove nós que possuem dois (2) filhos
                    aux = raiz->esq; // substituir por um nó da esq
                    while (aux->dir != NULL) aux = aux->dir; // substituir pelo nó mais a dir do nó a esq
                    raiz->valor = aux->valor; // trocar os conteúdos dos nós para remover um nó do final
                    aux->valor = valor;
                    // printf("Elemento trocado: %d\n", valor);
                    raiz->esq = remover_AVL(raiz->esq, valor);
                    return raiz; // a raiz em que estávamos trabalhando
                }
            }
        }
        else {
            if (raiz->valor > valor) raiz->esq = remover_AVL(raiz->esq,valor);
            else raiz->dir = remover_AVL(raiz->dir, valor);
            return raiz;
        }
    }
    raiz->altura = maior(alturaNo(raiz->esq),alturaNo(raiz->dir)) + 1; // recalculando altura da árvore
    raiz = balancear_AVL(raiz); // balanceamento, se necessário
    return raiz; // nova raiz
}

void liberarNos_ARV(No *raiz) {
    if (raiz != NULL) {
        liberarNos_ARV(raiz->esq);
        liberarNos_ARV(raiz->dir);
        free(raiz);
    }
}

void liberarArvore_ARV(ArvAVL *arv) {
    free(arv);
}

void clear_screen() {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}
