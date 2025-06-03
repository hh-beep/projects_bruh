#ifndef MENUS_H
#define MENUS_H

// ~ Importação das declarações de outros arquivos
#include "Cadastro.h"
#include "Pagamentos.h"





void menuPrincipal(  int* opcaoSubMenu  );


void menuCadastrosOpts(  int* opcaoSubMenu  );
void menuCadastros(  int* opcaoSubMenu, struct User** listaUsuarios, int* contadorUsuarios, struct Product** listaProdutos, int* contadorProdutos  );


void menuVendasOpts(  int* opcaoSubMenu  );
void menuVendasCompra(  struct Carrinho* carrinhoCompras, struct Product** listaProdutos, int contadorProdutos  );
void menuVendas(  
    struct Pagamentos** listaPagamentos, struct Carrinho* carrinhoCompras, struct Product** listaProdutos, 
    int* opcaoSubMenu, int* contadorPagamentos, int contadorProdutos, float *valorCaixa 
);
void verificarPagamentosAbertos(struct Pagamentos** listaPagamentos, int contadorPagamentos, struct Carrinho* carrinhoCompras);


void menuAbertCaixaOpts(  int* opcaoSubMenu  );
void menuAbertCaixa(  int* opcaoSubMenu, float* valorCaixa, char* isOpenCaixa  );


void menuFechaCaixa(  struct Pagamentos* listaPagamentos, int contadorPagamentos, float valorCaixa  );


void menuRelatorios(  struct Pagamentos* listaPagamentos, int contadorPagamentos  );


#endif
