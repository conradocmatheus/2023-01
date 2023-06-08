#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// INICIO DAS STRUCTS
struct itens
{
    int cod;
    char nome[20];
    float valor;
    float valor_total_item;
    int qnt;
} stock[5] = {0, 0, 0, 0, 0};
// STRUCT ITENS

// STRUCT PARA RELATORIO DE VENDAS
struct itens_vendidos
{
    char nome[20];
    int qnt;
} relatorio[5] = {0, 0, 0, 0, 0};
// FIM DAS STRUCTS

// INICIO DECLARACAO DAS FUNCOES
void codigo_invalido();
void quantidade_invalida();
struct itens menu_principal();
struct itens cadastrar_estoque();
struct itens visualizar_estoque();
struct itens realizar_vendas();
struct itens_vendidos realatorio_vendas();
// FIM DA DECLARACAO DAS FUNCOES

// INICIO DA FUNCAO DO MENU PRINCIPAL
struct itens menu_principal()
{
    int cod_funcao = 0;

    do
    {
        system("cls");

        printf("\033[0;32m  1. Cadastrar Estoque.\n");
        printf("  2. Visualizar Estoque.\n");
        printf("  3. Realizar Vendas.\n");
        printf("  4. Sair.\n\n");

        printf("  Selecione uma opcao: ");
        scanf("%d", &cod_funcao);

        switch (cod_funcao)
        {
        case 1:
            cadastrar_estoque();
            break;

        case 2:
            visualizar_estoque();
            system("pause");
            break;

        case 3:
            realizar_vendas();
            break;

        case 4:
            realatorio_vendas();
            break;

        default:
            codigo_invalido();
        }

    } while (cod_funcao != 4);
}
// FIM DA FUNCAO DO MENU PRINCIPAL

// INICIO DA FUNCAO DE CODIGO INVALIDO
void codigo_invalido()
{
    system("cls");
    printf("\n\nCodigo Invalido!!\n\n");
    system("pause");
    system("cls");
}
// FIM DA FUNCAO DE CODIGO INVALIDO

// INICIO DA FUNCAO DE QUANTIDADE INVALIDA
void quantidade_invalida()
{
    system("cls");
    printf("\n\nQuantidade Invalida!!\n\n");
    system("pause");
    system("cls");
}
// FIM DA FUNCAO DE QUANTIDADE INVALIDA

// INICIO DA FUNCAO DE CADASTRO DE ESTOQUE
struct itens cadastrar_estoque()
{
    int stock_add = 0;
    int stock_cod = 0;

    do
    {
        while (stock_cod > 5 || stock_cod <= 0)
        {
            system("cls");
            printf("\n==========Cadastro de Estoque========== \n");
            printf("\n Posicao no vetor - Codigo do Item - Item \n");
            printf("          0       -        1       - Pao de Forma.\n");
            printf("          1       -        2       - Pao de Centeio.\n");
            printf("          2       -        3       - Broa de Milho.\n");
            printf("          3       -        4       - Sonho.\n");
            printf("          4       -        5       - Tubaina.\n\n");
            printf(" Digite o codigo do item no qual se deseja alterar o estoque: ");
            scanf("%d", &stock_cod);

            switch (stock_cod)
            {
            case 1:
                printf("\nPao de Forma de codigo 1\n");
                break;

            case 2:
                printf("\nPao de Centeio de codigo 2\n");
                break;

            case 3:
                printf("\nBroa de Milho de codigo 3\n");
                break;

            case 4:
                printf("\nSonho de codigo 4\n");
                break;

            case 5:
                printf("\nTubaina de codigo 5\n");
                break;

            default:
                codigo_invalido();
            }
        }

        printf("Digite a quantidade que deseja alterar no estoque: ");
        scanf("%d", &stock_add);

        if (stock_add >= 0)
        {
            printf("Quantidade Valida\n");
            system("pause");
            stock[stock_cod - 1].qnt = stock[stock_cod - 1].qnt + stock_add;
        }
        else
        {
            quantidade_invalida();
        }

        stock_cod = 0; // variavel voltou a 0 para repeticao funcionar corretamente

    } while (stock_add < 0);
}
// FIM DA FUNCAO DE CADASTRO DE ESTOQUE

// INICIO DA FUNCAO DE VISUALIZAR ESTOQUE
struct itens visualizar_estoque()
{
    system("cls");
    printf("\n===================Menu de Itens========================\n");
    printf(" ___________________________________________________________\n");
    printf("|_Item(codigo)|__Nome do Item____|_Valor(Unidade)_|_Estoque_|\n");
    printf("       1      |  Pao de Forma    |     R$7,50     |    %d   \n", stock[0].qnt);
    printf("       2      |  Pao de Centeio  |     R$8,69     |    %d   \n", stock[1].qnt);
    printf("       3      |  Broa de Milho   |     R$5,00     |    %d   \n", stock[2].qnt);
    printf("       4      |  Sonho           |     R$4,50     |    %d   \n", stock[3].qnt);
    printf("       5      |  Tubaina         |     R$3,25     |    %d   \n", stock[4].qnt);
}
// FIM DA FUNCAO DE VISUALIZAR ESTOQUE

// INICIO DA FUNCAO DE REALIZAR VENDAS
struct itens realizar_vendas()
{
    int venda_cod = 0;
    int venda_outra = 0;
    int venda_qnt = 0;
    int venda_stock = 0;

    int qnt_desejada[5] = {0, 0, 0, 0, 0};

    int pag_cod = 0;
    int pag_parc = 0;

    float acrescimo[2] = {0, 0};
    float desconto[3] = {0, 0, 0};
    float valor_total = 0;
    float valor_parc = 0;
    float valor_adc[5] = {0, 0, 0, 0, 0};
    int itens_adc[5] = {0, 0, 0, 0, 0};
    int itens_total = 0;
    float valor_pago = 0;
    float troco = 0;

    for (int i = 0; i < 5; i++)
    {
        venda_stock = venda_stock + stock[i].qnt;
    }

    if (venda_stock > 0)
    {

        do
        {
            venda_outra = 0;

            do
            {
                do
                {

                    visualizar_estoque();
                    printf("\n Digite o codigo do item desejado:  ");
                    scanf("%d", &venda_cod);

                    switch (venda_cod)
                    {
                    case 1:
                        system("cls");
                        printf("\nVoce selecionou Pao de Forma\n");
                        stock[venda_cod - 1].cod = 1;
                        strcpy(stock[0].nome, "Pao de Forma");
                        stock[0].valor = 7.50;
                        break;

                    case 2:
                        system("cls");
                        printf("\nVoce selecionou Pao de Centeio\n");
                        stock[venda_cod - 1].cod = 2;
                        strcpy(stock[1].nome, "Pao de Centeio");
                        stock[1].valor = 8.69;
                        break;

                    case 3:
                        system("cls");
                        printf("\nVoce selecionou Broa de Milho\n");
                        stock[2].cod = 3;
                        strcpy(stock[2].nome, "Broa de Milho");
                        stock[2].valor = 5.00;
                        break;

                    case 4:
                        system("cls");
                        printf("\nVoce selecionou Sonho\n");
                        stock[3].cod = 4;
                        strcpy(stock[3].nome, "Sonho");
                        stock[3].valor = 4.50;
                        break;

                    case 5:
                        system("cls");
                        printf("\nVoce selecionou Tubaina\n");
                        stock[4].cod = 5;
                        strcpy(stock[4].nome, "Tubaina");
                        stock[4].valor = 3.25;
                        break;

                    default:
                        codigo_invalido();
                    }

                } while (venda_cod <= 0 || venda_cod > 5);

                if (stock[venda_cod - 1].qnt == 0)
                {
                    system("cls");
                    printf("Item sem estoque\n");
                    system("Pause");
                }

            } while (stock[venda_cod - 1].qnt == 0);

            printf("Estoque: %d unidades\n\n", stock[venda_cod - 1].qnt);

            do
            {
                venda_outra = 0;

                printf("Digite a Quantidade Desejada do Item:  ");
                scanf("%d", &qnt_desejada[venda_cod - 1]);
                printf("Voce adiconou %d unidades.\n", qnt_desejada[venda_cod - 1]);

                if (qnt_desejada[venda_cod - 1] <= stock[venda_cod - 1].qnt && qnt_desejada[venda_cod - 1] > 0)
                {
                    stock[venda_cod - 1].qnt = stock[venda_cod - 1].qnt - qnt_desejada[venda_cod - 1];
                    stock[venda_cod - 1].valor_total_item = qnt_desejada[venda_cod - 1] * stock[venda_cod - 1].valor;
                    relatorio[venda_cod - 1].qnt = relatorio[venda_cod - 1].qnt + qnt_desejada[venda_cod - 1];

                    valor_adc[venda_cod - 1] = valor_adc[venda_cod - 1] + stock[venda_cod - 1].valor_total_item;
                    itens_adc[venda_cod - 1] = itens_adc[venda_cod - 1] + qnt_desejada[venda_cod - 1];
                }
                else
                {
                    do
                    {
                        printf("\nQuantia Invalida ou Estoque Insuficiente\n");
                        printf("\nDeseja tentar novamente?\nA opcao 2 voltara para o menu principal...\n");
                        printf("1. Sim\n");
                        printf("2. Nao\n");
                        scanf("%d", &venda_outra);
                        system("cls");
                        if (venda_outra == 2)
                        {
                            menu_principal();
                        }
                        else if (venda_outra != 1 && venda_outra != 2)
                        {
                            codigo_invalido();
                        }

                    } while (venda_outra != 1 && venda_outra != 2);
                }

            } while (venda_outra == 1);

            venda_outra = 0;

            do
            {
                printf("Deseja realizar outra venda?\n");
                printf("1. Sim\n");
                printf("2. Nao\n");
                scanf("%d", &venda_outra);

                if (venda_outra < 1 || venda_outra > 2)
                {
                    codigo_invalido();
                }

            } while (venda_outra != 1 && venda_outra != 2);


        } while (venda_outra == 1);

        // SOMA DO VALOR TOTAL PARA O CUPOM
        for (int i = 0; i < 5; i++)
        {
            valor_total = valor_total + valor_adc[i];
        }
        // SOMA DO VALOR TOTAL PARA O CUPOM

        // SOMA DOS DA QUANTIA TOTAL PARA O CUPOM
        for (int i = 0; i < 5; i++)
        {
            itens_total = itens_total + itens_adc[i];
        }
        // SOMA DOS DA QUANTIA TOTAL PARA O CUPOM

        // CUPOM FISCAL
        system("cls");
        printf("\n=======================CUPOM FISCAL======================\n");
        printf("\nITEM -   NOME DO ITEM  - VALOR(un) - QUANTIA -     VALOR\n");

        for (int i = 0; i <= 5; i++)
        {
            if (valor_adc[i] != 0)
            {
                printf("%-2d   - %15s -   %.2f    -   %2d    - $%8.2f \n", i + 1, stock[i].nome, stock[i].valor, itens_adc[i], valor_adc[i]);
            }
        }

        printf("Valor total.....................................: R$%.2f \n", valor_total);
        printf("Quantia total...................................: %d itens\n", itens_total);
        system("pause");
        // CUPOM FISCAL

        //========================================INICIO DO PAGAMENTO================================================
        do
        {
            system("cls");

            printf("\n\n Formas de pagamento:\n");
            printf(" 1 = Desconto a Vista.\n");
            printf(" 2 = A prazo.\n");

            printf("\n Selecione a Forma de Pagamento:  ");
            scanf("%d", &pag_cod);

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
                    printf("\n\nTotal - Desconto: R$ %.2f - R$ %.2f", valor_total, desconto[0]);
                    valor_total = valor_total - desconto[0];
                    printf("\nTotal com Desconto: R$ %.2f\n", valor_total);
                }
                else if (valor_total > 50 && valor_total < 100)
                {
                    printf("\n\nTotal - Desconto: R$ %.2f - R$ %.2f", valor_total, desconto[1]);
                    valor_total = valor_total - desconto[1];
                    printf("\nTotal com Desconto: R$ %.2f \n", valor_total);
                }
                else
                {
                    printf("\n\nTotal - Desconto: R$ %.2f - R$ %.2f", valor_total, desconto[2]);
                    valor_total = valor_total - desconto[2];
                    printf("\nTotal com Desconto: R$ %.2f \n", valor_total);
                }

                system("pause");

                int troco_sim_nao = 0;

                printf("\nTroco necessario para o pagamento?\n");
                printf("1. Sim\n");
                printf("2. Nao\n");
                scanf("%d", &troco_sim_nao);

                if (troco_sim_nao == 1)
                {
                    do
                    {
                        printf("Valor Final: R$%.2f", valor_total);
                        printf("\nInsira o Valor Pago: R$ ");
                        scanf("%f", &valor_pago);
                        troco = valor_pago - valor_total;

                        if (valor_pago < valor_total)
                        {
                            troco = troco * -1;
                            printf("\n Valor insulficiente para realizar a compra! \n Faltam %.2f \n\n", troco);
                            printf(" Digite o Valor novamente...\n\n");
                        }
                        else
                        {
                            printf("\n Seu troco e: R$ %.2f", troco);
                            printf("\n\n OBRIGADO, VOLTE SEMPRE! \n\n");
                            system("pause");
                            menu_principal();
                        }
                        break;

                    } while (valor_pago < valor_total);
                }

                do
                {
                    printf("Valor total: %.2f", valor_total);
                    printf("\n\nInsira o Valor Pago: R$ ");
                    scanf("%f", &valor_pago);

                    if (fabs(valor_total - valor_pago) < 0.01)
                    {
                        printf("Compra Finalizada!!!\n");
                        system("pause");
                        menu_principal();
                    }

                    printf("Valor invalido ou insuficiente\n");
                    system("pause");

                } while (valor_pago != valor_total);

            case 2:

                do
                {
                    printf("\n\n Numero de parcelas (MAX 12!):");
                    scanf("%d", &pag_parc);

                    if (pag_parc <= 3 && pag_parc > 1)
                    {
                        valor_total = valor_total + acrescimo[0];
                        valor_parc = valor_total / pag_parc;

                        printf("\nSua compra sera dividida em %d parcelas\n", pag_parc);
                        printf("\nTotal + Acrescimo: R$ %.2f + R$ %.2f", valor_total, acrescimo[0]);
                        printf("\nTotal com Acrescimo: R$ %.2f ", valor_total);
                        printf("\nValor de cada Parcela: R$ %.2f \n", valor_parc);
                        system("pause");
                    }
                    else if (pag_parc > 3 && pag_parc <= 12)
                    {
                        valor_total = valor_total + acrescimo[1];
                        valor_parc = valor_total / pag_parc;

                        printf("\n\nSua compra sera dividida em %d parcelas\n", pag_parc);
                        printf("\nTotal + Acrescimo: R$ %.2f + R$ %.2f", valor_total, acrescimo[1]);
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
                codigo_invalido();
                break;
            }
            break;

        } while (pag_cod < 1 || pag_cod > 2);

        //=======================================FINAL DO PAGAMENTO===========================================
    }
    else
    {
        system("cls");
        printf("Primeiro adicione estoque\n");
        system("pause");
        menu_principal();
    }
}
// FIM DA FUNCAO DE REALIZAR VENDAS

// INICIO DA FUNCAO SAIR E RELATORIO DE VENDAS
struct itens_vendidos realatorio_vendas()
{
    int sair = 0;

    strcpy(relatorio[0].nome, "Pao de forma");
    strcpy(relatorio[1].nome, "Pao de Centeio");
    strcpy(relatorio[2].nome, "Broa de Milho");
    strcpy(relatorio[3].nome, "Sonho");
    strcpy(relatorio[4].nome, "Tubaina");

    do
    {
        system("cls");
        printf("Relatorio de Vendas\n\n");
        printf("Foi vendido de cada item:\n");

        for (int i = 0; i < 5; i++)
        {
            printf("%d  -  %s\n", relatorio[i].qnt, relatorio[i].nome);
        }

        printf("\n\nDeseja realmente sair do programa?\n");
        printf("1. Sim\n");
        printf("2. Nao\n");
        scanf("%d", &sair);
        if (sair == 1)
        {
            system("cls");
            printf("  PROGRAMA FINALIZADO!!!\n\n");
            exit(0);
        }
        else if (sair == 2)
        {
            menu_principal();
        }
        else
        {
            codigo_invalido();
        }

    } while (sair > 2 || sair < 1);
}
// FIM DA FUNCAO SAIR E RELATORIO DE VENDAS

// FIM DAS FUNCOES

// INICIO DA FUNCAO PRINCIPAL
int main()
{
    printf("\033[0;32m");
    menu_principal();
    return 0;
}
// FIM DA FUNCAO PRINCIPAL E DO CODIGO