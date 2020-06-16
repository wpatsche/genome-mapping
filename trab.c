#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

#define TAM 30300

int carrega_genoma();
void *compara_genoma(void *arg);
int exibe_resultado();
void *compara_sequencia(void *arg);

int igual, dif, NUMTHREAD;
char genoma1[TAM];
char genoma2[TAM];
char genoma3[TAM];
char genoma4[TAM];
char genoma5[TAM];
char genoma6[TAM];
char genoma7[TAM];
char genoma8[TAM];
char genoma9[TAM];
char genoma10[TAM];

int main(int argc, char *argv[])
{

    NUMTHREAD = atoi(argv[1]);

    if (NUMTHREAD < 1)
    {
        printf("Digite ./nome do executavel + numero de thread");
        return 0;
    }

    pthread_t pidt[NUMTHREAD];
    int x, y, inicio[NUMTHREAD + 1];

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

    exibe_resultado();

    inicio[0] = 0;

    for (i = 0; i < NUMTHREAD; i++)
    {
        pthread_create(&pidt[i], NULL, compara_sequencia, (void *)&inicio[i]);
        inicio[i + 1] = inicio[i] + TAM / NUMTHREAD;
    }
}

//funcao carrega genomas
//===============================================================
int carrega_genoma()
{

    int i = 0;
    char c;

    //genoma 1
    FILE *file1;

    //abre arquivo para leitura
    file1 = fopen("genomas/AY278741.txt", "r");

    //carrega o conteudo do arquivo no vetor genoma1
    i = 0;
    while ((c = getc(file1)) != EOF)
    { //le um nucleotideo do primeiro genoma enquanto não chegor ao final do arquivo

        genoma1[i] = c;
        i++;
    }

    //fecha arquivo
    fclose(file1);

    //genoma 2
    FILE *file2;

    //abre arquivo para leitura
    file2 = fopen("genomas/KY417146.txt", "r");

    //carrega o conteudo do arquivo no vetor genoma1
    i = 0;
    while ((c = getc(file2)) != EOF)
    {

        genoma2[i] = c;
        i++;
    }

    //fecha arquivo
    fclose(file2);

    // arq 3
    FILE *file3;
    file3 = fopen("genomas/MK211376.txt", "r");

    i = 0;
    while ((c = getc(file3)) != EOF)
    {

        genoma3[i] = c;
        i++;
    }
    fclose(file3);

    //arq 4
    FILE *file4;
    file4 = fopen("genomas/MN908947.txt", "r");

    i = 0;
    while ((c = getc(file4)) != EOF)
    {

        genoma4[i] = c;
        i++;
    }
    fclose(file4);

    //arq 5
    FILE *file5;
    file5 = fopen("genomas/MN996532.txt", "r");

    i = 0;
    while ((c = getc(file5)) != EOF)
    {

        genoma5[i] = c;
        i++;
    }
    fclose(file5);

    //arq 6
    FILE *file6;
    file6 = fopen("genomas/USA-AZ1-2020.txt", "r");

    i = 0;
    while ((c = getc(file6)) != EOF)
    {

        genoma6[i] = c;
        i++;
    }
    fclose(file6);

    //arq 7
    FILE *file7;
    file7 = fopen("genomas/USA-CA1-2020.txt", "r");

    i = 0;
    while ((c = getc(file7)) != EOF)
    {

        genoma7[i] = c;
        i++;
    }
    fclose(file7);

    //arq 8
    FILE *file8;
    file8 = fopen("genomas/USA-IL1-2020.txt", "r");

    i = 0;
    while ((c = getc(file8)) != EOF)
    {

        genoma8[i] = c;
        i++;
    }
    fclose(file8);

    //arq 9
    FILE *file9;
    file9 = fopen("genomas/USA-TX1-2020.txt", "r");

    i = 0;
    while ((c = getc(file9)) != EOF)
    {

        genoma9[i] = c;
        i++;
    }
    fclose(file9);

    //arq 10
    FILE *file10;
    file10 = fopen("genomas/WHUHAN-WH04-2020.txt", "r");

    i = 0;
    while ((c = getc(file10)) != EOF)
    {

        genoma10[i] = c;
        i++;
    }
    fclose(file10);
}

//funcao compara
//  o objetivo desta função é comparar cada genoma entre os arquivos contendo
//os genomas
void *compara_genoma(void *arg)
{
    int i = 0, x = 0, pos = *((int *)arg);

    igual = 0;
    dif = 0;

    printf("\n thread inicia na pos: %d", pos);

    for (i = 0; i < (TAM / NUMTHREAD + pos); i++)
    {

        //para fazer a soma dos numeros, devera ser idependente de acordo com cada
        // comparação, a dica é fazer uma matriz para guardar os resultados

        //pode fazer um switch case ao invés do if

        if (genoma1[i] == genoma2[i])
        { //compara os dois nucleotideos
            igual++;
        }
        else
        {
            dif++;
            //scanf("%d", &x);
            //sleep(1);
        }
    }
}

//exibe resultado
//===============================================================
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
