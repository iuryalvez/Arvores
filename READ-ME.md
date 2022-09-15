# [Árvores](https://pt.wikipedia.org/wiki/Árvore_binária)

Uma árvore binária é uma estrutura de dados caracterizada por: Ou não tem elemento algum (árvore vazia). Ou tem um elemento distinto, denominado raiz, com dois ponteiros para duas estruturas diferentes, denominadas subárvore esquerda e subárvore direita.

## [ABB - Árvore Binária de Busca](https://pt.wikipedia.org/wiki/Árvore_binária_de_busca)

### Especificação

Uma árvore binária de busca (ABB) é uma estrutura de dados de árvore binária baseada em nós, onde todos os nós da subárvore esquerda possuem um valor numérico inferior ao nó raiz e todos os nós da subárvore direita possuem um valor superior ao nó raiz.

### Programa

Implementação de uma árvore binária de busca.

Compilando e executando a aplicação

    gcc abb.c main.c -o abb.exe
    ./abb.exe

## [AVL - Árvore Balanceada AVL](https://pt.wikipedia.org/wiki/Árvore_AVL)

### Especificação

Árvore AVL é uma árvore binária de busca balanceada, ou seja, uma árvore balanceada são as árvores que minimizam o número de comparações efetuadas no pior caso para uma busca com chaves de probabilidades de ocorrências idênticas.

### Programa

Implementação das funções da árvore AVL, grande parte dos códigos de ABB foram reaproveitados. 

Compilando e executando o programa

    gcc avl.c main.c -o avl.exe
    ./avl.exe
