typedef struct {
    int id;             // Identificador do processo
    int tempoChegada;   // Instante em que o processo chega
    int duracao;        // Tempo total de CPU necessário (burst time)
    int prioridade;     // Menor valor = maior prioridade
    int tempoRestante;  // Para algoritmo preemptivo
    int tempoInicio;    // Para calcular response time
    int tempoTermino;   // Completion time
    int turnaround;     // Turnaround time
    int waiting;        // Waiting time
    int response;       // Response time
    int iniciado;       // Flag se já começou
} Processo;