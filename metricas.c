#include <stdio.h>
#include "metricas.h"

void calcularMetricas(Processo *p, int n) {
    double tTurn = 0, tWait = 0, tResp = 0;
    int fim = 0;

    for(int i = 0; i < n; i++) {
        p[i].turnaround = p[i].tempoTermino - p[i].tempoChegada;
        p[i].waiting = p[i].turnaround - p[i].duracao;
        p[i].response = p[i].tempoInicio - p[i].tempoChegada;

        tTurn += p[i].turnaround;
        tWait += p[i].waiting;
        tResp += p[i].response;

        if(p[i].tempoTermino > fim) fim = p[i].tempoTermino;
    }

    printf("\nMédias:\n");
    printf("Turnaround: %.2f\n", tTurn / n);
    printf("Waiting: %.2f\n", tWait / n);
    printf("Response: %.2f\n", tResp / n);
    printf("Throughput: %.2f\n", (double)n / fim);
}
