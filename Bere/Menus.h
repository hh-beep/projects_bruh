#ifndef MENUS_H
#define MENUS_H

// ~ Importação das declarações de outros arquivos
#include "Cadastro.h"
#include "Pagamentos.h"





void menuPrincipal(  int* opcaoSubMenu  );


void menuCadastrosOpts(  int* opcaoSubMenu  );
void menuCadastros(  int* opcaoSubMenu, struct User** listaUsuarios, int* contadorUsuarios, struct Product** listaProdutos, int* contadorProdutos  );


void menuVendasOpts(  int* opcaoSubMenu  );
void menuVendasCompra(  struct Product** listaProdutos, int contadorProdutos  );
void menuVendas(  int* opcaoSubMenu, struct Product** listaProdutos, int contadorProdutos   );


void menuAbertCaixaOpts(  int* opcaoSubMenu  );
void menuAbertCaixa(  int* opcaoSubMenu, float* valorCaixa, char* isOpenCaixa  );


void menuFechamentos();


void menuRelatorios();


#endif
