#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

#define TAM 30300
void create_matriz();
int carrega_genoma();
void *compara_genoma(void *arg);
int display_result();
void *compara_sequencia(void *arg);

int igual, dif, NUMTHREAD;
char genoma[10][TAM];
int equals[10][10];
int sequence[10][10];


int main(int argc, char *argv[])
{
    tempo1();
    NUMTHREAD = atoi(argv[1]);

    if (NUMTHREAD == 0)
    {
      create_matriz();
      carrega_genoma();
      modo_sequencial();
      tempo2();
      display_result();
      tempoFinal("milissegundos", argv[0], MSGLOG);
    }

    if (NUMTHREAD < 1)
    {
        printf("Digite ./nome do executavel + numero de thread");
        return 0;
    }

    pthread_t pidt[NUMTHREAD];
    int x, y, inicio[NUMTHREAD + 1];
    create_matriz();
    carrega_genoma();

    inicio[0] = 0;

    int i;
    for (i = 0; i < NUMTHREAD; i++)
    {
        pthread_create(&pidt[i], NULL, compara_genoma, (void *)&inicio[i]);
        inicio[i + 1] = inicio[i] + TAM / NUMTHREAD;
    }

    for (i = 0; i < NUMTHREAD; i++)
        pthread_join(pidt[i], NULL);

    tempo2();
    tempoFinal("milissegundos", argv[0], MSGLOG);

}


void create_matriz()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            equals[i][j] = 0;
            sequence[i][j] = 0;
        }
    }
}

//funcao carrega genomas
//===============================================================
int carrega_genoma()
{
    int j = 0;
    int i = 0;
    for(i=0; i<10; i++){
        int aux = i;
        char folder[100] = "genomas/";
        char * file_to_open = strcat(folder, arquivos[aux]);
        file_to_open = strcat(file_to_open, ".txt");
        int j=0;
        char c;

        FILE *file;
        file = fopen(file_to_open,"r");	  
        
        j = 0;        
        while((c=getc(file)) != EOF){                     //le um nucleotideo do primeiro genoma enquanto não chegor ao final do arquivo
        
            genoma[aux][j]=c;   
            j++;
        }
        //fecha arquivo
        fclose(file);
	}

    for(int k=0; k<10; k++ ){
        if (k > 2{
            compara_genoma(genoma[k],genoma[j], k, j)
        })
        j = j + 1;
    }

}

//funcao compara
//  o objetivo desta função é comparar cada genoma entre os arquivos contendo
//os genomas
int *compara_genoma(char genoma1[], char genoma2[], int pos1, int pos2,  void *args)
{       
	int i;
    int igual = 0, dif = 0, aux = 0, res = 0;


    for (int i = 0; i < TAM; i++)
    {
        if (genoma1[i] != NULL)
        {
            if ((genoma1[i] == genoma2[i]))
            {
                aux++;
                igual++;
            }
            else
            {
                if (aux > res)
                {

                    res = aux;
                    inicio = i - res;
                    aux = 0;
                }
                dif++;
            }
        }
    }
    if (aux > res)
    {
        res = aux;
        inicio = i - res;
        aux = 0;
    }
    
    equals[pos1][pos2] = igual; 
    sequence[pos1][pos2] = res;
}

int exibe_resultado()
{

    int i = 0;

    for (i = 0; i < TAM; i++)
    {

        printf("\n | %5d  | %c | %c |", i, genoma1[i], genoma2[i]);
    }

    printf("\n\n | Iguais %-18d \n | Diferentes %-18d ", igual, dif);

    printf("\n\n");
}

// o resultado esperado por esta função é compara a sequencia de genomas mais
//encontrados durante a execução da função compara_genoma
void *compara_sequencia(void *arg)
{

    int i = 0, j = 0, igual = 0, inicio = 0, qtde = 0, pos = *((int *)arg);

    for (i = 0, j = 0; i < (TAM / NUMTHREAD + pos); i++, j++)
    {

        if (genoma1[i] == genoma2[j])
        {
            igual++;
        }
        else
        {

            if (igual > qtde)
            {

                qtde = igual;
                inicio = i - qtde;
                igual = 0;

                printf("\n i = %-8d | inicio = %-8d | qtde = %-8d | ", i, inicio, qtde);
            }
        }
    }
    printf("\n\n");
}

void display_result()
{
    int maior=0;

    printf("\n MATRIZ DE RESULTADOS\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(maior<sequence[i][j]){
                maior= sequence[i][j];    
            }
            printf(" %5d|", sequence[i][j]);
        }
        printf("\n");
    }
    printf("\nMaior sequência de todas = %d, \n",maior);
}
