/*
LINGUAGEM DE PROGRAMAÇAO C
TRABALHO DE LISTA E ORDENAÇAO - TEMA 2
INSTITUIÇAO: ESTÁCIO
ALUNO: MATHEUS AVELINO
NÍVEL NOVATO
DATA: 01 12 2025
=======================================================
*/

// Pré-processadores
#include <stdio.h>
#include <string.h> // Bibiotecas necessarias para manipulação de strings as funções (strcopy) e (strcmp)
#include <stdlib.h>

/*
strcopy(destino, origem) - Copia a string da origem para o destino.
strcmp(str1, str2) - Compara duas strings. Retorna 0 se forem iguais.

*/

// Constantes globais
#define MAX_STRING 50 // tamanho máximo da string;
#define MAX_ITENS 10  // tamanho máximo do array;

/*
PARTE 1: LISTA ESTATICAS
- Lista estatica e tamanho de dados fixo;
- Usando array para criar a lista;
- Toda a memória ela é alocada aepnas uma vez quando é declarada
*/

// Definição de estruturas
typedef struct
{
    // Campos da struct
    char itens[MAX_ITENS][MAX_STRING]; // Array de strings para armazenar os itens, Matriz [10] linhas (itens) e [50] colunas (caracteres por itens);
    char nome[MAX_STRING];             // Nome do obejto da lista
    char tipo[MAX_STRING];             // Nome do tipo de objeto da lista
    int quantidade;                    // Esse é o nosso contador de controle. Ele conta quantos itens armazenados realmente estão na lista.
} item;

// Funções da lista estática
//- Define o contador quantidade como zero, indicando que a lista está vazia.
//- Reecebemos oponteiro *lista para modificar a variavel original passada por parâmetro.
void inicializarLista(item *lista);

void inserirListaStatica(item *lista, const char *texto); // Const char* texto para evitar modificação da string original;
void removerDeItens(item *lista, const char *texto);      // Const char* texto para evitar modificação da string original;
void listarItens(const item *lista);                      // Const item* lista para evitar modificação da lista original;

/*
PARTE 2: LISTA ENCADEADA (STRINGS)
- Lista encadeada é uma estrutura de dados dinâmica;
- Ela é composta por "nós" separados na memória;
- Cada nó contém um valor (string) e um ponteiro para o próximo nó na lista na sequência;
*/
typedef struct NoLista
{
    char *dado;              // Armazena o enereçoValor do nó (string)
    struct NoLista *proximo; // Ponteiro para o próximo nó na lista
} NoLista;

// Função Lista encadeada
typedef NoLista *ListaEncadeada; // Definir o tipo ListaEncadeada como um ponteiro para NoLista

// Funções para lista encadeada
void inicializarListaEncadeada(ListaEncadeada *lista);

void inserirNaListaEncadeada(ListaEncadeada *lista, const char *texto);
void removerDaListaEncadeada(ListaEncadeada *lista, const char *texto);
void listarItensEncadeados(const ListaEncadeada *lista);
void liberarListaEncadeada(ListaEncadeada *lista); // Função para liberar a memória alocada para a lista encadeada;

// Funções main e menus;
void buscarItemNaMochilaSequencial(const item *lista, const char *texto);

// função para Limpar o buffer de entrada
void LimparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // Limpa até o final da linha ou EOF
};

// main - Função principal
int main()
{

    item mochila = {.quantidade = 0}; // Declarar a variável mochila do tipo struct item
    int mochila2 = 10;                // Variável auxiliar para demonstração
    int opcao;

    do
    {

        printf("==============================================\n");
        printf("   MOCHILA DE SOBREVIVENCIA - CÓDIGO DA ILHA  \n");
        printf("==============================================\n");
        printf("Itens da mochila: %d\n", mochila.quantidade, mochila2);
        printf("\n");
        printf("Escolha uma opção:\n");
        printf("1. Adicionar item (Loot)\n");
        printf("2. Remover item da mochila\n");
        printf("3. Listar itens da mochila\n");
        printf("0. Sair\n");
        printf("\n");
        printf("-----------------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        LimparBufferEntrada(); // Limpar o buffer de entrada após ler o inteiro

        switch (opcao)
        {
        case 1:
        {
            if (mochila.quantidade >= MAX_ITENS)
            {
                printf("Mochila cheia! Não é posssível adicionar mais itens.\n");
            }
            else
            {
                char novoItem[MAX_ITENS];
                char tipoItem[MAX_STRING];

                printf("Digite o nome do item para adicionar: ");
                fgets(novoItem, sizeof(novoItem), stdin);

                printf("Digite o tipo do item a ser adicionado: ");
                fgets(tipoItem, sizeof(tipoItem), stdin);

                novoItem[strcspn(novoItem, "\n")] = 0; // Remover a nova linha do final da string
                tipoItem[strcspn(tipoItem, "\n")] = 0; // Remover a nova linha do final da string

                // inserir na lista/atualizar contador
                inserirListaStatica(&mochila, novoItem);
                inserirListaStatica(&mochila, tipoItem);
            }
        }

        break;
        case 2:
        {
            char itemRemover[MAX_STRING];
            printf("Digite o nome do item para remover: ");
            fgets(itemRemover, sizeof(itemRemover), stdin);

            itemRemover[strcspn(itemRemover, "\n")] = 0; // Remover a nova linha do final da string

            // remover da lista/atualizar contador
            removerDeItens(&mochila, itemRemover);
        }
        break;
        case 3:
            listarItens(&mochila);
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            break;
        }

    } while (opcao != 0);

    system("pause");
    return 0;
}

/// IMPREMENTAÇÕES DAS FUNÇÕES
//-----------------------------------------

void inicializarLista(item *lista)
{
    lista->quantidade = 0; // Inicializar o contador de itens como zero
}


//Buscar item na mochila - busca sequencial
void buscarItemNaMochilaSequencial(const item *lista, const char *texto)
{
    int i;
    for (i = 0; i < lista->quantidade; i++)
    {
        if (strcmp(lista->itens[i], texto) == 0)
        {
            printf("Item \"%s\" encontrado na mochila na posição %d.\n", texto, i);
            return;
        }
    }
    printf("Item \"%s\" não encontrado na mochila.\n", texto);
}



void inserirListaStatica(item *lista, const char *texto)
{
    if (lista->quantidade == MAX_ITENS)
    {

        printf("Erro: Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    else
    {

        // Copiar o texto para o array de itens na posição do contador
        strcpy(lista->itens[lista->quantidade], texto);
        lista->quantidade++; // Incrementar o contador de itens

        printf("Item \"%s\" adicionado à mochila.\n", texto);
    }
}

void removerDeItens(item *lista, const char *texto)
{
    int i, posição = -1; // Variável para armazenar a posição do item a ser removido

    // Para comparar strings, usamos strcmp da biblioteca string.h, Retorna 0 se forem iguais.
    // A função percorre o array de itens para encontrar o item em uso (de 0 até quantidade);
    // Para comparar strings, usamos strcmp(string1, string2).
    for (i = 0; i < lista->quantidade; i++)
    {
        if (strcmp(lista->itens[i], texto) == 0)
        {
            posição = i; // Encontrou o item, armazenar a posição
            break;
        }

        // Tratamento de erro
        if (posição == -1)
        {
            printf("Item \"%s\" não encontrado na mochila.\n", texto);
            return;
        }

        // Se removermos um item no meio da lista, criamos um "buraco"
        // Precisamos deslocar os itens seguintes para preencher esse buraco, movemos
        // todos os itens após a posição encontrada uma posição para a esquerda
        // Loop for comerça na posição do item a ser removido e copia cada item i+1 para a posição i;
        for (i = posição; i < lista->quantidade - 1; i++)
        {

            // Copiar o item seguinte para a posição atual
            strcpy(lista->itens[i], lista->itens[i + 1]);
        }

        // Atualizar o contador de itens, decrementado em 1 para refletir que a lista tem um item a menos.
        lista->quantidade--;
        printf("Item \"%s\" removido da mochila.\n", texto);
    }

    void listarItens(const item *lista)
    {
        int i;
        if (lista->quantidade == 0)
        {
            printf("Mochila vazia.\n");
            return;
        }

        printf("Itens na mochila: [\n");
        for (i = 0; i < lista->quantidade; i++)
        {
            printf("%d. %s\n", i + 1, lista->itens[i]); // Usamos %s para imprimir strings
        }
        printf("]\n");
    }

    // Funções de lista encadeada
    void inicializarListaEncadeada(ListaEncadeada * lista)
    {
        *lista = NULL; // Inicializar a lista como vazia (NULL)
    }

    void inserirNaListaEncadeada(ListaEncadeada * lista, const char *texto)
    {
        // Criar um novo nó
        NoLista* novoNo = (NoLista* )malloc(sizeof(NoLista));

        // verificar se a alocação foi bem sucedida
        if (novoNo == NULL)
        {
            printf("Erro de alocação de memória!\n");
            return;
        }

        // Alocar memória para a string e copiar o texto
        novoNo->dado = (char* )malloc(strlen(texto) + 1);

        // verificar se a alocação foi bem sucedida
        if (novoNo->dado == NULL)
        {
            printf("Erro de alocação de memória para string!\n");
            free(novoNo); // Liberar o nó já alocado
            return;
        }

        // Copia o texto para a memória recem alocada
        strcpy(novoNo->dado, texto);

        // Inserir o novo nó no início da lista
        novoNo->proximo = *lista;
        *lista = novoNo;

        printf("Item \"%s\" adicionado à lista co sucesso.\n", texto);
    }

    void removerDaListaEncadeada(ListaEncadeada * lista, const char *texto)
    {
        //usamos dois ponteiros atual e anterior para percorrer a lista
        NoLista* atual = *lista;
        NoLista* anterior = NULL;

        // Percorrer a lista para encontrar o nó a ser removido
        while (atual != NULL && strcmp(atual->dado, texto) != 0)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        // Se o nó não foi encontrado
        if (atual == NULL)
        {
            printf("Item \"%s\" não encontrado na lista.\n", texto);
            return;
        }

        // Remover o nó da lista
        if (anterior == NULL)
        {
            // O nó a ser removido é o primeiro nó
            *lista = atual->proximo;
        }
        else
        {
            anterior->proximo = atual->proximo;
        }

        // Liberar a memória do nó removido
        free(atual->dado);
        free(atual);

        printf("Item \"%s\" removido da lista com sucesso.\n", texto);
    }
