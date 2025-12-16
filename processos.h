#ifndef PROCESSOS_H
#define PROCESSOS_H

typedef struct {
    int id;
    int tempoChegada;
    int duracao;
    int prioridade;
    int tempoRestante;
    int tempoInicio;
    int tempoTermino;
    int turnaround;
    int waiting;
    int response;
    int iniciado;
} Processo;

void inserirProcessos(Processo **p, int *n);
void mostrarProcessos(Processo *p, int n);

#endif
