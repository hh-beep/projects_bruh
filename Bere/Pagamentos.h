#ifndef PAGAMENTOS_H
#define PAGAMENTOS_H

// ~ Importando as structs e partes de codigo que estão declarados no Cadastro.h
#include "Cadastro.h"




// ~ Essa struct será responsavel por guardar os valores de todos os pagamentos do dia.
struct Pagamentos {
  int codigo;
  float valor;
  char tipo[50];       // ~ Tipos: Dinheiro, Cartão e Dinheiro e Cartão

  struct itemCarrinho* itensComprados; 

  float valorMateriais;
  float valorAlimentos;
  float valorPadaria;
  
  float valorTotal;

  char emAberto[1]; 
};

/*
 *
 *  As variaveis abaixo servem para armazenar em um carrinho de compras temporário os 
 *  itens escolhidos para comprar pelo usuario na parte das vendas.
 *  
 *  A struct itemCarrinho armazenará o produto que o usuario escolheu, além da 
 *  quantidade.
 *
 *  Já a struct Carrinho em sí guardará tipo um Array de struct em que vai conter a 
 *  lista de todos os produtos escolhidos pelo usuario em uma compra, além do valor
 *  do total de itens, os valores de cada categoria + o valor total das compras.
 *
*/
struct itemCarrinho {
  // ~ A struct chamada aqui não é um ponteiro pois só vamos precisar dos valores
  // ~ do item que o usuario escolheu, não precisando mudar o item escolhido em sí.
  struct Product produtoEscolhido;
  int quant;
};

struct Carrinho {
  // ~ Como explicado outras vezes, essa struct 
  // ~ ponteiro abaixo funciona como um array dinâmico, 
  // ~ ( um "vetor que cresce conforme você adiciona produtos" ).
  struct itemCarrinho* itensCarrinho;
  
  int totalItems;
 
  float valorMateriais;
  float valorAlimentos;
  float valorPadaria;
  
  float valorTotal;
};





struct Pagamentos* novoPagamento(   struct Pagamentos* listaPagamentos, struct Carrinho carrinhoCompras, int* contadorPagamentos, int tipoPagamento  );

/*
void starCarrinho(  struct Carrinho* carrinhoCompras  );

void addCarrinho(  struct Carrinho* carrinhoCompras, struct Product produtoEscolhido, int quantidade  );

void resetCarrinho(  struct Carrinho* CarrinhoCompras  );
*/


void abrirCaixa(  float* valorCaixa, char* isOpenCaixa  );


#endif
