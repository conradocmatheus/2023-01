#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct cadastro
{
    int item_cod_cad;
    char item_nome_cad[25];
    float item_valorUN_cad;
    int item_stock_cad;
};

struct stock
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
    struct stock *proximo;
    struct stock *anterior;
};

typedef struct
{
    struct stock *inicio;
} Lista;

void liberarMemoria(Lista *lista)
{
    struct stock *atual = lista->inicio;
    struct stock *temp;

    while (atual != NULL)
    {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    lista->inicio = NULL;
}

void inserir(Lista *lista, struct stock no)
{
    struct stock *novo = (struct stock *)malloc(sizeof(struct stock));
    *novo = no;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (lista->inicio == NULL)// SE ESTIVER VAZIA
    {
        lista->inicio = novo;
    }
    else // SE NAO ESTIVER VAZIA
    {
        struct stock *atual = lista->inicio;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        novo->proximo = NULL;

        atual->proximo = novo;
        novo->anterior = atual;
    }
}

bool verificarCodigoRepetido(Lista *lista, int codigo)
{
    struct stock *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->item_cod == codigo)
        {
            return true; // Codigo repetido encontrado
        }
        atual = atual->proximo;
    }

    return false;
}

void carregarLista(Lista *lista)
{
    FILE *arquivo = fopen("stock.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo estoque-stock.txt");
        exit(1);
    }

    struct stock novo;
    while (fscanf(arquivo, "%d", &novo.item_cod) == 1)
    {
        fscanf(arquivo, " %[^\n]", novo.item_nome);
        fscanf(arquivo, "%f", &novo.item_valorUN);
        fscanf(arquivo, "%d", &novo.item_stock);

        inserir(lista, novo);
    }

    fclose(arquivo);
}

void cadastrar()
{
    int qnt_prod_desejados = 0;
    int ini;

    FILE *pini;
    pini = fopen("ini.txt", "r"); // abre pini
    fscanf(pini, "%d", &ini);
    fclose(pini); // fecha pini

    Lista lista;
    lista.inicio = NULL;

    if (ini > 0)
    {
        carregarLista(&lista);
    }

    struct stock no;

    do
    {
        system("cls");
        printf("================================================\n");
        printf("                Cadastro de Produtos             \n");
        printf("================================================\n");

        printf("Numero de produtos a cadastrar\n=>");
        scanf("%d", &qnt_prod_desejados);

        if (qnt_prod_desejados < 1)
        {
            printf("\nQuantia invalida!!\n");
            printf("O valor deve ser igual ou maior que 1\n");
            system("pause");
            system("cls");
        }
    } while (qnt_prod_desejados < 1);

    struct cadastro *cad = (struct cadastro *)calloc(qnt_prod_desejados, sizeof(struct cadastro));
    if (cad == NULL)
    {
        printf("Erro na Alocacao de cad\n");
        exit(1);
    }

    FILE *pARQLERTXT;
    pARQLERTXT = fopen("stock.txt", "r");

    for (int i = 0; i < qnt_prod_desejados; i++)
    {
        bool codigoRepetido = false;
        do
        {
            system("cls");
            printf("Digite o Codigo do Item\n=>");
            scanf("%d", &cad[i].item_cod_cad);
            getchar();
            if (cad[i].item_cod_cad < 1)
            {
                system("cls");
                printf("O valor deve ser maior ou igual a 1,\nnao pode ser composto por caracteres\ne tambem deve ser unico!!\n");
                system("pause");
            }

            codigoRepetido = verificarCodigoRepetido(&lista, cad[i].item_cod_cad);
            if (codigoRepetido)
            {
                system("cls");
                printf("O codigo digitado ja existe \nDigite um codigo diferente \n");
                system("pause");
                codigoRepetido = true;
            }
            else
            {
                break;
            }
        } while (codigoRepetido == true);

        char espaco = ' ';
        do
        {
            system("cls");
            printf("Digite o Nome do Item\n=>"); // String com ate 25 caracteres, nao pode ser vazio, nem so espacos
            fgets(cad[i].item_nome_cad, 25, stdin);
            if (strlen(cad[i].item_nome_cad) > 25 || cad[i].item_nome_cad[0] == '\n' || cad[i].item_nome_cad[0] == espaco)
            {
                system("cls");
                printf("Maximo 25 caracteres!! \n");
                printf("Nome nao pode ser composto somente por espacos!! \n");
                printf("Nao pode ser vazio!! \n");
                system("pause");
            }
        } while (strlen(cad[i].item_nome_cad) > 25 || cad[i].item_nome_cad[0] == '\n' || cad[i].item_nome_cad[0] == espaco);

        do
        {
            system("cls");
            printf("Digite o Valor Unitario\n=>"); // valor decimal igual ou maior que 0
            scanf("%f", &cad[i].item_valorUN_cad);
            getchar();
            if (cad[i].item_valorUN_cad < 0)
            {
                system("cls");
                printf("Valor deve ser maior que 0 !! \n");
                system("pause");
            }
        } while (cad[i].item_valorUN_cad < 0);

        do
        {
            system("cls");
            printf("Digite a Quantidade do Item\n=>"); // valor inteiro igual ou maior que 0
            scanf("%d", &cad[i].item_stock_cad);
            getchar();
            if (cad[i].item_stock_cad < 0)
            {
                system("cls");
                printf("Valor deve ser igual ou maior que 0 \n");
                system("pause");
            }
        } while (cad[i].item_stock_cad < 0);

        printf("Produto Cadastrado!!\n");
        system("pause");
        system("cls");

        // Abertura de arquivo para adicao dos itens a cada iteracao do for
        FILE *arq;
        arq = fopen("stock.txt", "a");
        if (arq == NULL)
        {
            printf("Erro ao abrir arquivo stock.txt");
            exit(4);
        }

        // Adicao dos itens no txt
        fprintf(arq, "%d\n", cad[i].item_cod_cad);
        fprintf(arq, "%s", cad[i].item_nome_cad);
        fprintf(arq, "%.2f\n", cad[i].item_valorUN_cad);
        fprintf(arq, "%d\n", cad[i].item_stock_cad);
        // Adicao dos itens no txt

        fclose(arq);
        // Fechamento de arquivo para adicao dos itens a cada iteracao do for

        no.item_cod = cad[i].item_cod_cad;
        strcpy(no.item_nome, cad[i].item_nome_cad);
        no.item_valorUN = cad[i].item_valorUN_cad;
        no.item_stock = cad[i].item_stock_cad;

        ini++;
        inserir(&lista, no);
    }

    system("pause");

    pini = fopen("ini.txt", "w");
    fprintf(pini, "%d", ini);
    fclose(pini);

    free(cad);
    fclose(pARQLERTXT);
    liberarMemoria(&lista);
}