#include "header.h"

/*
Down Went the Titanic
Rodrigo Luiz Kovalski
Guilherme Goetten
Davi Pereira
*/


int main(){
    //Ponteiros auxiliares
    int i, j, h, dir1, dir2, dir3, dir4 = 0;
    int total = 0;
    int leitor = 0;

    //Guarda os trechos do arquivo lido
    char *trecho;
    //Indica onde os trechos devem ser guardados
    int indicador = 0;
    int X = 0;//Linhas
    int Y = 0;//Colunas
    int C = 0;//Capacidade maxima(P)
    int pessoa = 0;//Pessoas
    int madeira = 0;//Madeiras
    int iceberg = 0;//Icebergs
    int gelo = 0;//Gelo
    int agua = 0;//Agua
    int vertice = 0;
    int resposta = 0;//Resposta a imprimir


    //arquivos de entrada e saida
    FILE *arqin, *arqout;

    #ifdef DEBUG
    printf("\nMain: Comecou!\n");
    #endif
///----------------------------------------Pegando os valores do arquivo
    //Abre o arquivo de entrada
    arqin = fopen("entrada.txt","r");
    if(arqin==NULL) printf("Problema ao abrir o arquivo de entrada\n");
    #ifdef DEBUG
    printf("\nMain: Arquivos Abertos!\n");
    #endif
    //Le o arquivo de entrada e armazena no vetor auxiliar
    while(!feof(arqin)){
        fgets(aux[total], LARGURA, arqin);
        total++;
    }
    //Fecha o arquivo de entrada
    fclose(arqin);
    #ifdef DEBUG2
    printf("\n  Lidos %d nomes\n",total);
    for(i=0;i<total;i++){
        printf("%s\n", aux[i]);
    }
    #endif
///---------------------------------------------- Montando os Grafos
    while(leitor<total){
        //inicalizando valores
        vertice = 0;//Vertices
        pessoa = 0;//Pessoas
        madeira = 0;//Madeiras
        iceberg = 0;//Icebergs
        gelo = 0;//Gelo
        agua = 0;//Agua
        //lendo a linha dos parametros gerais
        #ifdef DEBUG
        printf("\Main: Primeiros parametros\n");
        #endif
        indicador = 0;
        trecho = strtok (aux[leitor]," ");
        while (trecho != NULL){
            #ifdef DEBUG2
            printf ("   %s\n",trecho);
            #endif
            //Aloca nas instacias
            switch(indicador){
                case 0: X = atoi(trecho);break;
                case 1: Y = atoi(trecho);break;
                case 2: C = atoi(trecho);break;
            }
            trecho = strtok (NULL, " ");
            indicador++;
        }
        leitor++;//desce uma linha
        #ifdef DEBUG2
        printf("\n  X(linhas) = %d, Y(colunas) = %d, P(capacidade maxima pessoas) = %d\n", X, Y, C);
        #endif
        //Também irá guardar o valor do tipo de cada vetor pela ordem de leitura
        int mapaVertice[X][Y];//Enumera os ID para ter a referencia na hora de criar as arestas
        int tipo[X*Y];//guarda os tipos, a posicao corresponde ao ID do vertice
        h = 0;//Orienta o vetor de tipo
        //Para cada linha irá ler o texto
        for(i = leitor; i<(leitor+X);i++){
            indicador = 0;
            while (indicador < Y){
                j = aux[i][indicador];
                #ifdef DEBUG2
                printf ("   %d %d - %c %d ", leitor, indicador,j, j);
                #endif
                //Aloca nas instacias
                switch(j){
                    case 42://Pessoa
                        #ifdef DEBUG2
                        printf ("pessoa 3\n");
                        #endif
                        tipo[h] = 3;
                        h++;
                        pessoa++;
                        vertice++;
                        mapaVertice[i-leitor][indicador] = vertice;
                        break;
                    case 126://Agua
                        #ifdef DEBUG2
                        printf ("agua 0\n");
                        #endif
                        agua++;
                        mapaVertice[i-leitor][indicador] = 0;
                        break;
                    case 46://Gelo
                        #ifdef DEBUG2
                        printf ("gelo 1\n");
                        #endif
                        tipo[h] = 1;
                        h++;
                        gelo++;
                        vertice++;
                        mapaVertice[i-leitor][indicador] = vertice;
                        break;
                    case 64://Iceberg
                        #ifdef DEBUG2
                        printf ("iceberg 2\n");
                        #endif
                        tipo[h] = 2;
                        h++;
                        iceberg++;
                        vertice++;
                        mapaVertice[i-leitor][indicador] = vertice;
                        break;
                    case 35://Madeira
                        #ifdef DEBUG2
                        printf ("madeira 4\n");
                        #endif
                        tipo[h] = 4;
                        h++;
                        madeira++;
                        vertice++;
                        mapaVertice[i-leitor][indicador] = vertice;
                        break;
                }
                indicador++;
            }
        }

        #ifdef DEBUG2
        printf("\n  Main: Pessoas = %d\n", pessoa);
        printf("\n  Main: Aguas = %d\n", agua);
        printf("\n  Main: Gelos = %d\n", gelo);
        printf("\n  Main: Icebergs = %d\n", iceberg);
        printf("\n  Main: Madeiras = %d\n", madeira);
        printf("\n  Main: Vertices (Todos menos agua) = %d\n", vertice);
        printf("\n  Main: Lista dos tipos por ID\n\n");
        for(i=0;i<vertice;i++){
            printf("%d", tipo[i]);
        }
        printf("\n  Main: Mapa dos Vertices\n\n");
        for(i=0;i<X;i++){
            for(j=0;j<Y;j++){
                printf("%d", mapaVertice[i][j]);
            }
            printf("\n");
        }
        #endif
///---------------------------------------------------------Criando Grafo
        #ifdef DEBUG
        printf("\nMain: Criando Grafo\n");
        #endif
        Graph *G = criar_grafo (vertice, tipo, C, pessoa, madeira);
        for(i = leitor; i<(leitor+X);i++){
            indicador = 0;
            while (indicador < Y){
                j = mapaVertice[i-leitor][indicador];//se o ponto nao for gelo ou fora da matriz
                #ifdef DEBUG2
                printf("\n  Lendo Vertice %d x=%d y=%d\n", j, i-leitor, indicador);
                #endif
                if(j != 0 && j != NULL){
                    dir1 = mapaVertice[i-leitor-1][indicador];//Pega adjacente acima
                    dir2 = mapaVertice[i-leitor][indicador+1];//Pega adjacente a direita
                    dir3 = mapaVertice[i-leitor+1][indicador];//Pega adjacente de baixo
                    dir4 = mapaVertice[i-leitor][indicador-1];//Pega adjacente a esquerda
                    //verifica e manda criar a aresta
                    //Acima
                    if(dir1 != 0 && dir1 != NULL && i-leitor-1>=0){
                        #ifdef DEBUG2
                        printf("\n  Acima - %d -> %d\n", j, dir1);
                        printf("\n  Ax=%d Ay=%d Bx=%d By=%d\n", i-leitor, indicador, i-leitor-1, indicador);
                        #endif
                        adicionar_aresta(G, j, dir1);
                    }
                    //Direita
                    if(dir2 != 0 && dir2 != NULL && indicador+1<=Y-1){
                        #ifdef DEBUG2
                        printf("\n  Direita - %d -> %d\n", j, dir2);
                        printf("\n  x=%d y=%d\n", i-leitor, indicador+1);
                        #endif
                        adicionar_aresta(G, j, dir2);
                    }
                    //Abaixo
                    if(dir3 != 0 && dir3 != NULL && i-leitor+1<=X-1){
                        #ifdef DEBUG2
                        printf("\n  Abaixo -  %d -> %d\n", j, dir3);
                        printf("\n  x=%d y=%d\n", i-leitor+1, indicador);
                        #endif
                        adicionar_aresta(G, j, dir3);
                    }
                    //Esquerda
                    if(dir4 != 0 && dir4 != NULL && indicador-1>=0){
                        #ifdef DEBUG2
                        printf("\n  Esquerda - %d -> %d\n", j, dir4);
                        printf("\n  x=%d y=%d\n", i-leitor, indicador-1);
                        #endif
                        adicionar_aresta(G, j, dir4);
                    }
                }
            indicador++;
            }
        }
///-------------------------------------------------------Efetua os calculos
        //Calcula a resposta
        #ifdef DEBUG
        printf("\nMain: Executando o algoritmo:\n");
        #endif
        resposta = salvo(G);
///---------------------------------------------Salvando resposta em arquivo
        #ifdef DEBUG
        printf("\nMain: Salvando dado em arquivo\n");
        #endif
        arqout = fopen("saida.txt","a+");
        if(arqout==NULL) printf("Problema ao criar o arquivo de saida\n");
        fprintf(arqout, "%d\n", resposta);
        fclose(arqout);
        #ifdef DEBUG
        printf("\nMain: Dados salvos em arquivo\n");
        #endif
///---------------------------------------------Liberando memoria
        #ifdef DEBUG
        printf("\nMain: Liberando memoria\n");
        #endif
        free(G->listadj);
        for(i=0; i<vertice;i++){
            free(G->matrixadj[i]);
        }
        free(G->matrixadj);
        free(G);

        //ajusta a leitura para a proxima instancia
        leitor += X+1;
        #ifdef DEBUG
        printf("\nMain: Leitura da proxima instancia se existir\n");
        #endif


    }

    #ifdef DEBUG
    printf("\nMain: Fim do programa\n");
    #endif

    return 0;
}
