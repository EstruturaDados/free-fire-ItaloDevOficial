#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10 // Capacidade máxima da mochila

// ----------------------
// Definição da Struct
// ----------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ----------------------
// Funções do sistema
// ----------------------
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);

// ----------------------
// Função principal
// ----------------------
int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;

    printf("=== SISTEMA DE INVENTÁRIO ===\n");
    listarItens(mochila, qtd); // Mostra estado inicial da mochila

    do {
        printf("\n1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer do Enter

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ----------------------
// Inserir novo item
// ----------------------
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove '\n'

    printf("Digite o tipo do item (arma, munição, cura, etc): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpar buffer

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\n✅ Item adicionado com sucesso!\n");
    listarItens(mochila, *qtd); // Mostra mochila atualizada
}

// ----------------------
// Remover item
// ----------------------
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nA mochila está vazia! Nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1]; // move os próximos itens
            }
            (*qtd)--;
            encontrado = 1;
            printf("\n❌ Item '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado)
        printf("\nItem não encontrado!\n");

    listarItens(mochila, *qtd); // Mostra mochila atualizada
}

// ----------------------
// Listar todos os itens
// ----------------------
void listarItens(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\n📦 A mochila está vazia.\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// ----------------------
// Buscar item pelo nome
// ----------------------
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila está vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔎 Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\nItem não encontrado!\n");
}
