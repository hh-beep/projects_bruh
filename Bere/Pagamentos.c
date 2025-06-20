#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ~ Importz
#include "Cadastro.h"
#include "Pagamentos.h"




// ~ Nessa função da struct Pagamentos* importamos o carrinho de Compras para que 
// ~ fique mais facil na parte de atribuir um novo pagamento, ao inves de passar 
// ~ como parametro 3 propiedades.
struct Pagamentos* novoPagamento (  struct Pagamentos* listaPagamentos, struct Carrinho carrinhoCompras, int* contadorPagamentos, int tipoPagamento  ) {



  // ~ Realocação da memoria da variavel listaPagamentos para adicionar novos itens
  // ~ dinamicamente à variavel listaPagamentos.
  listaPagamentos = realloc(  listaPagamentos, sizeof(  struct Pagamentos  ) * (*contadorPagamentos + 1)  );


  int total = carrinhoCompras.totalItems;



  // ~ Só uma verificação (se a variavel dps de realocar é diferente de null) 
  // ~ para evitar erro .
  if (  listaPagamentos == NULL  ) {
    printf("Uhhh, deu algum erro em realocar a memoria da parte dos pagamentos :/\n");
    exit(1);
  }


  printf("\nRegistrando Pagamento...\n\n"); 
  

  // ~ Atribuição de Valores à lista de Pagamentos
  listaPagamentos[*contadorPagamentos].codigo = *contadorPagamentos;
  
  switch(  tipoPagamento  ) {
    case 1: 
      strcpy(  listaPagamentos[*contadorPagamentos].tipo, "Dinheiro"  ); 
      break;

    case 2: 
      strcpy(  listaPagamentos[*contadorPagamentos].tipo, "Cartao"  ); 
      break;
  
    default: 
      strcpy(  listaPagamentos[*contadorPagamentos].tipo, "Dinheiro e Cartao"  ); 
      break;
  } 

  // ~ A gente também estará guardando no item atual da listaPagamentos todos os tipos
  // ~ de valores, além de uma copia dos itens comprados.
  listaPagamentos[*contadorPagamentos].valorMateriais = carrinhoCompras.valorMateriais;  
  listaPagamentos[*contadorPagamentos].valorAlimentos = carrinhoCompras.valorAlimentos;
  listaPagamentos[*contadorPagamentos].valorPadaria = carrinhoCompras.valorPadaria;
  listaPagamentos[*contadorPagamentos].valorTotal = carrinhoCompras.valorTotal;



  listaPagamentos[*contadorPagamentos].itensComprados = malloc(sizeof(struct itemCarrinho) * total);

  // Copiar os itens manualmente
  for (int i = 0; i < total; i++) {
      listaPagamentos[*contadorPagamentos].itensComprados[i] = carrinhoCompras.itensCarrinho[i];
  }

  // BONUS: salvar o total de itens também
  listaPagamentos[*contadorPagamentos].totalItems = total;


  (*contadorPagamentos)++;

  return listaPagamentos;
}





// ~ A função vai adicionar na variavel carrinhoCompras (declarado em Pagamentos.h) o produto escolhido
// ~ no menuCompraVendas e a quantidade desse produto
void addCarrinho (  struct Carrinho* carrinhoCompras, struct Product* produtoEscolhido, int qnt  ) {


  // ~ Essa verificação serve só pra ver se o carrinho foi alocado a memoria corretamente e talz
  if (carrinhoCompras == NULL) {  return;  }




  // ~ Isso daq tamo usando pra fazer uma copia da quantidade passada pra função, modificando e fazendo
  // ~ verificationz
  int copyQuanty = qnt;



  //  ~ Reorganização de memória
  carrinhoCompras->itensCarrinho = realloc(carrinhoCompras->itensCarrinho, sizeof(struct itemCarrinho) * (carrinhoCompras->totalItems + 1));
  if (carrinhoCompras->itensCarrinho == NULL) {
      printf("Erro ao alocar memória para o carrinho!\n");
      exit(1);
  }

    // ~ Copia do produto do carrinho
    carrinhoCompras->itensCarrinho[carrinhoCompras->totalItems].produtoEscolhido = *produtoEscolhido;
    carrinhoCompras->itensCarrinho[carrinhoCompras->totalItems].quant = copyQuanty;
    carrinhoCompras->totalItems++;

    float subtotal = produtoEscolhido->precoVenda * copyQuanty;

    if (strcmp(produtoEscolhido->category, "Alimentos") == 0) carrinhoCompras->valorAlimentos += subtotal;
    else if (strcmp(produtoEscolhido->category, "Materiais") == 0) carrinhoCompras->valorMateriais += subtotal;
    else if (strcmp(produtoEscolhido->category, "Padaria") == 0) carrinhoCompras->valorPadaria += subtotal;

    carrinhoCompras->valorTotal += subtotal;

    //  ~ Reduz o estoque
    produtoEscolhido->quant -= copyQuanty;

    //  ~ Alertas de estoque mínimo e essas paradas :)
    if (produtoEscolhido->quant <= produtoEscolhido->quantMin && produtoEscolhido->quant > 0) {
        printf("\n ~ ALERTA ~ \nEstoque mínimo atingido para o produto [%s] (Min: %d | Atual: %d)\n",
               produtoEscolhido->nome, produtoEscolhido->quantMin, produtoEscolhido->quant);
    }

    if (produtoEscolhido->quant == 0) {
        printf("\n ~ ALERTA ~ \nEstoque zerado após essa venda para o produto [%s].\n", produtoEscolhido->nome);
    }
}


void startCarrinho(  struct Carrinho** carrinhoCompras  ) {
  *carrinhoCompras = malloc(sizeof(struct Carrinho));
  if (*carrinhoCompras == NULL) {
      printf("Erro ao alocar memória para o carrinho!\n");
      exit(1);
  }
  (*carrinhoCompras)->itensCarrinho = NULL;
  (*carrinhoCompras)->totalItems = 0;
  (*carrinhoCompras)->valorAlimentos = 0;
  (*carrinhoCompras)->valorMateriais = 0;
  (*carrinhoCompras)->valorPadaria = 0;
  (*carrinhoCompras)->valorTotal = 0;
}


void resetCarrinho (  struct Carrinho* carrinhoCompras  ) {
  free(carrinhoCompras->itensCarrinho);
  carrinhoCompras->itensCarrinho = NULL;
  carrinhoCompras->totalItems = 0;
  carrinhoCompras->valorAlimentos = 0;
  carrinhoCompras->valorMateriais = 0;
  carrinhoCompras->valorPadaria = 0;
  carrinhoCompras->valorTotal = 0;
}




//                    ~ Operações de Caixa ~
void abrirCaixa(  float* valorCaixa, char* isOpenCaixa  ) {
  printf("\n\n\n");
  printf("Digite o valor em que se queira iniciar o Caixa do Dia: \n");
  printf(" => ");
  scanf("%f", &(*valorCaixa));

  while (  *valorCaixa < 0 ) {
    printf("\n\nOpção Invalida!\nDigite novamente:  ");
    scanf("%d", &(*valorCaixa));
  }
  
  // ~ Definindo que o Caixa já foi abrido :D
  (*isOpenCaixa) = 'S';
 
  printf("\n\n\n");
  printf("O Caixa foi Aberto com o valor de: R$ %.2f!", *valorCaixa);
  printf("\n\n\n");
}


void retiradaCaixa(  float* valorCaixa  ) {
  while (1) {
    if (  *valorCaixa > 50.0  ) {
      float valorSangria;
      printf("Qual o valor que deseja se retirar do caixa? [0 para voltar ao menu]\n => ");
      scanf("%f", &valorSangria);
    
      if (  valorSangria < 0.0  ) {
        printf("\n\n\nValor de retirada Invalido!\n\n\n");
      }
      else if (  valorSangria > 0.0) {
        float novoValorCaixa = (*valorCaixa) - valorSangria;
        
        if (  novoValorCaixa <= 0.0  ) {
          printf("\n\n\nO valor de retirada é maior que o valor em caixa!!!\nValor em Caixa: R$ %.2f \n\n\n", *valorCaixa);
        }
        else if (  novoValorCaixa < 50 ) {
          printf("\n\n\nÉ preciso deixar pelo menos 50 reais no caixa!!!\nValor em Caixa: R$ %.2f \n\n\n", *valorCaixa);
        }
        else {
          *valorCaixa -= novoValorCaixa;
          printf("\n\n\nValor Retirado do caixa: R$ %.2f \nValor Atual de Caixa: %.2f\n\n Voltando ao Sub-Menu...\n\n\n", novoValorCaixa, *valorCaixa);
          break;
        }
      }
      else {
        printf("\n\nVoltando ao menu...\n\n");
        break;
      }
    }
    // ~ Aqui o alert de 50 não acaba sendo acionado pq né... não tem nem 50 reais no caixa 
    else if ((  *valorCaixa > 0.0  ) && (  *valorCaixa <= 50.0)) {
      printf("\n\n\nÉ preciso deixar pelo menos 50 reais no caixa!!!\nvalor atual do caixa [%.2f]\n\n\n", *valorCaixa); 
      break;
    }
    else {
      printf("\n\n\nNão há valor no caixa para realizar retirada!!!\n\nVoltando...\n\n\n\n");
      break;
    }
  }
}