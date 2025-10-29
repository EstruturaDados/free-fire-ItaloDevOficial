#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ----------------------
// Struct
// ----------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ----------------------
// Protótipos
// ----------------------
void adicionarItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
int buscarItem(Item mochila[], int qtd, char *nome, int *comparacoes);
void printCabecalho();

// ----------------------
// Função principal
// ----------------------
int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;
    char nomeBusca[30];
    int comparacoes;

    do {
        printCabecalho();
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {
            case 1:
                adicionarItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                printf("Digite o nome do item: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                comparacoes = 0;
                if (buscarItem(mochila, qtd, nomeBusca, &comparacoes) == -1)
                    printf("\n[!] Item não encontrado. Comparações realizadas: %d\n", comparacoes);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\n[!] Opção inválida! Tente novamente.\n");
        }
        printf("\n");
    } while(opcao != 0);

    return 0;
}

// ----------------------
// Funções
// ----------------------
void printCabecalho() {
    printf("\n====================================\n");
    printf("       SISTEMA DE INVENTÁRIO        \n");
    printf("====================================\n");
}

void adicionarItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\n[!] Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nNome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpar buffer

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\n[✔] Item adicionado com sucesso!\n");
}

void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\n[!] Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nNome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = 0;
    for(int i = 0; i < *qtd; i++) {
        if(strcmp(mochila[i].nome, nome) == 0) {
            for(int j = i; j < *qtd - 1; j++)
                mochila[j] = mochila[j + 1];
            (*qtd)--;
            encontrado = 1;
            printf("\n[✔] Item '%s' removido com sucesso!\n", nome);
            break;
        }
    }

    if(!encontrado)
        printf("\n[!] Item não encontrado!\n");
}

void listarItens(Item mochila[], int qtd) {
    if(qtd == 0) {
        printf("\n[!] Mochila vazia!\n");
        return;
    }

    printf("\n================ ITENS NA MOCHILA ================\n");
    printf("| %-3s | %-20s | %-15s | %-10s |\n", "Nº", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------------------------\n");
    for(int i = 0; i < qtd; i++)
        printf("| %-3d | %-20s | %-15s | %-10d |\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    printf("---------------------------------------------------------------\n");
}

int buscarItem(Item mochila[], int qtd, char *nome, int *comparacoes) {
    for(int i = 0; i < qtd; i++) {
        (*comparacoes)++;
        if(strcmp(mochila[i].nome, nome) == 0) {
            printf("\n[✔] Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Comparações realizadas: %d\n", *comparacoes);
            return i;
        }
    }
    return -1;
}
