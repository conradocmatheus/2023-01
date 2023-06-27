#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct exibir
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
};

struct stock_exibir
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
    struct stock_exibir *proximo;
    struct stock_exibir *anterior;
};

typedef struct
{
    struct stock_exibir *inicio;
} Lista_exibir;

void inserir_ex(Lista_exibir *lista, struct stock_exibir no)
{
    struct stock_exibir *novo = (struct stock_exibir *)malloc(sizeof(struct stock_exibir));
    *novo = no;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
    }
    else
    {
        struct stock_exibir *atual = lista->inicio;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        novo->proximo = NULL;

        atual->proximo = novo;
        novo->anterior = atual;
    }
}

void exibir()
{
    Lista_exibir lista;
    lista.inicio = NULL;

    struct stock_exibir no;

    int ini;

    FILE *pini;
    pini = fopen("ini.txt", "r"); // abre pini
    fscanf(pini, "%d", &ini);
    fclose(pini); // fecha pini

    if (ini == 0)
    {
        nenhum_produto();
    }
    else
    {
        // ALOCACAO DA STRUCT EXIBIR ZERANDO SEUS ELEMENTOS
        struct exibir *stock = (struct exibir *)calloc(ini, sizeof(struct exibir));
        if (stock == NULL)
        {
            printf("\nERRO NA ALOCACAO DA STRUCT EXIBIR!!!\n");
            exit(1);
        }
        // FIM DA ALOCACAO DA STRUCT EXIBIR

        // LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT
        FILE *pARQLERTXT;
        pARQLERTXT = fopen("stock.txt", "r"); // abre pARQLERTXT
        for (int i = 0; i < ini; i++)
        {
            fscanf(pARQLERTXT, "%d", &stock[i].item_cod);
            fgetc(pARQLERTXT);

            fgets(stock[i].item_nome, sizeof(stock[i].item_nome), pARQLERTXT);
            int pos = strcspn(stock[i].item_nome, "\n");
            stock[i].item_nome[pos] = '\0';

            fscanf(pARQLERTXT, "%f", &stock[i].item_valorUN);
            fscanf(pARQLERTXT, "%d", &stock[i].item_stock);
        }
        fclose(pARQLERTXT); // fecha pARQLERTXT
        // FIM DA LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT

        for (int i = 0; i < ini; i++)
        {
            no.item_cod = stock[i].item_cod;
            strcpy(no.item_nome, stock[i].item_nome);
            no.item_valorUN = stock[i].item_valorUN;
            no.item_stock = stock[i].item_stock;

            inserir_ex(&lista, no);
        }

        // EXIBICAO DE ESTOQUE
        system("cls");
        printf("=====================================================================\n");
        printf("                    Exibicao de Produtos e Estoque                    \n");
        printf("=====================================================================\n");
        printf("         |Item(codigo) |Nome do Item             |Valor(UN) |Estoque |\n");

        struct stock_exibir *atual = lista.inicio;
        int i = 0;
        while (atual != NULL)
        {
            printf("Item %d   |%-13d|%-25s|%-10.2f|%-8d\n", i + 1, atual->item_cod, atual->item_nome, atual->item_valorUN, atual->item_stock);
            atual = atual->proximo;
            i++;
        }

        // LIBERAR MEMÓRIA
        struct stock_exibir *temp = lista.inicio;
        while (temp != NULL)
        {
            struct stock_exibir *proximo = temp->proximo;
            free(temp);
            temp = proximo;
        }

        free(stock);
        // FIM DA LIBERAÇÃO DE MEMÓRIA
    }
}