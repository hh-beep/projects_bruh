#include <stdio.h>

// ~ Os arquivos foram importados aqui para que nos dê a possibilidade de separar
// ~ as funções de sistemas das funções de menus/submenus, ou seja, em Cadastro.c
// ~ estará declarado as funções relacionadas à criação e mostrar os cadastros, 
// ~ o que é chamado aqui no codigo dos sub-menus.
#include "Menus.h"
#include "Cadastro.h"
#include "Pagamentos.h"



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


void menuVendasCompra(  struct Product** listaProdutos, int contadorProdutos  ) {
  
  int getProduct;
  int productId;
  int hasProduct = 0;     // essa variavel serve para ajudar na verificação de se o usuario de fato escolheu algum produto.

  
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
  printf("\n\n");
  

  printf("Qual item deseja ser comprado?\n =>");
  scanf("%d", &getProduct);
  
  

  do {
    for (  int i = 0; i < contadorProdutos; i++  ) {
      if (  (*listaProdutos)[i].codigo == getProduct  ) {
        hasProduct = 1;
        productId = (*listaProdutos)[i].codigo;
      }   
    }
    // ~ O if aqui ele está servindo mais para printar na tela caso, mesmo após o for,
    // ~ ainda não encontre um item com o codigo digitado
    if (  hasProduct == 0  ) {
      printf("\n\nNão há produto com esse codigo cadastrado no sistema!!!\nDigite outro valor!\n\n => ");
      scanf("%d", &getProduct);
    }
  } while (  hasProduct == 0  );


  printf("getProduct: %d \n\n", getProduct);
}


//void menuVendasSangria() {}


//void menuVendasPagamento() {}


void menuVendas(  int* opcaoSubMenu, struct Product** listaProdutos, int contadorProdutos  ) {
    
  int opcaoVendas;
  
  menuVendasOpts(  &(*opcaoSubMenu)  );


  do {
    switch(  *opcaoSubMenu  ) {
      case 1:
        menuVendasCompra(  &(*listaProdutos), contadorProdutos  );
        menuVendasOpts(  &(*opcaoSubMenu)  ); 
        break;

      case 2:
        menuVendasOpts(  &(*opcaoSubMenu)  ); 
        break;

      case 3:
        menuVendasOpts(  &(*opcaoSubMenu)  ); 
        break;

      default:
        printf("\n\nVoltando ao Menu Principal...");
        break;
    }
  } while (  *opcaoSubMenu != 4  );
};


/*
void menuAbertura();

void menuFechamentos();

void menuRelatorios();


*/
