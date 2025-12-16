#include <stdio.h>
#include <stdlib.h>

#include "Processo.h"


void inserirProcessos(Processo **p, int *n) {
    printf("Digite o número de processos: ");
    scanf("%d", n);
    *p = (Processo *)malloc(sizeof(Processo) * (*n));
    for(int i=0;i<*n;i++){
        (*p)[i].id = i+1;
        printf("processo %d:\n", i+1);
        printf("tempo de chegada: "); scanf("%d", &(*p)[i].tempoChegada);
        printf("duração (Burst time): "); scanf("%d", &(*p)[i].duracao);
        printf("prioridade (menor valor = maior prioridade): "); scanf("%d", &(*p)[i].prioridade);
        (*p)[i].tempoRestante = (*p)[i].duracao;
        (*p)[i].iniciado = 0;
    }
}

void calcularMetricas(Processo *p, int n) {
    double somaTurnaround=0, somaWaiting=0, somaResponse=0;
    int maxTermino=0;
    for(int i=0;i<n;i++){
        p[i].turnaround = p[i].tempoTermino - p[i].tempoChegada;
        p[i].waiting = p[i].turnaround - p[i].duracao;
        p[i].response = p[i].tempoInicio - p[i].tempoChegada;
        somaTurnaround += p[i].turnaround;
        somaWaiting += p[i].waiting;
        somaResponse += p[i].response;
        if(p[i].tempoTermino > maxTermino) maxTermino = p[i].tempoTermino;
    }
    printf("\nMétricas do Algoritmo:\n");
    printf("Média Turnaround: %.2f\n", somaTurnaround/n);
    printf("Média Waiting: %.2f\n", somaWaiting/n);
    printf("Média Response: %.2f\n", somaResponse/n);
    printf("Throughput: %.2f processos/unidade de tempo\n", (double)n/maxTermino);
}

void mostrarProcessos(Processo *p, int n) {
    printf("\nTabela de Processos:\n");
    printf("ID | Chegada | Duração | Prioridade | Início | Término | Turnaround | Waiting | Response\n");
    for(int i=0;i<n;i++){
        printf("%2d | %7d | %7d | %9d | %6d | %7d | %10d | %7d | %8d\n",
               p[i].id, p[i].tempoChegada, p[i].duracao, p[i].prioridade,
               p[i].tempoInicio, p[i].tempoTermino, p[i].turnaround, p[i].waiting, p[i].response);
    }
}

void prioridadeNaoPreemptivo(Processo *p, int n) {
    int tempo = 0, processosCompletos = 0;
    int escolhidos[n]; 
    for(int i=0;i<n;i++) escolhidos[i]=0;

    while(processosCompletos < n){
        int menorPrioridade = 1000000;
        int idx = -1;
        for(int i=0;i<n;i++){
            if(!escolhidos[i] && p[i].tempoChegada <= tempo){
                if(p[i].prioridade < menorPrioridade){
                    menorPrioridade = p[i].prioridade;
                    idx = i;
                }
            }
        }
        if(idx == -1){ 
            tempo++;
        } else {
            p[idx].tempoInicio = tempo;
            tempo += p[idx].duracao;
            p[idx].tempoTermino = tempo;
            escolhidos[idx] = 1;
            processosCompletos++;
        }
    }
}

void prioridadePreemptivo(Processo *p, int n) {
    int tempo = 0, processosCompletos = 0;
    while(processosCompletos < n){
        int menorPrioridade = 1000000;
        int idx = -1;
        for(int i=0;i<n;i++){
            if(p[i].tempoChegada <= tempo && p[i].tempoRestante > 0){
                if(p[i].prioridade < menorPrioridade){
                    menorPrioridade = p[i].prioridade;
                    idx = i;
                }
            }
        }
        if(idx == -1){
            tempo++;
        } else {
            if(!p[idx].iniciado){
                p[idx].tempoInicio = tempo;
                p[idx].iniciado = 1;
            }
            p[idx].tempoRestante--;
            tempo++;
            if(p[idx].tempoRestante == 0){
                p[idx].tempoTermino = tempo;
                processosCompletos++;
            }
        }
    }
}

int main() {
    Processo *processos;
    int n, opcao;

    inserirProcessos(&processos, &n);

    printf("\nescolha o algoritmo de escalonamento:\n");
    printf("1 - prioridade Não Preemptivo\n");
    printf("2 - prioridade Preemptivo\n");
    printf("opção: ");
    scanf("%d", &opcao);

    if(opcao == 1) prioridadeNaoPreemptivo(processos, n);
    else if(opcao == 2) prioridadePreemptivo(processos, n);
    else {
        printf("Opção inválida.\n");
        free(processos);
        return 1;
    }

    mostrarProcessos(processos, n);
    calcularMetricas(processos, n);

    free(processos);
    return 0;
}