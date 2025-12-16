#include <stdio.h>
#include <stdlib.h>
#include "processos.h"

void inserirProcessos(Processo **p, int *n) {
    printf("Digite o número de processos: ");
    scanf("%d", n);

    *p = (Processo *)malloc(sizeof(Processo) * (*n));

    for(int i = 0; i < *n; i++) {
        (*p)[i].id = i + 1;
        printf("\nProcesso %d\n", i + 1);
        printf("Tempo de chegada: ");
        scanf("%d", &(*p)[i].tempoChegada);
        printf("Duração (Burst): ");
        scanf("%d", &(*p)[i].duracao);
        printf("Prioridade (menor = maior prioridade): ");
        scanf("%d", &(*p)[i].prioridade);

        (*p)[i].tempoRestante = (*p)[i].duracao;
        (*p)[i].iniciado = 0;
    }
}

void mostrarProcessos(Processo *p, int n) {
    printf("\nID | Cheg | Dur | Pri | Início | Fim | Turn | Wait | Resp\n");
    for(int i = 0; i < n; i++) {
        printf("%2d | %4d | %3d | %3d | %6d | %3d | %4d | %4d | %4d\n",
            p[i].id, p[i].tempoChegada, p[i].duracao, p[i].prioridade,
            p[i].tempoInicio, p[i].tempoTermino,
            p[i].turnaround, p[i].waiting, p[i].response);
    }
}
