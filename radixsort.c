/*
                             Trabalho 3 de ICC 2 - Radix Sort

                    Vin�cius Marques Stocco - n� USP: 6427233 - Professora: Rosane Minghim
*/

#include <stdio.h>
#include <stdlib.h>
#define NUM_DIGITOS 7

typedef struct {
    char nro_usp[NUM_DIGITOS+1];
    char nome[50];
} registro;

typedef struct {
    int n;           // n�mero de registros num vetor auxiliar;
    registro *lista; // lista � o vetor com o n�mero "n" de registros;
} registros_aux;

void inicializar(int fn, registros_aux vet_aux[10]) {
    int i;

    // inicializa o tamanho dos vetores auxiliares com zero;
    for (i = 0; i < 10; i++) vet_aux[i].n = 0;

    // l� quantos registros ser�o inseridos;
    //scanf ("%d", &fn);

    // aloca a quantidade m�xima que um vetor auxiliar pode armazenar, que � igual � "fn";
    for (i = 0; i < 10; i++) vet_aux[i].lista = (registro *)malloc(fn*sizeof(registro));
};

void entrada(const int fn, registro vetreg_aux[]) {
    int i;

    for (i = 0; i < fn; i++) {
        printf("Type a number: ");
        scanf ("%s", &vetreg_aux[i].nro_usp);
        printf("Type a name: ");
        scanf ("%s", &vetreg_aux[i].nome);
    }
};

void ordenar(const int fn, registro vetreg_aux[], registros_aux vet_aux[10]) {
    int i,k;
    int l = 0; // representa as posi��es no vetor original;
    int j = 6; // representa a posi��o dos d�gitos;
    int pos;   // um inteiro do n�mero usp;
    int tam;   // n�mero de registros num vetor auxiliar;
    char c;    // um caracter do n�mero usp, que ser� convertido para int (pos);

    while (j != -1) {
        // percorre todos os registros selecionando um caracter e inserindo num vetor auxiliar, de acordo com o valor do caracter;
        for (i = 0; i < fn; i++) {
            c = vetreg_aux[i].nro_usp[j];
            pos = atoi(&c);
            tam = vet_aux[pos].n;
            vet_aux[pos].lista[tam] = vetreg_aux[i];
            vet_aux[pos].n++;
        }


        for (i = 0; i < 10; i++) {
            // verifica se tem algum elemento num vetor auxiliar;
            if (vet_aux[i].n > 0) {
                // copia pro vetor original(vetreg_aux), na posi��o "l", os elementos que est�o no vetor auxiliar;
                for (k = 0; k < vet_aux[i].n; k++, l++) {
                    vetreg_aux[l] = vet_aux[i].lista[k];
                }
                vet_aux[i].n = 0;
            }
        }
        l = 0;
        j--;  // decrementa o d�gito que est� sendo analisado;
    }
};

int main () {

    registros_aux vetores_auxiliares[10]; // vetores auxiliares;
    registro *vetreg;                     // vetor original;
    int j;
    int n;                                // n�mero de registros;

    // l� quantos registros ser�o inseridos(n); inicializa os vetores_auxiliares[i].n com zero; aloca "n" posi��es em cada vetor auxiliar;
    printf("Type the number of inputs:");
    scanf ("%d", &n);
    inicializar(n,vetores_auxiliares);

    // vetor original(vetreg), onde s�o inseridos os registros;
    vetreg = (registro *)malloc(n*sizeof(registro));

    //l� o n�mero usp e o nome;
    entrada(n,vetreg);

    // ordena os registros;
    ordenar(n,vetreg,vetores_auxiliares);

    // exibi os registros ordenados;
    for (j = 0; j < n; j++) printf ("%s %s\n", vetreg[j].nro_usp, vetreg[j].nome);

    // libera a mem�ria alocada;
    for (j = 0; j < 10; j++) free(vetores_auxiliares[j].lista);

    return 0;
}
