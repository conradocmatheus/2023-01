#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct vendas
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int item_stock;
};

struct stock_venda
{
    int item_cod;
    char item_nome[25];
    float item_valorUN;
    int qnt_vendida;
    float total;
    struct stock_venda *proximo;
    struct stock_venda *anterior;
};

typedef struct
{
    struct stock_venda *inicio;
} Lista_venda;

void inserir_venda(Lista_venda *lista, struct stock_venda no)
{
    struct stock_venda *novo = (struct stock_venda *)malloc(sizeof(struct stock_venda));
    *novo = no;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
    }
    else
    {
        struct stock_venda *atual = lista->inicio;

        // Encontra a posição para inserir o novo nó com base no total em ordem decrescente
        while (atual->proximo != NULL && novo->total > atual->proximo->total)
        {
            atual = atual->proximo;
        }

        // Insere o novo nó na posição correta
        novo->proximo = atual->proximo;
        if (atual->proximo != NULL)
        {
            atual->proximo->anterior = novo;
        }
        novo->anterior = atual;
        atual->proximo = novo;
    }
}

void realizar_vendas()
{

    int ini;

    FILE *pini;
    pini = fopen("ini.txt", "r");
    fscanf(pini, "%d", &ini);
    fclose(pini);

    if (ini == 0)
    {
        nenhum_produto();
    }
    else
    {
        // ALOCACAO DA STRUCT VENDAS ZERANDO SEUS ELEMENTOS
        struct vendas *stock = (struct vendas *)calloc(ini, sizeof(struct vendas));
        if (stock == NULL)
        {
            printf("\nERRO NA ALOCACAO DA STRUCT EXIBIR!!!\n");
            exit(1);
        }
        // FIM DA ALOCACAO DA STRUCT VENDAS

        // LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT
        FILE *pARQLERTXT;
        pARQLERTXT = fopen("stock.txt", "r");
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
        fclose(pARQLERTXT);
        // FIM DA LEITURA DE DOS ITEMS NO STOCK GUARDADOS NO ARQUIVO TXT

        int pag_cod = 0;
        int pag_parc = 0;

        float acrescimo[2] = {0, 0};
        float desconto[3] = {0, 0, 0};
        float valor_parc = 0;
        float valor_pago = 0;
        float troco = 0;

        int codVE = 0;
        int posicao = 0;
        int qnt_desejada = 0;
        int tentar_novamente = 0;
        int outra_venda = 0;
        float valor_total = 0;
        int itens_total = 0;

        int *quantia = (int *)calloc(ini, sizeof(int));
        float *valor = (float *)calloc(ini, sizeof(float));

        Lista_venda lista;
        lista.inicio = NULL;

        struct stock_venda no;

        do
        {

            do
            {
                tentar_novamente = 0;
                do
                {
                    system("cls");
                    exibir();
                    printf("======================================================================\n");
                    printf("                          Venda de Produtos                           \n");
                    printf("======================================================================\n");
                    printf("Digite o codigo do produto que sera vendido\n=>");
                    scanf("%d", &codVE);
                    for (int i = 0; i < ini; i++)
                    {
                        if (codVE == stock[i].item_cod)
                        {
                            system("cls");
                            printf("Produto com o Codigo %d encontrado!!\n", codVE);
                            posicao = i;

                            break;
                        }
                    }
                    if (codVE != stock[posicao].item_cod)
                    {
                        system("cls");
                        printf("Produto com o Codigo %d nao encontrado!!\n", codVE);
                        system("pause");
                    }

                } while (codVE != stock[posicao].item_cod);
                // FIM LEITURA E VERIFICACAO DO CODIGO DO PRODUTO

                if (stock[posicao].item_stock == 0)
                {
                    printf("Item sem estoque\n");
                    system("Pause");
                }

            } while (stock[posicao].item_stock == 0);

            tentar_novamente = 0;
            do
            {
                printf("Estoque: %d unidades\n", stock[posicao].item_stock);
                printf("Digite a Quantidade Desejada do Item:\n=>");
                scanf("%d", &qnt_desejada);
                if (qnt_desejada > stock[posicao].item_stock || qnt_desejada < 1)
                {
                    do
                    {
                        system("cls");
                        printf("Quantia Invalida ou Estoque Insuficiente!!\n");
                        printf("1. Tentar novamente\n");
                        printf("2. Voltar ao menu de vendas\n");
                        scanf("%d", &tentar_novamente);
                        system("cls");
                        if (tentar_novamente == 2)
                        {
                            vendas();
                        }
                        else if (tentar_novamente != 1 && tentar_novamente != 2)
                        {
                            opcao_invalida();
                        }
                        if (tentar_novamente == 1)
                        {
                            break;
                        }
                    } while (tentar_novamente != 2);
                }
            } while (qnt_desejada > stock[posicao].item_stock || qnt_desejada < 1);

            tentar_novamente = 0;

            printf("Voce adicionou %d unidades\n", qnt_desejada);
            system("pause");

            stock[posicao].item_stock = stock[posicao].item_stock - qnt_desejada;

            FILE *pARQESCTXT;
            pARQESCTXT = fopen("stock.txt", "w");
            if (pARQESCTXT == NULL)
            {
                printf("Erro ao abrir arquivo stock.txt");
                exit(1);
            }
            // ADICAO DOS ITENS NO TXT
            for (int i = 0; i < ini; i++)
            {
                fprintf(pARQESCTXT, "%d\n", stock[i].item_cod);
                fprintf(pARQESCTXT, "%s\n", stock[i].item_nome);
                fprintf(pARQESCTXT, "%.2f\n", stock[i].item_valorUN);
                fprintf(pARQESCTXT, "%d\n", stock[i].item_stock);
            }
            // FIM DA ADICAO DOS ITENS NO TXT
            fclose(pARQESCTXT);

            quantia[posicao] += qnt_desejada;

            FILE *quantia_vendida;
            quantia_vendida = fopen("vendida.txt", "w");

            for (int a = 0; a < ini; a++)
            {
                fprintf(quantia_vendida, "%d\n", quantia[a]);
            }

            fclose(quantia_vendida);

            valor[posicao] += (stock[posicao].item_valorUN * qnt_desejada);

            no.item_cod = stock[posicao].item_cod;
            strcpy(no.item_nome, stock[posicao].item_nome);
            no.item_valorUN = stock[posicao].item_valorUN;
            no.qnt_vendida = quantia[posicao];
            no.total = no.qnt_vendida * no.item_valorUN;

            inserir_venda(&lista, no);

            do
            {
                system("cls");
                printf("Deseja realizar outra venda?\n");
                printf("1. Sim\n");
                printf("2. Nao\n");
                scanf("%d", &outra_venda);

                if (outra_venda < 1 || outra_venda > 2)
                {
                    opcao_invalida();
                }
            } while (outra_venda != 1 && outra_venda != 2);

        } while (outra_venda == 1);

        // SOMA DO VALOR TOTAL PARA O CUPOM
        for (int i = 0; i < ini; i++)
        {
            valor_total += valor[i];
        }
        // SOMA DO VALOR TOTAL PARA O CUPOM

        // SOMA DOS DA QUANTIA TOTAL PARA O CUPOM
        for (int i = 0; i < ini; i++)
        {
            itens_total += quantia[i];
        }
        // SOMA DOS DA QUANTIA TOTAL PARA O CUPOM

        // CUPOM FISCAL
        system("cls");
        printf("=======================CUPOM FISCAL======================\n");
        printf("ITEM -   NOME DO ITEM  - VALOR(un) - QUANTIA -     VALOR\n");

        int i = 0;
        struct stock_venda *atual = lista.inicio;
        while (atual != NULL)
        {
            printf("%-2d   - %15s -   %.2f    -   %2d    - $%8.2f \n", i + 1, atual->item_nome, atual->item_valorUN, atual->qnt_vendida, atual->total);
            i++;
            atual = atual->proximo;
        }

        printf("Valor total.....................................: R$%.2f \n", valor_total);
        printf("Quantia total...................................: %d itens\n", itens_total);
        system("pause");
        // CUPOM FISCAL

        //========================================INICIO DO PAGAMENTO================================================

        do
        {
            system("cls");

            printf("Formas de pagamento:\n");
            printf("1 = Desconto a Vista.\n");
            printf("2 = A prazo.\n");

            printf("Selecione a Forma de Pagamento:\n=>");
            scanf("%d", &pag_cod);
            system("cls");

            acrescimo[0] = valor_total * 0.05;
            acrescimo[1] = valor_total * 0.08;

            desconto[0] = valor_total * 0.05;
            desconto[1] = valor_total * 0.10;
            desconto[2] = valor_total * 0.18;

            switch (pag_cod)
            {
            case 1:
                if (valor_total <= 50)
                {
                    printf("Total - Desconto: R$ %.2f - R$ %.2f\n", valor_total, desconto[0]);
                    valor_total = valor_total - desconto[0];
                    printf("Total com Desconto: R$ %.2f\n", valor_total);
                }
                else if (valor_total > 50 && valor_total < 100)
                {
                    printf("Total - Desconto: R$ %.2f - R$ %.2f\n", valor_total, desconto[1]);
                    valor_total = valor_total - desconto[1];
                    printf("\nTotal com Desconto: R$ %.2f \n", valor_total);
                }
                else
                {
                    printf("Total - Desconto: R$ %.2f - R$ %.2f\n", valor_total, desconto[2]);
                    valor_total = valor_total - desconto[2];
                    printf("Total com Desconto: R$ %.2f \n", valor_total);
                }

                system("pause");

                int troco_sim_nao = 0;

                system("cls");
                printf("Troco necessario para o pagamento?\n");
                printf("1. Sim\n");
                printf("2. Nao\n");
                scanf("%d", &troco_sim_nao);

                if (troco_sim_nao == 1)
                {
                    do
                    {
                        printf("Valor Final: R$%.2f\n", valor_total);
                        printf("Insira o Valor Pago: R$ ");
                        scanf("%f", &valor_pago);
                        troco = valor_pago - valor_total;

                        if (valor_pago < valor_total)
                        {
                            troco = troco * -1;
                            printf("\nValor insulficiente para realizar a compra!\nFaltam %.2f \n\n", troco);
                            printf(" Digite o Valor novamente...\n\n");
                        }
                        else
                        {
                            printf("\n Seu troco e: R$ %.2f", troco);
                            printf("\n\nOBRIGADO, VOLTE SEMPRE! \n\n");
                            system("pause");
                            vendas();
                        }
                        break;

                    } while (valor_pago < valor_total);
                }

                do
                {
                    system("cls");
                    printf("Valor total: %.2f", valor_total);
                    printf("\n\nInsira o Valor Pago: R$ ");
                    scanf("%f", &valor_pago);

                    if (fabs(valor_total - valor_pago) < 0.01)
                    {
                        printf("Compra Finalizada!!!\n");
                        system("pause");
                        vendas();
                    }

                    printf("Valor invalido ou insuficiente\n");
                    system("pause");

                } while (valor_pago != valor_total);

            case 2:
                do
                {
                    printf("Numero de parcelas (MAX 12!):");
                    scanf("%d", &pag_parc);

                    if (pag_parc <= 3 && pag_parc > 1)
                    {
                        valor_parc = valor_total / pag_parc;

                        printf("\nSua compra sera dividida em %d parcelas\n", pag_parc);
                        printf("\nTotal + Acrescimo: R$ %.2f + R$ %.2f", valor_total, acrescimo[0]);

                        valor_total = valor_total + acrescimo[0];

                        printf("\nTotal com Acrescimo: R$ %.2f ", valor_total);
                        printf("\nValor de cada Parcela: R$ %.2f \n", valor_parc);
                        system("pause");
                    }
                    else if (pag_parc > 3 && pag_parc <= 12)
                    {
                        valor_parc = valor_total / pag_parc;

                        printf("\n\nSua compra sera dividida em %d parcelas\n", pag_parc);
                        printf("\nTotal + Acrescimo: R$ %.2f + R$ %.2f", valor_total, acrescimo[1]);

                        valor_total = valor_total + acrescimo[1];

                        printf("\nTotal com Acrescimo: R$ %.2f ", valor_total);
                        printf("\nValor de cada Parcela: R$ %.2f \n", valor_parc);
                        system("pause");
                    }
                    else if (pag_parc > 12)
                    {
                        system("cls");
                        printf("O Numero maximo de parcelas e 12\n");
                        system("pause");
                    }
                    else if (pag_parc < 1)
                    {
                        system("cls");
                        printf("O Numero minimo de parcelas e 1\n");
                        system("pause");
                    }

                } while (pag_parc > 12 || pag_parc <= 1);
                break;

            default:
                opcao_invalida();
                break;
            }
            break;

        } while (pag_cod < 1 || pag_cod > 2);

        //=======================================FINAL DO PAGAMENTO===========================================

        // DESAFIO TIME.H
        time_t t = time(NULL);
        struct tm *currentTime = localtime(&t);

        char nomeArquivo[100];
        sprintf(nomeArquivo, "%d-%02d-%02d_%02d-%02d-%02d.txt",
                currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday,
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);

        FILE *arquivo = fopen(nomeArquivo, "w");
        if (arquivo == NULL)
        {
            printf("Erro ao criar o arquivo.\n");
            exit(1);
        }

        fprintf(arquivo, "|       Nome do Item       | Quantia Vendida |\n");
        // ESCRITA
        for (int i = 0; i < ini; i++)
        {
            fprintf(arquivo, " %-26s|%-16d\n", stock[i].item_nome, quantia[i]);
        }

        fclose(arquivo);

        printf("Arquivo criado com sucesso: %s\n", nomeArquivo);
        // DESAFIO TIME.H

        free(stock);
    }
}
// FIM DA FUNCAO DE REALIZAR VENDAS