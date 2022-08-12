#include "AVL.h"

void menu() {
    printf("ARVORE AVL\n");
    printf("1  ->  INSERIR ELEMENTOS\n");
    printf("2  ->  IMPRIMIR ELEMENTOS\n");    
    printf("3  ->  TAMANHO DA ARVORE\n");    
    printf("4  ->  ALTURA DA ARVORE\n");
    printf("5  ->  BUSCAR ELEMENTO\n");
    printf("6  ->  REMOVER ELEMENTO\n");
    printf("99 ->  CLEAR/CLS\n");
    printf("0  ->  SAIR\n");
    printf("\n");
}

ArvAVL *criarArvoreVazia_AVL() {
    ArvAVL *arv = NULL; // prevenindo possível lixo de memória
    arv = (ArvAVL *) malloc(sizeof(ArvAVL)); // alocando memória para a árvore
    arv->raiz = NULL; // prevenindo possível lixo de memória
    return arv; // retornando memória alocada
}

No *novoNo (int valor) {
    No *novo = NULL; // prevenindo posível lixo de memória
    novo = (No *) malloc(sizeof(No));  // alocando memória para o novo nó
    if (novo) { // criando novo nó e colocando valor
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
        printf("Elemento inserido com sucesso!\n");
    }
    else printf("Erro ao alocar memoria para um novo no\n");
    return novo; // retornando nó alocado
}

No *inserir_AVL(No *raiz, int valor) {
    if (!raiz) raiz = novoNo(valor);
    else { // inserindo ordenadamente
        if (valor < raiz->valor) raiz->esq = inserir_AVL(raiz->esq, valor);
        else if (valor > raiz->valor) raiz->dir = inserir_AVL(raiz->dir, valor);
        else {
            printf("Elemento ja esta na arvore.\n");
            return NULL;
        }
    }
    // calculando a altura do nó (necessário para o cálculo do fator de balanceamento)
    raiz->altura = maior(alturaNo(raiz->esq),alturaNo(raiz->dir)) + 1; // o maior nó + a adição do novo nó (+1)  
    raiz = balancear_AVL(raiz); // verificando balanceamento e balanceando caso seja necessário
    
    // nova raiz, perceba que aqui a "raiz" é retornada desde o nó que foi inserida até a verdadeira raiz,
    // fazendo com que todos os elementos sejam balanceados caso tenham sido desbalanceados
    return raiz;    
}

short maior(short a, short b) {
    return (a > b) ? a: b; // se a for maior que b, retorna a, se não, retorna b
}

short alturaNo(No *no) {
    if (no == NULL) return -1; // se não existe no->dir ou no->esq, então retornamos -1 porque não há filho desse lado
    else return no->altura;
}

short fatorDeBalanceamento_AVL(No *no) {
    if (no) return (alturaNo(no->esq) - alturaNo(no->dir)); // diferença da altura do nó à esquerda pelo da direita
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
    No *up = NULL, *up_esq = NULL;
    up = r->dir; // up é o nó a ser subido
    up_esq = up->esq; // up_esq recebe as informações armazenadas de up->esq

    up->esq = r; // up->esq recebe r, início da rotação
    // como up estava à direita de r, sabemos que ele é maior que r
    // como up_esq recebe o que estava à esquerda de up, sabemos que
    // ele também é maior que r, por isso... ↓
    r->dir = up_esq; // r->dir recebe os valores que estavam em up->esq antes

    r->altura = maior(alturaNo(r->esq),alturaNo(r->dir)) + 1;
    up->altura = maior(alturaNo(up->esq),alturaNo(up->dir)) + 1;
    
    return up;
}

No *rotacaoDireita_AVL(No *r) {
    No *up = NULL, *up_dir = NULL;
    up = r->esq; // up recebe o nó a ser subido
    up_dir = up->dir; // up_dir recebe o nó à direita do nó up, armazena os nós se houverem

    up->dir = r; // o valor à direita do nó up recebe o r, início da rotação
    // como up é menor que r, podemos colocar o r à direita do que
    // sobe e o que estava à direita colocamos à esquerda de r, que
    // também é menor que r
    r->esq = up_dir; // a esquerda do r recebe o que estava à direita do up de antes
    r->altura = maior(alturaNo(r->esq),alturaNo(r->dir)) + 1; // a altura do nó é a altura do maior nó filho +1
    up->altura = maior(alturaNo(up->esq),alturaNo(up->dir)) + 1; // calculando a altura do nó que rotacionou
    
    return up;
}

No *rotacaoDuplaDE_AVL(No *r) {
    r->dir = rotacaoDireita_AVL(r->dir); // início com rotação simples à direita
    return rotacaoEsquerda_AVL(r); // finaliza com rotação simples à esquerda
}

No *rotacaoDuplaED_AVL(No *r) {
    r->esq = rotacaoEsquerda_AVL(r->esq); // início com rotação simples à esquerda
    return rotacaoDireita_AVL(r); // finaliza com rotação à direita
}

void imprimirRepresentacao_ARV(No *raiz, int nivel) { // árvore deitada estilo infix
    int i;
    if (raiz) {
        // imprime todos os números a direita primeiro de acordo com os níveis
        // quanto maior a altura, maior o nível e maior as tabulações
        imprimirRepresentacao_ARV(raiz->dir, nivel+1);
        printf("\n");
        for (i = 0; i < nivel; i++) {
            printf("\t");
        }
        // imprime o valor do meio sem tabulações (o nível não aumentou)
        printf("%d", raiz->valor);
        // imprime os da esquerda agora com tabulações da mesma forma que imprimiu o da direita
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
        printf("Valor nao encontrado!\n");
        return NULL; // não removeu nada
    }
    else {
        if (raiz->valor == valor) {
            if(raiz->esq == NULL && raiz->dir == NULL) { // se o nó é um nó folha (sem filhos)
                free(raiz);
                // printf("Elemento folha removido: %d\n", valor); // Debug
                printf("Elemento removido: %d\n", valor);
                return NULL; // o nó passa a ser NULL
            }
            else {
                if(raiz->esq == NULL || raiz->dir == NULL) { // remove nós que possuem apenas um (1) filho
                    if (raiz->esq != NULL) aux = raiz->esq;
                    else aux = raiz->dir;
                    free(raiz);
                    // printf("Elemento com um nó filho removido: %d\n", valor); // Debug
                    printf("Elemento removido: %d\n", valor);
                    return aux; // o raiz->dir ou esq receberá esse aux
                }
                else { // remove nós que possuem dois (2) filhos
                    aux = raiz->esq; // substituir por um nó da esq
                    while (aux->dir != NULL) aux = aux->dir; // substituir pelo nó mais a dir do nó a esq
                    raiz->valor = aux->valor; // trocar os conteúdos dos nós para remover um nó do final
                    aux->valor = valor;
                    // printf("Elemento trocado: %d\n", valor); // Debug
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
    
    // nova raiz, perceba que aqui a "raiz" é retornada desde o nó que foi removida até a verdadeira raiz,
    // fazendo com que todos os elementos sejam balanceados caso tenham sido desbalanceados
    return raiz;
}

void liberarNos_ARV(No *raiz) {
    // liberação pós fixada para não perdermos nenhum valor
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
