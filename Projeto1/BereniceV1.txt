#include <stdio.h>
#include <stdlib.h>

int main()
{
    int cod, parc, codpag, qnt;
    float valor, total, troco, total_final, acrescimo_5, acrescimo_8, porc1_8, valor_parcela, desconto_5, desconto_10, desconto_18, valor_pago;
    char escolha;

    printf(" ##########Menu de Items Padaria Berenice##########\n");
    printf("  _________________________________________________\n");
    printf(" |_Item(codigo)|__Nome do Item____|_Valor(Unidade)_|\n");
    printf(" |______1______|__Pao de Forma____|_____R$7,50_____|\n");
    printf(" |______2______|__Pao de Centeio__|_____R$8,69_____|\n");
    printf(" |______3______|__Broa de Milho___|_____R$5,00_____|\n");
    printf(" |______4______|__Sonho___________|_____R$4,50_____|\n");
    printf(" |______5______|__Tubaina_________|_____R$3,25_____|\n");
    printf("\n Digite o codigo do item desejado:  ");
    scanf("%d", &cod);

    switch(cod)
    {
        case 1: valor = 7.50;
            printf(" Voce selecionou Pao de Forma\n");
        break;

        case 2: valor = 8.69;
            printf(" Voce selecionou Pao de Centeio\n");
        break;

        case 3: valor = 5.00;
            printf(" Voce selecionou Broa de Milho\n");
        break;

        case 4: valor = 4.50;
            printf(" Voce selecionou Sonho\n");
        break;

        case 5: valor = 3.25;
            printf(" Voce selecionou Tubaina\n");
        break;

        default:
            printf(" Codigo Incorreto!!!!\n");
            exit(0);
    }

    printf("\n Digite a Quantidade Desejada do Item:  ");
    scanf("%d", &qnt);
    printf(" Voce adicionou %d unidades", qnt);

    printf("\n_________________________________________________");

    total = valor * qnt;

    printf("\n\n Valor Unitario: R$ %.2f \n", valor);
    printf("\n Valor Unitario X Quantidade \n R$ %.2f X %d Un", valor, qnt);
    printf("\n\n Valor Total: R$ %.2f ", total);

    printf("\n_________________________________________________");

    printf("\n\n Formas de pagamento:\n");
    printf(" 1 = A prazo.\n");
    printf(" 2 = Desconto a Vista.\n");

    printf("\n Selecione a Forma de Pagamento:  ");
    scanf("%d", &codpag);

    acrescimo_5 = total * 0.05;
    acrescimo_8 = total * 0.08;

    desconto_5 = total * 0.05;
    desconto_10 = total * 0.10;
    desconto_18 = total * 0.18;

    printf("\n_________________________________________________");

    switch(codpag)
    {
        case 1:
            printf("\n\n Numero de parcelas (MAX 12!):");
            scanf("%d", &parc);

            if(parc <= 3)
            {
                total_final = total + acrescimo_5;
                valor_parcela = total_final / parc;

                printf("\n Sua compra sera dividida em %d parcelas\n", parc);
                printf("\n Valor de cada Parcela: R$ %.2f", valor_parcela);
                printf("\n Total + Acrescimo: R$ %.2f + R$ %.2f", total, acrescimo_5);
                printf("\n Total com Acrescimo: R$ %.2f ", total_final);
            }
            else if(parc > 3 && parc <= 12)
            {
                total_final = total + acrescimo_8;
                valor_parcela = total_final / parc;

                printf("\n\n Sua compra sera dividida em %d parcelas\n", parc);
                printf("\n Valor de cada Parcela: R$ %.2f", valor_parcela);
                printf("\n Total + Acrescimo: R$ %.2f + R$ %.2f", total, acrescimo_8);
                printf("\n Total com Acrescimo: R$ %.2f ", total_final);
            }
            else
            {
                printf("\n\n O numero maximo de parcelas e 12");
                exit(0);
            }

            printf("\n_________________________________________________");

            printf("\n\n Gostaria de pagar a primeira parcela agora? (S/N) ");
            scanf(" %c", &escolha);

            switch(escolha)
            {
                case 'S':
                case 's':
                    printf("\n O valor da sua parcela e %.2f \n\n", valor_parcela);
                break;

                case 'N':
                case 'n':
                    printf(" OBRIGADO, VOLTE SEMPRE!");
                    exit(0);
                break;

                default:
                    printf(" Opcao incorreta!!");
                    exit(0);
            }
        break;

        case 2:
            if(total <= 50)
            {
                total_final = total - desconto_5;

                printf("\n\n Total - Desconto: R$ %.2f - R$ %.2f", total, desconto_5);
                printf("\n Total com Desconto: R$ %.2f", total_final);
            }
            else if(total > 50 && total < 100)
            {
                total_final = total - desconto_10;

                printf("\n\n Total - Desconto: R$ %.2f - R$ %.2f", total, desconto_10);
                printf("\n Total com Desconto: R$ %.2f", total_final);
            }
            else 
            {
                total_final = total - desconto_18;

                printf("\n\n Total - Desconto: R$ %.2f - R$ %.2f", total, desconto_18);
                printf("\n Total com Desconto: R$ %.2f", total_final);                
            }

            


        break;
    }

    printf("\n\n Insira o Valor Pago: R$ ");
    scanf("%f", &valor_pago); 
    troco = valor_pago - total_final;
    
    
    if(valor_pago<total_final)
    {
        troco=troco*-1;
        printf("\n Valor insulficiente para realizar a compra! \n Faltam %.2f", troco);
    }
    else
    {
        printf("\n Seu troco e: R$ %.2f", troco);
        printf("\n\n OBRIGADO, VOLTE SEMPRE!");
    }

    return 0;
}