#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TRUE 1
#define FALSE -1

typedef struct no {
    int dado;
    struct no *esquerda, *direita;
} No;

typedef struct {
    No *raiz;
    int tam;
} ArvBin;

// função que exibe o menu de opções
void menu();

/**
 * @brief função que cria árvore vazia (arv->raiz = NULL)
 * 
 * @param arv estrutura da árvore binária
 */
void criarArvoreVazia_Bin(ArvBin *arv);

/**
 * @brief função que insere valores na árvore binária
 * 
 * @param arv estrutura de árvore binária 
 * @param valor valor a ser inserido
 */
void inserir_Bin(ArvBin *arv, int valor);

/**
 * @brief função complementar para inserir à esquerda
 * 
 * @param no estrura de nó
 * @param valor valor a ser inserido
 */
void inserirEsq(No *no, int valor);

/**
 * @brief função complementar para inserir à direita
 * 
 * @param no estrutura de nó
 * @param valor valor a ser inserido
 */
void inserirDir(No *no, int valor);

/**
 * @brief função que imprime os itens da árvore de forma pré-fixada
 * 
 * @param raiz raiz da árvore binária
 */
void imprimirPrefix_Bin(No *raiz);

/**
 * @brief função que imprime os itens da árvore de forma meio-fixada
 * 
 * @param raiz raiz da árvore binária
 */
void imprimirInfix_Bin(No *raiz);

/**
 * @brief função que imprime os itens da árvore de forma pós-fixada
 * 
 * @param raiz raiz da árvore binária
 */
void imprimirPostfix_Bin(No *raiz);

/**
 * @brief função que retorna se o elemento está ou não na árvore
 * 
 * @param raiz raiz da arvore binária
 * @param valor valor a ser buscado
 * @return int 
 */
int buscar_Bin(No * raiz, int valor);

/**
 * @brief função que retorna o tamanho da árvore (recursivo)
 * 
 * @param raiz raiz da árvore
 * @return int, o tamanho
 */
int tamanho_Bin(No *raiz);

/**
 * @brief função que remove um nó da árvore
 * 
 * @param raiz raiz da árvore
 * @param valor valor a ser removido
 * @return No* auxiliar para fazer os nós pais apontarem para os filhos do nó removido
 */
No *remover_Bin(No *raiz, int valor);

/**
 * @brief função que libera os nós alocados
 * 
 * @param raiz raiz da árvore
 */
void liberarArvore_Bin(No *raiz);

// função que dá "cls" na tela do terminal
void clear_screen();
