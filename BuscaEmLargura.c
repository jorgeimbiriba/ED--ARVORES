#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore binária
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} NODE;

// Estrutura da fila para BFS
typedef struct QueueNode {
    NODE *treeNode;
    struct QueueNode *next;
} QUEUE_NODE;

typedef struct Queue {
    QUEUE_NODE *front;
    QUEUE_NODE *rear;
} QUEUE;

// Funções básicas da árvore binária
NODE *criarNo(int valor);
NODE *inserir(NODE *root, int valor);
NODE *remover(NODE *root, int valor);
NODE *buscar(NODE *root, int valor);
int calcularAltura(NODE *root);

// Funções de travessia
void preOrder(NODE *root);
void inOrder(NODE *root);
void postOrder(NODE *root);
void breadthFirstSearch(NODE *root);

// Funções auxiliares para remoção
NODE *encontrarMinimo(NODE *root);

// Funções auxiliares para fila (usada na BFS)
QUEUE *criarFila();
void enfileirar(QUEUE *fila, NODE *treeNode);
NODE *desenfileirar(QUEUE *fila);
int filaVazia(QUEUE *fila);

int main() {
    NODE *root = NULL;

    // Inserindo valores na árvore
    root = inserir(root, 50);
    root = inserir(root, 30);
    root = inserir(root, 70);
    root = inserir(root, 20);
    root = inserir(root, 40);
    root = inserir(root, 60);
    root = inserir(root, 80);

    printf("Busca Pré-ordem (Pre-order): ");
    preOrder(root);
    printf("\n");

    printf("Busca Em ordem (In-order): ");
    inOrder(root);
    printf("\n");

    printf("Busca Pós-ordem (Post-order): ");
    postOrder(root);
    printf("\n");

    printf("Busca em largura (BFS): ");
    breadthFirstSearch(root);
    printf("\n");

    // Buscando um valor
    int valorBuscado = 40;
    NODE *resultadoBusca = buscar(root, valorBuscado);
    if (resultadoBusca != NULL) {
        printf("Valor %d encontrado na árvore.\n", valorBuscado);
    } else {
        printf("Valor %d não encontrado na árvore.\n", valorBuscado);
    }

    // Calculando a altura da árvore
    printf("Altura da árvore: %d\n", calcularAltura(root));

    // Removendo um nó
    printf("Removendo o valor 30 da árvore...\n");
    root = remover(root, 30);

    printf("Busca Em ordem (In-order) após remoção: ");
    inOrder(root);
    printf("\n");

    return 0;
}

// Função para criar um novo nó
NODE *criarNo(int valor) {
    NODE *novoNo = (NODE *)malloc(sizeof(NODE));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->data = valor;
    novoNo->left = NULL;
    novoNo->right = NULL;
    return novoNo;
}

// Função para inserir um valor na árvore
NODE *inserir(NODE *root, int valor) {
    if (root == NULL) {
        return criarNo(valor);
    }
    if (valor < root->data) {
        root->left = inserir(root->left, valor);
    } else if (valor > root->data) {
        root->right = inserir(root->right, valor);
    }
    return root;
}

// Função para remover um nó da árvore
NODE *remover(NODE *root, int valor) {
    if (root == NULL) {
        return NULL;
    }

    if (valor < root->data) {
        root->left = remover(root->left, valor);
    } else if (valor > root->data) {
        root->right = remover(root->right, valor);
    } else {
        // Caso 1: Nó sem filhos
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Caso 2: Nó com um filho
        if (root->left == NULL) {
            NODE *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            NODE *temp = root->left;
            free(root);
            return temp;
        }
        // Caso 3: Nó com dois filhos
        NODE *minimo = encontrarMinimo(root->right);
        root->data = minimo->data;
        root->right = remover(root->right, minimo->data);
    }
    return root;
}

// Função para buscar um valor na árvore
NODE *buscar(NODE *root, int valor) {
    if (root == NULL || root->data == valor) {
        return root;
    }
    if (valor < root->data) {
        return buscar(root->left, valor);
    } else {
        return buscar(root->right, valor);
    }
}

// Função para calcular a altura da árvore
int calcularAltura(NODE *root) {
    if (root == NULL) {
        return -1; // Árvore vazia tem altura -1
    }
    int alturaEsquerda = calcularAltura(root->left);
    int alturaDireita = calcularAltura(root->right);
    return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;
}

// Função para encontrar o menor valor em uma subárvore
NODE *encontrarMinimo(NODE *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Travessia Pré-ordem
void preOrder(NODE *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Travessia Em ordem
void inOrder(NODE *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Travessia Pós-ordem
void postOrder(NODE *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

// Busca em Largura (BFS)
void breadthFirstSearch(NODE *root) {
    if (root == NULL) {
        return;
    }

    QUEUE *fila = criarFila();
    enfileirar(fila, root);

    while (!filaVazia(fila)) {
        NODE *current = desenfileirar(fila);
        printf("%d ", current->data);

        if (current->left != NULL) {
            enfileirar(fila, current->left);
        }
        if (current->right != NULL) {
            enfileirar(fila, current->right);
        }
    }
}

// Funções auxiliares para fila
QUEUE *criarFila() {
    QUEUE *fila = (QUEUE *)malloc(sizeof(QUEUE));
    fila->front = NULL;
    fila->rear = NULL;
    return fila;
}

void enfileirar(QUEUE *fila, NODE *treeNode) {
    QUEUE_NODE *novoNo = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));
    novoNo->treeNode = treeNode;
    novoNo->next = NULL;

    if (fila->rear == NULL) {
        fila->front = novoNo;
        fila->rear = novoNo;
    } else {
        fila->rear->next = novoNo;
        fila->rear = novoNo;
    }
}

NODE *desenfileirar(QUEUE *fila) {
    if (fila->front == NULL) {
        return NULL;
    }

    QUEUE_NODE *temp = fila->front;
    NODE *treeNode = temp->treeNode;
    fila->front = fila->front->next;

    if (fila->front == NULL) {
        fila->rear = NULL;
    }
    free(temp);
    return treeNode;
}

int filaVazia(QUEUE *fila) {
    return fila->front == NULL;
}
