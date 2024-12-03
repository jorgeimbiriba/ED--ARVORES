#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
// Estrutura de um n� da �rvore bin�ria
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} NODE;

// Fun��es b�sicas da �rvore bin�ria
NODE *criarNo(int valor);
NODE *inserir(NODE *root, int valor);
NODE *remover(NODE *root, int valor);
NODE *buscar(NODE *root, int valor);
int calcularAltura(NODE *root);

// Fun��es de travessia
void preOrder(NODE *root);
void inOrder(NODE *root);
void postOrder(NODE *root);

// Fun��es auxiliares
NODE *encontrarMinimo(NODE *root);

int main() {
	setlocale(LC_ALL,"Portuguese");
    NODE *root = NULL;

    // Inserindo valores na �rvore
    root = inserir(root, 50);
    root = inserir(root, 30);
    root = inserir(root, 70);
    root = inserir(root, 20);
    root = inserir(root, 40);
    root = inserir(root, 60);
    root = inserir(root, 80);

    printf("Busca Pr�-ordem (Pre-order): ");
    preOrder(root);
    printf("\n");

    printf("Busca Em ordem (In-order): ");
    inOrder(root);
    printf("\n");

    printf("Busca P�s-ordem (Post-order): ");
    postOrder(root);
    printf("\n");

    // Buscando um valor
    int valorBuscado = 40;
    NODE *resultadoBusca = buscar(root, valorBuscado);
    if (resultadoBusca != NULL) {
        printf("Valor %d encontrado na �rvore.\n", valorBuscado);
    } else {
        printf("Valor %d n�o encontrado na �rvore.\n", valorBuscado);
    }

    // Calculando a altura da �rvore
    printf("Altura da �rvore: %d\n", calcularAltura(root));

    // Removendo um n�
    printf("Removendo o valor 30 da �rvore...\n");
    root = remover(root, 30);

    printf("Busca Em ordem (In-order) ap�s remo��o: ");
    inOrder(root);
    printf("\n");

    return 0;
}

// Fun��o para criar um novo n�
NODE *criarNo(int valor) {
    NODE *novoNo = (NODE *)malloc(sizeof(NODE));
    if (novoNo == NULL) {
        printf("Erro: Mem�ria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->data = valor;
    novoNo->left = NULL;
    novoNo->right = NULL;
    return novoNo;
}

// Fun��o para inserir um valor na �rvore
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

// Fun��o para remover um n� da �rvore
NODE *remover(NODE *root, int valor) {
    if (root == NULL) {
        return NULL;
    }

    if (valor < root->data) {
        root->left = remover(root->left, valor);
    } else if (valor > root->data) {
        root->right = remover(root->right, valor);
    } else {
        // Caso 1: N� sem filhos - apenas remove o n�
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Caso 2: N� com um filho - substitui o n� pelo filho
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
        // Caso 3: N� com dois filhos -  substitui o valor pelo menor valor da subarvore direita(ou o maior a esquerda) e remove o no substituto
        NODE *minimo = encontrarMinimo(root->right);
        root->data = minimo->data;
        root->right = remover(root->right, minimo->data);
    }
    return root;
}

// Fun��o para buscar um valor na �rvore
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

// Fun��o para calcular a altura da �rvore
int calcularAltura(NODE *root) {
    if (root == NULL) {
        return -1; // �rvore vazia tem altura -1
    }
    int alturaEsquerda = calcularAltura(root->left);
    int alturaDireita = calcularAltura(root->right);
    return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;
}

// Fun��o para encontrar o menor valor em uma sub�rvore
NODE *encontrarMinimo(NODE *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Travessia Pr�-ordem
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

// Travessia P�s-ordem
void postOrder(NODE *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}
