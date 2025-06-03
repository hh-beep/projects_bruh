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





void menuVendasCompra(  struct Carrinho* carrinhoCompras, struct Product** listaProdutos, int contadorProdutos  ) {
  
  int getProduct;
  int productId;
  int hasProduct = 0;     // essa variavel serve para ajudar na verificação de se o usuario de fato escolheu algum produto.

  
  printf("\n\n\n");
  printf("--- Comprar um novo Produto ---\n");
  printf("  ~  \n\n\n");
  printf("Cod.\t Nome\t Categoria\t Valor\t Quantidade\n\n");
  for (  int i = 0; i < contadorProdutos; i++  ) {
    printf("[%d]\t ", (*listaProdutos)[i].codigo);
    printf("%s\t ", (*listaProdutos)[i].nome);
    printf("%s\t ", (*listaProdutos)[i].category);
    printf("%.2f\t ", (*listaProdutos)[i].precoVenda);
    printf("%d\t\n ", (*listaProdutos)[i].quant);
  }
  printf("\n\n\n");
  

  printf("Qual item deseja ser comprado? [0: sair do menu]\n => ");
  scanf("%d", &getProduct);
  printf("\n\n");
  

  do {
    for (  int i = 0; i < contadorProdutos; i++  ) {
      // ~ aq só tá verificando se o produto escolhido ainda tem estoque (se o estoque for maior q zero ), entrando dnv o loop até sair 
      if (  (*listaProdutos)[i].quant <= 0  ) {
        // ~ uhhh, aqui não precisaria desse if e um while, poderia só ter o while em si, mas como lá em baixo já tá sendo usado um else if 
        while (  (*listaProdutos)[i].quant <= 0 && (*listaProdutos)[i].codigo == getProduct  ) {
          printf("\nO item escolhido não tem estoque!!!\n");
          printf("Qual outro item vc deseja ser comprado? [0: sair do menu]\n => ");
          scanf("%d", &getProduct);
          printf("\n\n");
        }
      }  


      // ~ Ele entrará nesta verificação se o houver algum produto com codigo digitado pelo usuario 
      // ~ executando a função da compra já aqui dentro dessa verificação.
      else if (  (*listaProdutos)[i].codigo == getProduct  && (*listaProdutos)[i].quant > 0  ) {
      
        int getQuant;
        
        printf("Qual será a quantidade de itens a serem compradas?\n => ");
        scanf("%d", &getQuant);
        printf("\n\n");


        // ~ Loop de evitar quant invalida
        while ((  getQuant > (*listaProdutos)[i].quant  ) || (  getQuant <= 0  )) {
          printf("\n\nQuantidade Invalida!\nDigite a quantidade novamente (quant. disponivel: %d)\n => ", (*listaProdutos)[i].quant);
          scanf("%d", &getQuant);
        }

        addCarrinho(carrinhoCompras, &(*listaProdutos)[i], getQuant);

        hasProduct = 1;
      } 
    }
    if (  getProduct == 0  ) {
      printf("\n\nVoltando ao Sub-Menu de Vendas...\n\n");
      return;
    }
    // ~ O if aqui ele está servindo mais para printar na tela caso, mesmo após o for,
    // ~ ainda não encontre um item com o codigo digitado
    else if (  hasProduct == 0  ) {
      printf("\n\nNão há produto com esse codigo cadastrado no sistema!!!\nDigite outro valor!\n\n => ");
      scanf("%d", &getProduct);
    }
  } while (  hasProduct == 0  );
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