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


  // ~ Essa verificação serve só pra ver se o carrinho foi alocado a memoria corretamente e talz além de, dps, zerar os itens da struct para evitar problemas de alocação
  if (carrinhoCompras == NULL) {
    carrinhoCompras = malloc(sizeof(struct Carrinho));
    carrinhoCompras->itensCarrinho = NULL;
    carrinhoCompras->totalItems = 0;
    carrinhoCompras->valorAlimentos = 0;
    carrinhoCompras->valorMateriais = 0;
    carrinhoCompras->valorPadaria = 0;
    carrinhoCompras->valorTotal = 0;
}




  // ~ Isso daq tamo usando pra fazer uma copia da quantidade passada pra função, modificando e fazendo
  // ~ verificationz
  int copyQuanty = qnt;


  while (  produtoEscolhido->quant < copyQuanty  ) {

  };


  // ~ Realocação da memoria do item itensCarrinho (que também é uma struct) da struct carrinhoCompras
  // ~ É o local onde guardamos uma copia do produtoEscolhido pelo usuario no menu de Compras.
  (*carrinhoCompras).itensCarrinho = realloc(
        carrinhoCompras->itensCarrinho,
        // ~ Ao inves de utilizar um contador para aumentar o tamanho desse array dinamico do carrinho,
        // ~ tá sendo pego a propiedade de dentro da struct totalItems 
        sizeof(struct itemCarrinho) * (carrinhoCompras->totalItems + 1)  
  );



  if (  (*carrinhoCompras).itensCarrinho == NULL  ) {
    printf("Uhhh, deu algum erro na realocação de memoria dos itensCarrinho :/ \n\n");
    exit(1);
  }


  
   /* 
    *  Passando valores para as variaveis carrinhoCompras 
    * 
    *  essas  [chaves] tão sendo usadas para definir o item [x] da propiedade itensCarrinho (tipo quando)
    *  a gente chama variavel[i] em um for
    *
    */
  carrinhoCompras->itensCarrinho[carrinhoCompras->totalItems].produtoEscolhido = *produtoEscolhido;
  carrinhoCompras->itensCarrinho[carrinhoCompras->totalItems].quant = copyQuanty;
  carrinhoCompras->totalItems++;  



   /*
    *  Mais um blocão de comentario aq 
    *
    *  Uhh, aq em baixo, o programa ele faz a multiplicação entre o valor de venda do produto e a quantidade,
    *  e dps verifica qual é a categoria do produto (usandoi o strcmp (msm coisa que string = "valor a verificar"))
    *  somando dai no valor da categoria o valor total da compra do produto escolhido.
    *
    *  e no finalzinho ali ele incrementa/soma/sla na variavel valorTotal o valor da compra.
    */
  float subtotal = produtoEscolhido->precoVenda * copyQuanty;

  if (strcmp(produtoEscolhido->category, "Alimentos") == 0) {
      carrinhoCompras->valorAlimentos += subtotal;
  } else if (strcmp(produtoEscolhido->category, "Materiais") == 0) {
      carrinhoCompras->valorMateriais += subtotal;
  } else if (strcmp(produtoEscolhido->category, "Padaria") == 0) {
      carrinhoCompras->valorPadaria += subtotal;
  }

  carrinhoCompras->valorTotal += subtotal;



  // ~ Aqui tá aquele thrownback de erro q ele pede caso o estoque minimo seja atingido e a retirada da quanti do produto escolhido e talz 
  produtoEscolhido->quant -= copyQuanty;

  if (  produtoEscolhido->quant <= produtoEscolhido->quantMin  ) {
    printf("\n\n!!!ALERTA!!!\n\nA quantidade minima de: %s foi atingida! ( que era de: %d )\n quantidade atual agora: %d", 
      produtoEscolhido->nome, produtoEscolhido->quantMin, produtoEscolhido->quant
    );
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