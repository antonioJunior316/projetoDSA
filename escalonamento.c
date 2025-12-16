#include "escalonamento.h"

void prioridadeNaoPreemptivo(Processo *p, int n) {
    int tempo = 0, completos = 0;
    int usado[n];

    for(int i = 0; i < n; i++) usado[i] = 0;

    while(completos < n) {
        int idx = -1, menor = 999999;

        for(int i = 0; i < n; i++) {
            if(!usado[i] && p[i].tempoChegada <= tempo) {
                if(p[i].prioridade < menor) {
                    menor = p[i].prioridade;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            tempo++;
        } else {
            p[idx].tempoInicio = tempo;
            tempo += p[idx].duracao;
            p[idx].tempoTermino = tempo;
            usado[idx] = 1;
            completos++;
        }
    }
}

void prioridadePreemptivo(Processo *p, int n) {
    int tempo = 0, completos = 0;

    while(completos < n) {
        int idx = -1, menor = 999999;

        for(int i = 0; i < n; i++) {
            if(p[i].tempoChegada <= tempo && p[i].tempoRestante > 0) {
                if(p[i].prioridade < menor) {
                    menor = p[i].prioridade;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            tempo++;
        } else {
            if(!p[idx].iniciado) {
                p[idx].tempoInicio = tempo;
                p[idx].iniciado = 1;
            }

            p[idx].tempoRestante--;
            tempo++;

            if(p[idx].tempoRestante == 0) {
                p[idx].tempoTermino = tempo;
                completos++;
            }
        }
    }
}
