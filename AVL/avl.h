#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TRUE 1
#define FALSE -1

typedef struct no {
    int valor;
    struct no *esq, *dir;
    int tam;
    short altura;
} No;

typedef struct {
    No *raiz;
    int tam;
} ArvAVL;

// função que exibe o menu de opções
void menu();

/**
 * @brief função que cria árvore vazia (arv->raiz = NULL)
 * 
 * @return Árvore alocada
 */
ArvAVL *criarArvoreVazia_AVL();

/**
 * @brief função que cria um novo nó
 * 
 * @param valor valor a ser armazenado no nó
 * @return No*, o endereço de um nó alocado
 */
No *novoNo (int valor);

/**
 * @brief função recursiva que insere elementos na árvore AVL
 * 
 * @param *no nó raiz da árvore
 * @param valor valor a ser inserido
 * @return No*, o nó alocado e balanceado (recursivo)
 */
No *inserir_AVL(No *raiz, int valor);

// função que retorna o maior valor entre a e b;
short maior (short a, short b);

/**
 * @brief função que retorna a altura de um nó
 * 
 * @param no altura desse nó
 * @return short, valor da altura
 */
short alturaNo(No *no);

/**
 * @brief função que calcula o fator de balanceamento da árvore
 * 
 * @param no nó que vai ser rotacionado
 * @return short, positivo ou negativo
 */
short fatorDeBalanceamento_AVL(No *no);

/**
 * @brief função que imprime a representação visual da árvore
 * 
 * @param raiz nó raiz
 * @param nivel camada em que se encontra o valor
 */
void imprimirRepresentacao_ARV(No *raiz, int nivel);

/**
 * @brief função que imprime os itens da árvore de forma pré-fixada
 * 
 * @param raiz raiz da árvore AVL
 */
void imprimirPrefix_ARV(No *raiz);

/**
 * @brief função que imprime os itens da árvore de forma meio-fixada
 * 
 * @param raiz raiz da árvore AVL
 */
void imprimirInfix_ARV(No *raiz);

/**
 * @brief função que imprime os itens da árvore de forma pós-fixada
 * 
 * @param raiz raiz da árvore AVL
 */
void imprimirPostfix_ARV(No *raiz);

/**
 * @brief função que faz o balanceamento da árvore AVL a medida que inserimos nós
 * 
 * @param no nó a ser balanceado
 * @return No* nó balanceado
 */
No *balancear_AVL(No *no);

/**
 * @brief função que rotaciona a árvore à esquerda
 * 
 * @param r nó raiz a ser rotacionado
 * @return No* nova raiz
 */
No *rotacaoEsquerda_AVL(No *r);

/**
 * @brief função que rotaciona a árvore à direita
 * 
 * @param r nó raiz a ser rotacionado
 * @return No* nova raiz
 */
No *rotacaoDireita_AVL(No *r);

/**
 * @brief função que rotaciona a árvore à direita e depois à esquerda
 * 
 * @param r nó a ser rotacionado
 * @return No* nó rotacionado
 */
No *rotacaoDuplaDE_AVL(No *r);

/**
 * @brief função que rotaciona a árvore à esquerda e depois à direita
 * 
 * @param r nó a ser rotacionado
 * @return No* nó rotacionado
 */
No *rotacaoDuplaED_AVL(No *r);

/**
 * @brief função que retorna se o elemento está ou não na árvore
 * 
 * @param raiz raiz da arvore AVL
 * @param valor valor a ser buscado
 * @return int 
 */
int buscar_ARV(No * raiz, int valor);

/**
 * @brief função que retorna o tamanho da árvore (recursivo)
 * 
 * @param raiz raiz da árvore
 * @return int, o tamanho
 */
int tamanho_ARV(No *raiz);

/**
 * @brief função que remove um nó da árvore
 * 
 * @param raiz raiz da árvore
 * @param valor valor a ser removido
 * @return No* auxiliar para fazer os nós pais apontarem para os filhos do nó removido
 */
No *remover_AVL(No *raiz, int valor);

/**
 * @brief função que libera os nós alocados
 * 
 * @param raiz raiz da árvore
 */
void liberarNos_ARV(No *raiz);

// função que libera a árvore passada por referência
void liberarArvore_ARV(ArvAVL *arv);

// função que dá "cls" na tela do terminal
void clear_screen();
