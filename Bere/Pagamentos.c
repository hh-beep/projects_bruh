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

  listaPagamentos[*contadorPagamentos].itensComprados = carrinhoCompras.itensCarrinho; 


  (*contadorPagamentos)++;

  return listaPagamentos;
}





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

