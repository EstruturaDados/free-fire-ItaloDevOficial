#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 20

// ----------------------
// Struct
// ----------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // prioridade de 1 a 10
} Componente;

// ----------------------
// Protótipos
// ----------------------
void adicionarComponente(Componente lista[], int *qtd);
void descartarComponente(Componente lista[], int *qtd);
void listarComponentes(Componente lista[], int qtd);
int buscarComponentePorNome(Componente lista[], int qtd, char *nome, int *comparacoes);
void printCabecalho();

// Algoritmos de ordenação
void bubbleSortNome(Componente lista[], int n, int *comparacoes);
void insertionSortTipo(Componente lista[], int n, int *comparacoes);
void selectionSortPrioridade(Componente lista[], int n, int *comparacoes);

// Busca binária
int buscaBinariaPorNome(Componente lista[], int n, char chave[], int *comparacoes);

// Medição de tempo
void medirTempo(void (*algoritmo)(Componente[], int, int*), Componente lista[], int n, int *comparacoes);

// ----------------------
// Função principal
// ----------------------
int main() {
    Componente lista[MAX_ITENS];
    int qtd = 0;
    int opcao, subOpcao;
    char chave[30];
    int comparacoes;

    do {
        printCabecalho();
        printf("1 - Adicionar componente\n");
        printf("2 - Descartar componente\n");
        printf("3 - Listar componentes (inventário)\n");
        printf("4 - Organizar mochila\n");
        printf("5 - Busca binária por componente-chave (por nome)\n");
        printf("6 - Ativar torre de fuga (sair)\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {
            case 1:
                adicionarComponente(lista, &qtd);
                break;
            case 2:
                descartarComponente(lista, &qtd);
                break;
            case 3:
                listarComponentes(lista, qtd);
                break;
            case 4:
                // Sub-menu de ordenação
                printf("\n--- ORGANIZAR MOCHILA ---\n");
                printf("1 - Ordenar por nome (Bubble Sort)\n");
                printf("2 - Ordenar por tipo (Insertion Sort)\n");
                printf("3 - Ordenar por prioridade (Selection Sort)\n");
                printf("Escolha uma opção: ");
                scanf("%d", &subOpcao);
                getchar();
                comparacoes = 0;
                switch(subOpcao) {
                    case 1:
                        medirTempo(bubbleSortNome, lista, qtd, &comparacoes);
                        printf("Bubble Sort concluído. Comparações: %d\n", comparacoes);
                        listarComponentes(lista, qtd);
                        break;
                    case 2:
                        medirTempo(insertionSortTipo, lista, qtd, &comparacoes);
                        printf("Insertion Sort concluído. Comparações: %d\n", comparacoes);
                        listarComponentes(lista, qtd);
                        break;
                    case 3:
                        medirTempo(selectionSortPrioridade, lista, qtd, &comparacoes);
                        printf("Selection Sort concluído. Comparações: %d\n", comparacoes);
                        listarComponentes(lista, qtd);
                        break;
                    default:
                        printf("[!] Opção inválida!\n");
                }
                break;
            case 5:
                printf("Digite o nome do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';
                comparacoes = 0;
                int idx = buscaBinariaPorNome(lista, qtd, chave, &comparacoes);
                if(idx != -1)
                    printf("[✔] Componente encontrado: %s | %s | %d\n", lista[idx].nome, lista[idx].tipo, lista[idx].prioridade);
                else
                    printf("[!] Componente não encontrado.\n");
                printf("Comparações realizadas na busca binária: %d\n", comparacoes);
                break;
            case 6:
                printf("Ativando torre de fuga... Encerrando sistema.\n");
                break;
            default:
                printf("[!] Opção inválida!\n");
        }
        printf("\n");
    } while(opcao != 6);

    return 0;
}

// ----------------------
// Funções
// ----------------------
void printCabecalho() {
    printf("\n====================================\n");
    printf("      SISTEMA DE COMPONENTES         \n");
    printf("====================================\n");
}

void adicionarComponente(Componente lista[], int *qtd) {
    if(*qtd >= MAX_ITENS) {
        printf("[!] Lista cheia!\n");
        return;
    }

    Componente novo;
    printf("Nome do componente: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do componente: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Prioridade (1-10): ");
    scanf("%d", &novo.prioridade);
    getchar();

    lista[*qtd] = novo;
    (*qtd)++;

    printf("[✔] Componente adicionado com sucesso!\n");
}

void descartarComponente(Componente lista[], int *qtd) {
    if(*qtd == 0) {
        printf("[!] Nenhum componente para descartar.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do componente a descartar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = 0;
    for(int i=0; i<*qtd; i++) {
        if(strcmp(lista[i].nome, nome) == 0) {
            for(int j=i; j<*qtd-1; j++)
                lista[j] = lista[j+1];
            (*qtd)--;
            encontrado = 1;
            printf("[✔] Componente '%s' descartado com sucesso!\n", nome);
            break;
        }
    }
    if(!encontrado) printf("[!] Componente não encontrado.\n");
}

void listarComponentes(Componente lista[], int qtd) {
    if(qtd == 0) {
        printf("[!] Nenhum componente cadastrado.\n");
        return;
    }

    printf("\n================ COMPONENTES ===================\n");
    printf("| %-3s | %-20s | %-15s | %-10s |\n", "Nº", "NOME", "TIPO", "PRIORIDADE");
    printf("---------------------------------------------------------------\n");
    for(int i=0; i<qtd; i++)
        printf("| %-3d | %-20s | %-15s | %-10d |\n", i+1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    printf("---------------------------------------------------------------\n");
}

// ----------------------
// Ordenações
// ----------------------
void bubbleSortNome(Componente lista[], int n, int *comparacoes) {
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++) {
            (*comparacoes)++;
            if(strcmp(lista[j].nome, lista[j+1].nome) > 0) {
                Componente tmp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = tmp;
            }
        }
}

void insertionSortTipo(Componente lista[], int n, int *comparacoes) {
    for(int i=1; i<n; i++) {
        Componente key = lista[i];
        int j = i-1;
        while(j>=0) {
            (*comparacoes)++;
            if(strcmp(lista[j].tipo, key.tipo) > 0) {
                lista[j+1] = lista[j];
                j--;
            } else break;
        }
        lista[j+1] = key;
    }
}

void selectionSortPrioridade(Componente lista[], int n, int *comparacoes) {
    for(int i=0; i<n-1; i++) {
        int min_idx = i;
        for(int j=i+1; j<n; j++) {
            (*comparacoes)++;
            if(lista[j].prioridade < lista[min_idx].prioridade)
                min_idx = j;
        }
        if(min_idx != i) {
            Componente tmp = lista[i];
            lista[i] = lista[min_idx];
            lista[min_idx] = tmp;
        }
    }
}

// ----------------------
// Busca binária
// ----------------------
int buscaBinariaPorNome(Componente lista[], int n, char chave[], int *comparacoes) {
    int inicio=0, fim=n-1;
    while(inicio <= fim) {
        int meio = (inicio + fim)/2;
        (*comparacoes)++;
        int cmp = strcmp(lista[meio].nome, chave);
        if(cmp == 0) return meio;
        else if(cmp < 0) inicio = meio+1;
        else fim = meio-1;
    }
    return -1;
}

// ----------------------
// Medição de tempo
// ----------------------
void medirTempo(void (*algoritmo)(Componente[], int, int*), Componente lista[], int n, int *comparacoes) {
    clock_t inicio = clock();
    algoritmo(lista, n, comparacoes);
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio))/CLOCKS_PER_SEC;
    printf("Tempo de execução: %.6f segundos\n", tempo);
}
