#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// ~ Arquivos importados
#include "Pagamentos.h"
#include "Cadastro.h"
#include "Menus.h"





int main() {
  // ~ Permitindo o uso de caracteres com acento e ç no proggerma.
  // ~ Obs: por algum motivo n tá funcionando, n sei se é a fonte, pwershell, sla...
  setlocale(LC_ALL, "Portuguese");

  
  // ~ Sla, outras variaveis usadas no sistema ai :D
  float valorCaixa = 0;

  // ~ Por algum motivo, ao se comparar usando "" aspas dulas, ele compara como
  // ~ se fosse uma string 🤯.
  char isOpenCaixa = 'N';


  // ~ Aqui, são inicialicadas as variaveis relacionadas à criação/modificação de usuarios no sistema, além
  // ~ de estar chamando o arquivo para guardar os dados de usuarios .
  struct User* listaUsuarios = NULL;
  int contadorUsuarios = 0;
  FILE *userData;


  // ~ As variaveis relacionadas aos produtos cadastrados e aos arquivos para exportação dos produtos criadoz.
  struct Product* listaProdutos = NULL;
  int contadorProdutos = 0;
  FILE *productData;

 
  // ~ As variaveis para controle de todos os pagamentos feitos no dia + carrinho de 
  // ~ Compras (que é algo temporario para aquela compra) .
  struct Pagamentos* listaPagamentos = NULL;
  struct Carrinho* carrinhoCompras = NULL;
  int contadorPagamentos = 0;
  int opcaoMenu, opcaoSubMenu = 0;







  // ~ Le Programe  
  menuPrincipal(  &opcaoMenu  );




  // ~ Um Loop que executará enquanto a opção sair (6) não for escolhida;
  do {
    switch (  opcaoMenu  ) {
      case 1:
        menuCadastros(  &opcaoSubMenu, &listaUsuarios, &contadorUsuarios, &listaProdutos, &contadorProdutos  );  
        menuPrincipal(  &opcaoMenu  );
        break;



      case 2:
        // ~ Aqui, a gente tá verificando se há algum produto cadastrado, depois se o 
        // ~ já foi aberto, caso sim, dai a gente prossegue pras vendas :D
        if ((  listaProdutos == NULL  ) && (  contadorProdutos == 0  )) {
          printf("\n\n\nNão ha nenhum produto cadastrado no sistema!!!\n");
          printf("Cadastre algum produto para prosseguir com as vendas\n\n\n");
        }

        else if (  isOpenCaixa == 'N'  ) {
          printf("\n\n\nO caixa do sistema não foi aberto ainda!!!\n");
          printf("Faça a abertura de caixa para prosseguir com as vendas\n\n\n");
        }

        else {
          menuVendas(  &opcaoSubMenu, &listaProdutos, contadorProdutos  );
        }
        

        menuPrincipal(  &opcaoMenu  );
        break;
     



      case 3:
        // ~ Funções localizada em Menus.c
        menuAbertCaixa(  &opcaoSubMenu, &valorCaixa, &isOpenCaixa  );
        menuPrincipal(  &opcaoMenu  );
        break;

      case 4:
        // Fechamento
        menuPrincipal(  &opcaoMenu  );
        break;

      case 5:
        printf("Opt 5");
        menuPrincipal(  &opcaoMenu  );
        break;
      
      default:
        if (  contadorUsuarios > 0  ) {  exportUsuarios(  listaUsuarios, contadorUsuarios, userData  );  }
        if (  contadorProdutos > 0  ) {  exportProdutos(  listaProdutos, contadorProdutos, productData  );  }
        
        break;
    } 
  } while (  opcaoMenu != 6  );


  // ~ Essas função no final do codigo serve para liberar o espaço de memoria alocado por uma função realloc, usado
  // ~ (o que fizemos em Cadastro.c)
  free(listaUsuarios);
  free(listaProdutos);
  free(listaPagamentos);
  return 0;
}
