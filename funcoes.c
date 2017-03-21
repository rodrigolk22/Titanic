#include "header.h"


//Cria um grafo dado o numero de vertices
Graph* criar_grafo (int V, int *tipo, int C, int P, int M) {
    Graph *G = (Graph *)malloc(sizeof(Graph));//Espaco para o grafo
    G->V = V;//Vertices
    G->E = 0;//Inicia sem arestas
    G->C = C;//Capacidade maxima de pessoas na madeira
    G->P = P;//Total de pessoas
    G->M = M;//Total de madeiras
    G->tipo = tipo;
    G->listadj = (Node **)malloc(V * sizeof (Node *));
    int v;
    for (v = 0; v < V; v++){
        G->listadj[v] = NULL;
    }
    //Inicializa a matrix de adjacencia
    G->matrixadj = inicializa_matriz_de_adjacencias (V, V, 0);
    #ifdef DEBUG3
    printf("\n      Criar grafo:  Grafo criado com sucesso\n");
    #endif
    return G;
}
//inicializa a matriz de adjacencias
int **inicializa_matriz_de_adjacencias (int r, int c, int w) {
    int i, j;
    int **mat = malloc( r * sizeof (int *));
    for (i = 0; i < r; i++){
        mat[i] = malloc( c * sizeof (int));
    }
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
        mat[i][j] = w;
        }
    }
    #ifdef DEBUG3
    printf("\n          Inicializa_matriz_de_adjacencias: Matriz de adjacencia criada com sucesso\n");
    #endif
    return mat;
}
//Adiciona aresta
void adicionar_aresta (Graph *G, int u, int v) {
    Node *aux;
    #ifdef DEBUG3
    printf("\n      Adicionar aresta: Adicionando aresta %d -> %d\n", u, v);
    #endif
    for (aux = G->listadj[u-1]; aux != NULL; aux = aux->proximo){
        if (aux->id == v){
            #ifdef DEBUG3
            printf("\n          Adicionar aresta:  Aresta ja existe na lista de adjacencia!\n");
            #endif
            return;
        }
    }

    //Cria o vertice
    G->listadj[u-1] = criar_vertice (v, G->listadj[u-1], G->tipo[v-1]);
    //Adiciona o peso na matriz de adjacencias
    G->matrixadj[u-1][v] = 1;

    //Acrescenta o numero  de arestas
    G->E++;
    #ifdef DEBUG3
    printf("\n          Adicionar aresta:  Aresta adicionada com sucesso\n");
    #endif
}

//Cria novo vertice
Node* criar_vertice (int v, Node *lista, int tipo) {
    #ifdef DEBUG3
    printf("\n      Criar vertie: Criando o vertice de ID %d do tipo ", v);
    if(tipo == 1){printf("Gelo\n");}
    if(tipo == 2){printf("Iceberg\n");}
    if(tipo == 3){printf("Pessoa\n");}
    if(tipo == 4){printf("Madeira\n");}
    #endif
    Node *novo = (Node *)malloc(sizeof(Node));
    novo->id = v;
    novo->proximo = lista;
    return novo;
}

//Funcao principal que calcula quantas pessoas podem ser salvas
int salvo(Graph *G){
    #ifdef DEBUG4
    printf("\nSalvo: iniciando\n");
    #endif
    //Quantidade total de pessoas salvas
    int resposta = 0;
    //Quantidade de pessoas ja salvas daquela madeira
    int mad_ocupada = 0;
    //Verifica caminho valido
    int valido = 0;
    //Leitor
    int i = 0;
    #ifdef DEBUG4
    printf("\n  Salvo: Verificando existencia de madeiras\n");
    #endif
    //Enquanto tiver madeira com espaco e pessoas a serem salvas
    while(i<G->V && resposta<G->P){
        #ifdef DEBUG4
        printf("\n  Salvo: Vertice %d tipo %d\n", i+1, G->tipo[i]);
        #endif
        //Para cada madeira
        if(G->tipo[i] == 4){
            //madeira livre
            mad_ocupada = 0;
            #ifdef DEBUG4
            printf("\n  Salvo: Madeira encontrada\n");
            #endif
            //Enquanto tiver espaco na madeira e ainda tiver pessoas para salvar
            while(mad_ocupada < G->C && resposta < G->P){
                #ifdef DEBUG4
                printf("\n      Salvo: procurando caminho valido\n");
                #endif
                //funcao tentar salvar uma pessoa retorna zero caso nao consiga
                valido = tenta_salvar(G, i+1);//Manda o ID do vertice da madeira
                if(valido == 1){
                    //atualiza o espaco
                    mad_ocupada++;
                    resposta++;
                    #ifdef DEBUG4
                    printf("\n      Salvo: pessoa salva!\n");
                    #endif
                }//Nao ha caminho valido
                else {
                    #ifdef DEBUG4
                    printf("\n  Salvo: Nao ha caminho valido para essa madeira\n\nPessoas salvas: %d\n", mad_ocupada);
                    #endif
                    i++;//avanca manualmente o leitor para proximo vertice
                    break;//para a busca na madeira atual

                }
            }
        }
        else{
            i++;
        }
    }
    #ifdef DEBUG4
    printf("\nSalvo: retornando resposta %d\n", resposta);
    #endif
    return resposta;
}

//Procura um caminho valido para salvar
int tenta_salvar(Graph *G, int id_madeira){
    #ifdef DEBUG4
    printf("\n      Tenta salvar: iniciando madeira %d \n", id_madeira);
    #endif
    int salvo = 0;
    int i = 0;
    int *visitado = (int *)malloc(G->V * sizeof(int));
    for(i=0;i<G->V;i++){
        visitado[i] = 0;
    }
    visitado[id_madeira] = TRUE;
    #ifdef DEBUG4
    printf("\n          Tenta salvar: iniciando a busca %d\n", id_madeira);
    #endif

    salvo = busca(G, id_madeira, visitado);

    #ifdef DEBUG4
    printf("\n      Tenta salvar: fim da busca\n");
    #endif
    return salvo;
}
int busca(Graph *G, int vertice, int *visitado){
    int resultado = 0;
    Node *v = G->listadj[vertice-1];
    #ifdef DEBUG4
    printf("\n          Busca: Vertice: %d tipo %d\n", vertice, G->tipo[vertice-1]);
    #endif
    //Se for pessoa adiciona na fila e retorna verdade
    if(G->tipo[vertice-1] == 3){
        #ifdef DEBUG4
        printf("\n              Busca: Achou! Deve retornar 1\n");
        #endif
        //Arruma seu tipo atual
        G->tipo[vertice-1] = 0;
        return TRUE;
    }//Tipo agua
    else if(G->tipo[vertice-1] == 0){
        #ifdef DEBUG4
        printf("\n              Busca: Encontrou agua retorna 0\n");
        #endif
        return FALSE;
    }
    else{//Enquanto ha um vertice adjacente
        while(v != NULL){
            #ifdef DEBUG4
            printf("\n              Busca: Lendo adjacente %d visitado %d\n", v->id, visitado[v->id]);
            #endif
            //Verifica se foi visitado
            if(visitado[v->id] == FALSE){
                //marca como visitado
                visitado[v->id] = TRUE;

                //Efetua a recursividade
                resultado = busca (G, v->id, visitado);
                #ifdef DEBUG4
                printf("\n              Busca: recursividade %d resultado: %d\n", v->id, resultado);
                #endif
                //Se algum adjacente retorna TRUE entao ele tambem faz parte do caminho
                if(resultado == 1){
                    //Atualiza seu tipo atual se for gelo ele quebra
                    if(G->tipo[vertice-1] == 1){
                        G->tipo[vertice-1] = 0;
                    }
                    return TRUE;
                }

            }

            v = v->proximo;
        }
        #ifdef DEBUG4
        printf("\n              Busca: Todos adjacentes ja foram visitados retorna 0\n");
        #endif
        return FALSE;
    }
}

