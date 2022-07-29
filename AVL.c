#include "AVL.h"

void menu() {
    printf("ÁRVORE AVL\n");
    printf("1  ->  INSERIR\n");
    printf("2  ->  LISTAR ELEMENTOS\n");    
    printf("3  ->  TAMANHO DA ÁRVORE\n");    
    printf("4  ->  BUSCAR ELEMENTO\n");
    printf("5  ->  REMOVER ELEMENTOS\n");
    printf("99 ->  CLEAR/CLS\n");
    printf("0  ->  SAIR\n");
}

void criarArvoreVazia_AVL(ArvAVL *arv) {
    arv->raiz = NULL;
}

No *novoNo (int valor) {
    No *novo = malloc(sizeof(No));
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
        if (valor < raiz->valor) raiz->esq = inserir_AVL(raiz, valor);
        else if (valor > raiz->valor) raiz->dir = inserir_AVL(raiz, valor);
        else {
            printf("Elemento já está na arvore.\n");
            return;
        }
    }
    raiz->altura = maior(alturaNo(raiz->esq),alturaNo(raiz->dir) + 1);  
    raiz = balancear_AVL(raiz);
    return raiz;
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
    if (fatorDeBalanceamento_AVL(no) < -1) { // rotações do lado direito
        // verificando se há necessidade de rotação dupla, se o da esquerda estiver desbalanceado
        if (fatorDeBalanceamento_AVL(no->dir) >= 1) rotacaoDuplaDE_AVL(no);
        // se a árvore estiver completamente desbalanceada à direita fb < -1 e fb do direito <= 0
        else rotacaoEsquerda_AVL(no);
    }
    else if (fatorDeBalanceamento_AVL(no) > 1) { // rotações do lado esquerdo
        // verificando se há necessidade de rotação dupla do lado esquerdo
        if (fatorDeBalanceamento_AVL(no) <= -1) rotacaoDuplaED_AVL(no);
        // se estiver completamente desbalanceada á esquerda, ou seja fb > 1 e fb do esquerdo >= 0
        else rotacaoDireita_AVL(no);
    }
    return no;
}

No *rotacaoEsquerda_AVL(No *r) {
    No *y, *f;
    y = r->dir;
    f = y->esq;

    y->esq = r;
    r->dir = f;

    r->altura = maior(alturaNo(r->esq),alturaNo(r->dir) + 1);
    y->altura = maior(alturaNo(y->esq),alturaNo(y->dir) + 1);
    
    return y;
}

No *rotacaoDireita_AVL(No *r) {
    No *y, *f;
    y = r->esq;
    f = y->dir;

    y->dir = r;
    r->esq = f;

    r->altura = maior(alturaNo(r->esq),alturaNo(r->dir) + 1); // a altura do nó é a altura do maior nó filho +1
    y->altura = maior(alturaNo(y->esq),alturaNo(y->dir) + 1);
    
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

void imprimirPrefix_AVL(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        imprimirPrefix_AVL(raiz->esq);
        imprimirPrefix_AVL(raiz->dir);
    }
}

void imprimirInfix_AVL(No *raiz) {
    if (raiz != NULL) {
        imprimirInfix_AVL(raiz->esq);
        printf("%d ", raiz->valor);
        imprimirInfix_AVL(raiz->dir);
    }
}

void imprimirPostfix_AVL(No *raiz) {
    if (raiz != NULL) {
        imprimirPostfix_AVL(raiz->esq);
        imprimirPostfix_AVL(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

int buscar_AVL(No * raiz, int valor) {
    if (raiz == NULL) return FALSE;
    else {
        if (raiz->valor == valor) return raiz->valor;
        else if (raiz->valor > valor) return buscar_AVL(raiz->esq, valor);
        else return buscar_AVL(raiz->dir, valor);
    }
}

int tamanho_AVL(No *raiz) {
    if (raiz == NULL) return 0;
    else return 1 + tamanho_AVL(raiz->esq) + tamanho_AVL(raiz->dir);
}

No *remover_AVL(No *raiz, int valor) {
    No *aux;
    if (raiz == NULL) { // se a raiz da árvore é vazia ou se não encontrar o valor.
        printf("Valor não encontrado!\n");
        return NULL; // não removeu nada
    }
    else {
        if (raiz->valor == valor) {
            if(raiz->esq == NULL && raiz->dir == NULL) { // se o nó é um nó folha (sem filhos)
                free(raiz);
                return NULL; // o nó passa a ser NULL
            }
            else { // remove nós que possuem apenas um filho
                if(raiz->esq == NULL || raiz->dir == NULL) {
                    if (raiz->esq != NULL) aux = raiz->esq;
                    else aux = raiz->dir;
                    free(raiz);
                    return aux; // o raiz->dir ou esq receberá esse aux
                }
                else {
                    aux = raiz->esq; // substituir por um nó da esq
                    while (aux->dir != NULL) aux = aux->dir; // substituir pelo nó mais a dir do nó a esq
                    raiz->valor = aux->valor; // trocar os conteúdos dos nós para remover um nó do final
                    aux->valor = valor;
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
}

void liberarArvore_AVL(No *raiz) {
    if (raiz != NULL) {
        liberarArvore_AVL(raiz->esq);
        liberarArvore_AVL(raiz->dir);
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
