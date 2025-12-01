#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// ==========================
// Struct do Item
// ==========================
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// ==========================
// Enum para ordenação
// ==========================
enum CriterioOrdenacao {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
};

// ==========================
// Variáveis globais da mochila
// ==========================
Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;

// ==========================
// Limpar tela (simples)
// ==========================
void limparTela() {
    for (int i = 0; i < 40; i++) printf("\n");
}

// ==========================
// Menu principal
// ==========================
void exibirMenu() {
    printf("===== CODIGO DA ILHA – NIVEL MESTRE =====\n");
    printf("1 - Adicionar item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Ordenar itens\n");
    printf("5 - Busca binária por nome\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

// ==========================
// Inserir item
// ==========================
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Nome do item: ");
    scanf("%49s", mochila[numItens].nome);

    printf("Tipo do item: ");
    scanf("%29s", mochila[numItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &mochila[numItens].prioridade);

    numItens++;
    ordenadaPorNome = false;

    printf("Item adicionado com sucesso!\n");
}

// ==========================
// Remover item
// ==========================
void removerItem() {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeBusca[50];
    printf("Nome do item para remover: ");
    scanf("%49s", nomeBusca);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < numItens - 1; j++)
                mochila[j] = mochila[j + 1];
            numItens--;
            printf("Item removido!\n");
            return;
        }
    }

    printf("Item não encontrado!\n");
}

// ==========================
// Listar itens
// ==========================
void listarItens() {
    if (numItens == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("===== ITENS NA MOCHILA =====\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d) Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
}

// ==========================
// Comparação para ordenação
// ==========================
int comparar(Item a, Item b, int criterio) {
    if (criterio == ORDENAR_NOME)
        return strcmp(a.nome, b.nome);
    if (criterio == ORDENAR_TIPO)
        return strcmp(a.tipo, b.tipo);
    return a.prioridade - b.prioridade;
}

// ==========================
// Insertion Sort
// ==========================
int insertionSort(int criterio) {
    int comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0 && comparar(mochila[j], chave, criterio) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }
        mochila[j + 1] = chave;
    }

    if (criterio == ORDENAR_NOME)
        ordenadaPorNome = true;
    else
        ordenadaPorNome = false;

    return comparacoes;
}

// ==========================
// Menu de ordenação
// ==========================
void menuDeOrdenacao() {
    int opc;
    printf("Ordenar por:\n1 - Nome\n2 - Tipo\n3 - Prioridade\nEscolha: ");
    scanf("%d", &opc);

    int comp = insertionSort(opc);
    printf("Itens ordenados! Comparações: %d\n", comp);
}

// ==========================
// Busca Binária
// ==========================
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("A mochila precisa estar ordenada por NOME!\n");
        return;
    }

    char nomeBusca[50];
    printf("Nome a buscar: ");
    scanf("%49s", nomeBusca);

    int ini = 0, fim = numItens - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {
            printf("Encontrado: %s | %s | Qtd: %d | Prioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo,
                   mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        }
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Item não encontrado!\n");
}

// ==========================
// Programa principal
// ==========================
int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}