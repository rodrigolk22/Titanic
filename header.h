#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LINHAS 15
#define LARGURA 30
#define MADEIRA_MAX 10
#define PESSOA_MAX 10


#define TRUE 1
#define FALSE 0

#define DEBUG//Informacoes gerais
#define DEBUG2//Detalhes da leitura da entrada
#define DEBUG3//Informacoes das funcoes
#define DEBUG4//Funcao salvo e subfuncoes


char aux [LINHAS][LARGURA];//armazena dados do arquivo

//Lista encadeada para guardar os vizinhos de cada no
typedef struct node {
    int id;//identificação do vértice
    struct node *proximo;
} Node;

typedef struct graph {
    int V;//Numero de vértices no Grafo
    int E;//Numero de arestas no Grafo
    int C;//Capacidade Maxima de pessoas na madeira
    int P;//Total de pessoas
    int M;//Total de madeiras
    int *tipo;//Agua = 0, Gelo = 1, Iceberg = 2, Pessoa = 3, Madeira = 4
    Node **listadj;//Lista de adjacencias
    int **matrixadj;//Matriz de adjacencias
} Graph;



//Funcoes de grafos
Graph* criar_grafo (int V, int *tipo, int C, int P, int M);
void adicionar_aresta (Graph *G, int u, int v);
int **inicializa_matriz_de_adjacencias (int r, int c, int w);
Node* criar_vertice (int v, Node *lista, int tipo);

//Funcoes do algortimo
int salvo(Graph *G);
int tenta_salvar(Graph *G, int id_madeira);
int busca(Graph *G, int vertice, int *visitado);





