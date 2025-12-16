#include <stdio.h>
#include <stdlib.h>
#include "processos.h"
#include "escalonamento.h"
#include "metricas.h"

int main() {
    Processo *p;
    int n, opcao;

    inserirProcessos(&p, &n);

    printf("\n1 - Prioridade Não Preemptivo");
    printf("\n2 - Prioridade Preemptivo\n");
    scanf("%d", &opcao);

    if(opcao == 1)
        prioridadeNaoPreemptivo(p, n);
    else
        prioridadePreemptivo(p, n);

    mostrarProcessos(p, n);
    calcularMetricas(p, n);

    free(p);
    return 0;
}
