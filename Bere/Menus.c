#include <stdio.h>
#include <string.h>

// ~ Os arquivos foram importados aqui para que nos dê a possibilidade de separar
// ~ as funções de sistemas das funções de menus/submenus, ou seja, em Cadastro.c
// ~ estará declarado as funções relacionadas à criação e mostrar os cadastros, 
// ~ o que é chamado aqui no codigo dos sub-menus.
#include "Menus.h"
#include "Cadastro.h"
#include "Pagamentos.h"





//                    ~ Menu Principal ~

void menuPrincipal(  int* opcaoMenu  ) {

  printf("\n\n\n\n\n");
  printf("--- Menu Principal ---\n");
  printf("  ~  \n");
  printf("[ 1 ]: Cadastros.\n");
  printf("[ 2 ]: Vendas.\n");
  printf("[ 3 ]: Abertura de Caixa.\n");
  printf("[ 4 ]: Fechamento de Caixa.\n");
  printf("[ 5 ]: Relatorio.\n");
  printf("  ~   \n");
  printf("[ 6 ]: Sair do Programa.\n");
  printf("\n\n");


  // ~ Um get da opção digitada pelo usuario sobre o menu + loop de previnir opção errada.
  printf(" => ");
  scanf("%d", &(*opcaoMenu));
  while ((  *opcaoMenu < 1  ) || (  *opcaoMenu > 6  )) {
    printf("\n\nOpção Invalida!\nDigite novamente:  ");
    scanf("%d", &(*opcaoMenu));
  }
}










//                    ~ Menu Cadastros ~ 

void menuCadastrosOpts(  int* opcaoSubMenu  ) {
  printf("\n\n\n\n\n");
  printf("--- Menu de Cadastros ---");
  printf("  ~  \n");
  printf("[ 1 ]: Cadastrar um Novo Cliente.\n");
  printf("[ 2 ]: Cadastrar um Novo Produto.\n");
  printf("  ~  \n");
  printf("[ 3 ]: Mostrar todos os Clientes.\n");
  printf("[ 4 ]: Mostrar todos os Produtos.\n");
  printf("  ~  \n");
  printf("[ 5 ]: Voltar.\n"); 
  printf("  ~  \n");
  printf("\n\n");
  

  printf(" => ");
  scanf("%d", &(*opcaoSubMenu));
  while ((  *opcaoSubMenu < 1  ) || (  *opcaoSubMenu > 5  )) {
    printf("\n\nOpção Invalida!\nDigite novamente:  ");
    scanf("%d", &(*opcaoSubMenu));
  }
}


void menuCadastros(  int* opcaoSubMenu, struct User** listaUsuarios, int* contadorUsuarios, struct Product** listaProdutos, int* contadorProdutos  ) {


  menuCadastrosOpts(  opcaoSubMenu  );

  do {
    switch (  *opcaoSubMenu  ) {
      case 1:
        // ~ A função novoUsuario foi escrita e declarada em Cadastro.c
        *listaUsuarios = novoUsuario(  &(*listaUsuarios), &(*contadorUsuarios)  );        
        printf("\n\nVoltando ao Sub-Menu...\n\n");
        menuCadastrosOpts(  opcaoSubMenu  );
        break;

      case 2:
        // ~ A função novoProduto foi escrita e declarada em Cadastro.c
        (*listaProdutos) = novoProduto(  &(*listaProdutos), &(*contadorProdutos)  );       
        printf("\n\nVoltando ao Sub-Menu...\n\n");
        menuCadastrosOpts(  opcaoSubMenu  );
        break;

      case 3: 

        // ~ A função de mostrarTodosUsuarios foi declarada em Cadastro.c
        mostrarTodosUsuarios(  *listaUsuarios, *contadorUsuarios  ); 
        printf("\n\nVoltando ao Sub-Menu...\n\n");
        menuCadastrosOpts(  opcaoSubMenu  );
        break;

      case 4:
        // ~ A função de mostrarTodosProdutos foi declarada em Cadastro.c
        mostrarTodosProdutos(  *listaProdutos, *contadorProdutos  );  
        printf("\n\nVoltando ao Sub-Menu...\n\n");
        menuCadastrosOpts(  opcaoSubMenu  );
        break;

      default:
        printf("Voltando ao Menu Principal...\n\n\n");
        break;
    } 
  } while (  *opcaoSubMenu != 5  );
}










//                    ~ Menus de Vendas ~

void menuVendasOpts(  int* opcaoSubMenu  ) {
  printf("\n\n\n\n\n");
  printf("--- Menu de Vendas ---\n");
  printf("  ~  \n");
  printf("[ 1 ]: Nova Venda.\n");
  printf("[ 2 ]: Retirada de Caixa.\n");
  printf("[ 3 ]: Pagamentos.\n");
  printf("  ~  \n");
  printf("[ 4 ]: Voltar ao Menu Principal.\n");
  printf("\n\n");


  printf(" => ");
  scanf("%d", &(*opcaoSubMenu));
  while ((  *opcaoSubMenu < 1  ) || (  *opcaoSubMenu > 4  )) {
    printf("\n\nOpção Invalida!\nDigite novamente:  ");
    scanf("%d", &(*opcaoSubMenu));
  }
} 





void menuVendasCompra(struct Carrinho* carrinhoCompras, struct Product** listaProdutos, int contadorProdutos) {
    int codigoProduto, quantidade;
    int produtoValido = 0;

    while (1) {
        printf("\n--- Lista de Produtos Disponíveis ---\n");
        printf("Código | Nome            | Categoria        | Preço R$ | Estoque\n");
        printf("---------------------------------------------------------------\n");
        for (int i = 0; i < contadorProdutos; i++) {
            printf("%5d | %-15s | %-15s | %7.2f | %d\n",
                (*listaProdutos)[i].codigo,
                (*listaProdutos)[i].nome,
                (*listaProdutos)[i].category,
                (*listaProdutos)[i].precoVenda,
                (*listaProdutos)[i].quant);
        }

        printf("\nInforme o código do produto a ser comprado [0 para voltar]:\n => ");
        scanf("%d", &codigoProduto);
        if (codigoProduto == 0) {  break;  }

        //  ~ Verifica se o produto existe e tem estoque
        for (int i = 0; i < contadorProdutos; i++) {
            if ((*listaProdutos)[i].codigo == codigoProduto) {
                if ((*listaProdutos)[i].quant <= 0) {
                    printf("\nProduto sem estoque! Escolha outro.\n");
                    produtoValido = -1;
                    break;
                }

                printf("Informe a quantidade desejada: \n => ");
                scanf("%d", &quantidade);

                if (quantidade <= 0) {
                    printf("Quantidade inválida!\n");
                    produtoValido = -1;
                    break;
                }

                if (quantidade > (*listaProdutos)[i].quant) {
                    //  ~ Um alert do estoque minimo
                    printf("Atenção: estoque insuficiente! Estoque atual: %d\n", (*listaProdutos)[i].quant);
                    printf("Deseja continuar com %d unidades? \n\t[1 = Sim]\n\t[0 = Não]: \n => ", (*listaProdutos)[i].quant);
                    int continuar;
                    scanf("%d", &continuar);
                    if (continuar == 1) {
                        quantidade = (*listaProdutos)[i].quant;
                    } else {
                        break;
                    }
                }

                // Tudo certo! Adiciona ao carrinho
                addCarrinho(carrinhoCompras, &(*listaProdutos)[i], quantidade);
                produtoValido = 1;

                printf("\n Produto adicionado ao carrinho com sucesso!\n");
                break;
            }
        }

        if (produtoValido == 0)
            printf(" Código de produto inválido! Tente novamente.\n");
    }

    printf("\n Retornando ao menu de vendas...\n");
}





void menuVendasPagamento(  struct Pagamentos** listaPagamentos, int* contadorPagamentos, struct Carrinho* carrinhoCompras  ) {
  // ~ Codigo do pagamentos e talz
  if (carrinhoCompras->totalItems == 0) {
        printf("\n\nNenhum item foi adicionado ao carrinho ainda!\n\n");
        return;
    }

    int opcaoPagamento;
    float total = carrinhoCompras->valorTotal;
    float valorRecebido;
    int pagamentoOk = 0;

    printf("\n\n--- Pagamento ---\n");
    printf("Total da compra: R$ %.2f\n", total);
    printf("[1] Pagamento no Cartao\n");
    printf("[2] Pagamento em Dinheiro\n");
    printf("[3] Voltar ao menu\n");
    printf("\n=> ");
    scanf("%d", &opcaoPagamento);

    switch(opcaoPagamento) {
        case 1: // ~ Pagamento em Cartão
            printf("\nPagamento feito na maquininha? [1 - Sim / 0 - Não]: ");
            scanf("%d", &pagamentoOk);

            if (pagamentoOk == 1) {
                *listaPagamentos = novoPagamento(*listaPagamentos, *carrinhoCompras, contadorPagamentos, 2);
                (*listaPagamentos)[*contadorPagamentos - 1].emAberto[0] = 'f';
                printf("\nPagamento registrado com sucesso!\n");
                resetCarrinho(carrinhoCompras);
            } 
            else {
                printf("\nPagamento nao foi realizado. Voltando ao menu de pagamento.\n");
            }
            break;

        case 2: // ~ Pagamento em Dinheiro
            printf("\nDigite o valor recebido em dinheiro: R$ ");
            scanf("%f", &valorRecebido);

            if (valorRecebido < total) {
                float restante = total - valorRecebido;
                printf("\nValor insuficiente. Deseja pagar os R$ %.2f restantes no cartão? [1 - Sim / 0 - Não]: ", restante);
                scanf("%d", &pagamentoOk);

                if (pagamentoOk == 1) {
                    printf("\nPagamento no cartão realizado com sucesso? [1 - Sim / 0 - Não]: ");
                    scanf("%d", &pagamentoOk);

                    if (pagamentoOk == 1) {
                        *listaPagamentos = novoPagamento(*listaPagamentos, *carrinhoCompras, contadorPagamentos, 3);
                        (*listaPagamentos)[*contadorPagamentos - 1].emAberto[0] = 'f';
                        printf("\n\nPagamento (dinheiro + cartao) registrado com sucesso!\n\n\n");
                        resetCarrinho(carrinhoCompras);
                    } 
                    else {
                        printf("\n\nPagamento cancelado. Voltando ao menu de pagamento...\n\n\n");
                    }
                } 
                else {
                    printf("\n\nPagamento cancelado. Voltando ao menu de pagamento...\n\n\n");
                }
            } 

            else {
                float troco = valorRecebido - total;
                printf("\nTroco a ser devolvido: R$ %.2f\n", troco);
                *listaPagamentos = novoPagamento(*listaPagamentos, *carrinhoCompras, contadorPagamentos, 1);
                (*listaPagamentos)[*contadorPagamentos - 1].emAberto[0] = 'f';
                printf("\nPagamento em dinheiro registrado com sucesso!\n");
                resetCarrinho(carrinhoCompras);
            }
            break;




        case 3:
            printf("\nVoltando ao menu de vendas...\n");
            break;

        default:
            printf("\nOpcao invalida! Voltando ao menu de vendas.\n");
            break;
    }
} 





void menuVendas(  
  struct Pagamentos** listaPagamentos, struct Carrinho* carrinhoCompras, struct Product** listaProdutos, 
  int* opcaoSubMenu, int* contadorPagamentos, int contadorProdutos, float *valorCaixa
) {
    
  int opcaoVendas;
  

  verificarPagamentosAbertos(  &(*listaPagamentos), *contadorPagamentos, carrinhoCompras  );
  menuVendasOpts(  &(*opcaoSubMenu)  );


  do {
    switch(  *opcaoSubMenu  ) {
      case 1:
        menuVendasCompra(  carrinhoCompras, &(*listaProdutos), contadorProdutos  );
        menuVendasOpts(  &(*opcaoSubMenu)  ); 
        break;

      case 2:
        retiradaCaixa(  &(*valorCaixa)  );
        menuVendasOpts(  &(*opcaoSubMenu)  ); 
        break;

      case 3:
        menuVendasPagamento(  &(*listaPagamentos), &(*contadorPagamentos), carrinhoCompras  );
        menuVendasOpts(  &(*opcaoSubMenu)  ); 
        break;

      default:
        printf("\n\nVoltando ao Menu Principal...");
        break;
    }
  } while (  *opcaoSubMenu != 4  );
};





// ~ Verificação se o pagamento está em aberto 
void verificarPagamentosAbertos(struct Pagamentos** listaPagamentos, int contadorPagamentos, struct Carrinho* carrinhoCompras) {
    for (int i = 0; i < contadorPagamentos; i++) {
        if ((*listaPagamentos)[i].emAberto[0] == 'a') {
            printf("\n\nExiste uma venda em aberto!\n");
            printf("Venda nº: %d\n", (*listaPagamentos)[i].codigo);
            printf("Valor total: R$ %.2f\n", (*listaPagamentos)[i].valorTotal);
            printf("Itens comprados: %d\n", (*listaPagamentos)[i].itensComprados ? 1 : 0); // você pode expandir isso depois

            printf("\n\nDeseja finalizar o pagamento agora? [1 - Sim / 0 - Não]: ");
            int finalizarAgora;
            scanf("%d", &finalizarAgora);

            if (finalizarAgora == 1) {
                // Copia os dados do carrinho da venda em aberto para o carrinho atual
                carrinhoCompras->itensCarrinho = (*listaPagamentos)[i].itensComprados;
                carrinhoCompras->valorAlimentos = (*listaPagamentos)[i].valorAlimentos;
                carrinhoCompras->valorMateriais = (*listaPagamentos)[i].valorMateriais;
                carrinhoCompras->valorPadaria = (*listaPagamentos)[i].valorPadaria;
                carrinhoCompras->valorTotal = (*listaPagamentos)[i].valorTotal;
                carrinhoCompras->totalItems = 0;
                // Finalizar o pagamento da venda em aberto
                printf("\n\nEncaminhando para finalizar pagamento...\n\n\n");
                (*listaPagamentos)[i].emAberto[0] = 'f'; // marca como pago

                // Aqui você pode chamar sua função de pagamento direto se quiser, ou retornar o carrinho preenchido
                break;
            } else {
                printf("\nVenda permanecerá em aberto...\n\n\n");
            }
        }
    }
}











//                    ~ Menu de Abertura e Fechamento de caixas ~

void menuAbertCaixaOpts(  int* opcaoSubMenu  ) {
  printf("\n\n\n\n\n");
  printf("--- Menu de Abertura de Caixa ---\n");
  printf("  ~  \n");
  printf("[ 1 ]: Abrir o caixa.\n");
  printf("  ~  \n");
  printf("[ 2 ]: Voltar ao Menu Principal.\n");
  printf("\n\n");


  printf(" => ");
  scanf("%d", &(*opcaoSubMenu));
  while ((  *opcaoSubMenu < 1  ) || (  *opcaoSubMenu > 2  )) {
    printf("\n\nOpção Invalida!\nDigite novamente:  ");
    scanf("%d", &(*opcaoSubMenu));
  }
}





void menuAbertCaixa(  int* opcaoSubMenu, float* valorCaixa, char* isOpenCaixa  ) {
 
  menuAbertCaixaOpts(  &(*opcaoSubMenu)  );

  do { 
    switch(  *opcaoSubMenu  ) {
      case 1: 
        
        // ~ Por algum motivo, ao se comparar usando "" aspas dulas, ele compara como
        // ~ se fosse uma string 🤯.
        if (  *isOpenCaixa == 'S'  ) {  printf("\n\nO caixa já foi aberto hoje!");  }
        // ~ A função de abrirCaixa foi declarada em Pagamentos.c
        else {  abrirCaixa(  &(*valorCaixa), &(*isOpenCaixa)  );  }                
       
        menuAbertCaixaOpts(  &(*opcaoSubMenu)  );
        break;

      default:
        printf("\n\nVoltando ao Menu Principal...");
        break;
    }
  } while(  *opcaoSubMenu != 2  );
}









// ~ Fechamento de caixa e essas parada ai
void menuFechaCaixa(  struct Pagamentos* listaPagamentos, int contadorPagamentos, float valorCaixa  ) {
  float totalVendas = 0, totalDinheiro = 0, totalCartao = 0, totalMisto = 0;
    float totalAlimentos = 0, totalMateriais = 0, totalPadaria = 0;

    printf("\n\n--- FECHAMENTO DE CAIXA ---\n");

    for (int i = 0; i < contadorPagamentos; i++) {
        totalVendas += listaPagamentos[i].valorTotal;
        totalAlimentos += listaPagamentos[i].valorAlimentos;
        totalMateriais += listaPagamentos[i].valorMateriais;
        totalPadaria += listaPagamentos[i].valorPadaria;

        if (strcmp(listaPagamentos[i].tipo, "Dinheiro") == 0)
            totalDinheiro += listaPagamentos[i].valorTotal;
        else if (strcmp(listaPagamentos[i].tipo, "Cartao") == 0)
            totalCartao += listaPagamentos[i].valorTotal;
        else
            totalMisto += listaPagamentos[i].valorTotal;
    }

    printf("Total de Vendas: R$ %.2f\n", totalVendas);
    printf("Valor em Caixa: R$ %.2f\n", valorCaixa);
    printf("\nPor Categoria:\n");
    printf("  Alimentos: R$ %.2f\n", totalAlimentos);
    printf("  Materiais: R$ %.2f\n", totalMateriais);
    printf("  Padaria:   R$ %.2f\n", totalPadaria);
    printf("\nPor Tipo de Pagamento:\n");
    printf("  Dinheiro:            R$ %.2f\n", totalDinheiro);
    printf("  Cartão:              R$ %.2f\n", totalCartao);
    printf("  Dinheiro + Cartão:   R$ %.2f\n", totalMisto);
    printf("\n--------------------------\n");
}










// ~ nahhhhhhh
void menuRelatorios(  struct Pagamentos* listaPagamentos, int contadorPagamentos  ) {
  printf("\n--- RELATÓRIO DE VENDAS ---\n");
    printf("Número total de vendas: %d\n", contadorPagamentos);

    for (int i = 0; i < contadorPagamentos; i++) {
        printf("\nVenda %d:\n", listaPagamentos[i].codigo);
        printf("  Tipo de pagamento: %s\n", listaPagamentos[i].tipo);
        printf("  Valor total: R$ %.2f\n", listaPagamentos[i].valorTotal);
        printf("  Alimentos:   R$ %.2f\n", listaPagamentos[i].valorAlimentos);
        printf("  Materiais:   R$ %.2f\n", listaPagamentos[i].valorMateriais);
        printf("  Padaria:     R$ %.2f\n", listaPagamentos[i].valorPadaria);
        printf("  Situação:    %s\n", listaPagamentos[i].emAberto[0] == 'a' ? "Aberta" : "Fechada");
    }

    printf("\n----------------------------\n");
}