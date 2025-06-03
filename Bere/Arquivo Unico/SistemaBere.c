// --------- Início de Cadastro.c ---------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cadastro.h"




  
// ~ Cadastro de Clientes
 




 /*
  *  Função de criar um novo usuario: 
  *
  *  O codigo abaixo faz o seguinte: pegando a struct User* (que está em Cadastro.h),
  *  ele executa uma função novoUsuario (que, vai criar um novo usuario). É uma função
  *  struct do tipo ponteiro pois apontará para o espaço de memoria de uma variavel que
  *  será criada no main.c
  *
  *
  *  É usado 2 ** pois um apontará para a struct User (criando uma struct de array dinamica) e o outro
  *  para referenciar que o listaUsuarios é um ponteiro (ou seja, estamos mudando o valor da variavel)
  *  
*/ 
struct User* novoUsuario(  struct User** listaUsuarios, int* contadorUsuarios  ) {

  int codigoValido = 0, codigoRepetido = 0;



  /*
   *  A variavel abaixo listaUsuario (que será uma variavel ponteiro criada no main.c) recebe
   *  a função realloc para realocar na memoria de forma dinamica novos usuarios para a
   *  struct, que, neste caso, age também como um tipo de array(vetor), nos permitindo a 
   *  acessar variaveis de struct ao declarar listaUsuarios[  numero  ], que retornará
   *  algum usuario ou um valor null caso não tenha um usuario com esse id
   *
   *  Além disso, o realloc funciona assim: ele recebe a lista(que é a struct) e o novo 
   *  tamanho que vai ser a lista (que no caso será sizeof(struct User)....).
   *  O tamanho é declarado dessa forma para que não precise ser trocado manualmente o tamanho
   *  do array (pois listaUsuarios é um array dinamico, um ponteiro da variavel User*), atraves do calculo que 
   *  é feito, pegando o sizeof da struct User e multiplicando pelo contadorUsuarios + 1.
   *  
   */ 
  *listaUsuarios = realloc(  (*listaUsuarios), sizeof(struct User) * (*contadorUsuarios + 1));

  //  ~ Aqui ele dá um erro caso dê algum problema na variavel da lista de usuarios
  if (  *listaUsuarios == NULL  ) {
    printf("Erro ao alocar memoria de usuario no sistema!!!");
    exit(1);
  }
      


  // ~ Aqui, ele só atribui automaticamente na variavel id o valor do contadorUsuarios
  // ~ (ou seja, a posição da variavel direto).
  (*listaUsuarios[*contadorUsuarios]).id = *contadorUsuarios;



  // ~ Aqui, o a função vai perguntar e atribuir ao item da listaUsuarios as suas propiedades
  // ~ (pois começa sem informações).
  printf("Digite o nome do novo usuario: \n => ");
  // ~ Esses treco que estão dentro do scanf serve para permitir ao usuario a digitar palavras e usar o espaço
  // ~ na string além disso, previne de que a primeira letra digitada não seja "cortada" da string
  scanf(" %[^\n]%*c", (*listaUsuarios)[*contadorUsuarios].nome);
  printf("\n\n");



  printf("Digite o codigo do usuario [val. min: 1000 / val max: 9999]: \n => ");
  scanf("%d", &((*listaUsuarios[*contadorUsuarios]).codigo));
  printf("\n\n");

  // ~ Verificação se o codigo do usuario é valido (ou seja, se é entre 1000 e 9999 ou se não é repetido)
  while (!codigoValido) {
    scanf("%d", &((*listaUsuarios)[*contadorUsuarios].codigo));

    if ((  (*listaUsuarios)[*contadorUsuarios].codigo < 1000  ) || (  (*listaUsuarios)[*contadorUsuarios].codigo > 9999  )) {
      printf("\nCódigo inválido!\nDigite um valor entre [1000] e [9999]:\n => ");
    }

    for (int i = 0; i < *contadorUsuarios; i++) {
      if (  (*listaUsuarios)[i].codigo == (*listaUsuarios)[*contadorUsuarios].codigo  ) {
        codigoRepetido = 1;
        break;
      }
    }

    if (codigoRepetido) {
      printf("\nJá existe um usuario com esse código!\n Digite outro:\n => ");
    } else {
      codigoValido = 1;
    }
  }


  printf("Digite o nome social: \n => ");
  getchar();
  scanf("%[^\n]", &(*listaUsuarios)[*contadorUsuarios].social);
  printf("\n\n");

  printf("Digite o CPF (numeros todos juntos e sem pontuação): \n => ");
  scanf("%lld", &((*listaUsuarios[*contadorUsuarios]).cpf));
  printf("\n\n");

  printf("Digite o CEP (tudo junto e sem pontuação): \n => ");
  scanf("%d", &((*listaUsuarios[*contadorUsuarios]).cep));
  printf("\n\n");

  printf("Digite o Telefone (ex: 45998119312): \n => ");
  scanf("%lld", &((*listaUsuarios[*contadorUsuarios]).telefone));
  printf("\n\n\n");




  // ~ Um printf de que foi gravado um novo usuario
  printf("Novo Usuario Criado!\n\n");
  printf("Nome:\t    %s\n", (*listaUsuarios[*contadorUsuarios]).nome);
  printf("Codigo:\t  %d\n", (*listaUsuarios[*contadorUsuarios]).codigo);
  printf("Social:\t  %s\n", (*listaUsuarios[*contadorUsuarios]).social);
  printf("CPF:\t     %lld\n", (*listaUsuarios[*contadorUsuarios]).cpf);
  printf("CEP:\t     %d\n", (*listaUsuarios[*contadorUsuarios]).cep);
  printf("telefone:\t%lld\n", (*listaUsuarios[*contadorUsuarios]).telefone);
  printf("\n\n");



  // ~ Aumenta dinamicamente o tamanho do Array (vetor) de usuarios
  (*contadorUsuarios)++;



  return *listaUsuarios;
}




void mostrarTodosUsuarios(  struct User* listaUsuarios, int contadorUsuarios  ) {
  

  printf("\n\n\n");
  printf("Mostrando todos os usuarios: ");
  printf("\n\n");

  if (  contadorUsuarios > 0  ) {
    for (  int i = 0; i < contadorUsuarios; i++  ) {
      printf("Usuario [%d] \n", i);
      printf("Nome:\t    %s\n", listaUsuarios[i].nome);
      printf("Codigo:\t  %d\n", listaUsuarios[i].codigo);
      printf("Social:\t  %s\n", listaUsuarios[i].social);
      printf("CPF:\t     %lld\n", listaUsuarios[i].cpf);
      printf("CEP:\t     %d\n", listaUsuarios[i].cep);
      printf("telefone:\t%lld\n", listaUsuarios[i].telefone);
    }
  }
  else {
    printf("Não ha usuarios cadastrados no sistema :/\n\n");
  }
}



void exportUsuarios(  struct User* listaUsuarios, int contadorUsuarios, FILE* userData  ) {
  


  printf("\n\n\n");
  printf("Exportando dados de usuarios para o arquivo ./data/userData.txt: ......");
  printf("\n\n");


  // ~ Abertura de um arquivo de sistema, para guardar as informações de todos os usuarios criados
  userData = fopen("./data/userData.txt", "w");
  if (userData == NULL) {  
    printf("Erro ao tentar abrir e gravar no arquivo userData.txt :| ");
    exit(1);  }



  // ~ Loop para printar no arquivo as informações de cada usuario 
  if (  contadorUsuarios > 0  ) {
    for (  int i = 0; i < contadorUsuarios; i++  ) {
      fprintf(userData, "Usuario [%d] \n", i);   
      fprintf(userData, "Nome:\t    %s\n", listaUsuarios[i].nome);
      fprintf(userData, "Codigo:\t  %d\n", listaUsuarios[i].codigo);
      fprintf(userData, "Social:\t  %s\n", listaUsuarios[i].social);
      fprintf(userData, "CPF:\t     %lld\n", listaUsuarios[i].cpf);
      fprintf(userData, "CEP:\t     %d\n", listaUsuarios[i].cep);
      fprintf(userData, "telefone:\t%lld\n", listaUsuarios[i].telefone);
      fprintf(userData, "\n\n");

      printf("\n\n\nDados de usuarios gravados!\n\n");
    }
  } 
  else {
    printf("\n\n\nNão havia dados de usuarios gravados no sistema!!!\n\n");
  }

  
  // ~ Essa função é importante para que, no final do codigo, o arquivo seja fechado, evitando erros e talz 
  fclose(userData);
}





// ~ Funções relacionadas ao Cadastro de Produtos





struct Product* novoProduto (  struct Product** listaProdutos, int* contadorProdutos  ) {

 
 int categoria;
  int codigoValido = 0, codigoRepetido = 0;

  
  // ~ É Criada uma variavel temporaria para que seja evitado de dar erro na realocação de memoria da variavel listaProdutos direto, primeiro verificando se essa variavel
  // ~ copia (temp) vai retornar algo diferente de NULL
  struct Product* temp = realloc(*listaProdutos, sizeof(struct Product) * (*contadorProdutos + 1));

  if (temp == NULL) {
    printf("Erro ao alocar memória para novo produto.\n");
    exit(1);
  }

  // ~ Atualização da variavel listaProdutos.
  *listaProdutos = temp;




  // ~ É criada uma varaivel struct ponteiro para (*listaProdutos)[*contadorProdutos] para facilitar a chamada desta variavel nas operações
  struct Product* produtoAtual = &(*listaProdutos)[*contadorProdutos];

  // ~ Por algum motivo, perguntado pro catgpt, quando eu faço esse scanf com esses valores esquisitos ai, é meio perigoso para a alocação de memoria
  // ~ de se misturar & e o ponteiro de struct, o porque sla.
  printf("Digite o Nome do Produto:\n => ");
  scanf(" %[^\n]%*c", produtoAtual->nome);          // ~ Quando se utiliza o -> é a mesma coisa do que chamar a variavel e pegar o valor de struct dela 
  printf("\n\n");                                   // ~ (*variavel).valorStruct   ==  variavel->valorStruct 

    
  // ~ Essa verificação no codigo serve para comparar se já existe algum produto com o codigo digitado cadastrado no sistema, caso
  // ~ já tenha sido criado algum produto, alem de ver se o codigo digitado é valido.
  printf("Digite o Codigo do Produto: de [1000] a [9999]:\n\n => ");
  while (!codigoValido) {
        scanf("%d", &produtoAtual->codigo);

        if (produtoAtual->codigo < 1000 || produtoAtual->codigo > 9999) {
            printf("\nCódigo inválido!\nDigite um valor entre [1000] e [9999]:\n => ");
    
        }

        codigoRepetido = 0;
        for (int i = 0; i < *contadorProdutos; i++) {
            if ((*listaProdutos)[i].codigo == produtoAtual->codigo) {
                codigoRepetido = 1;
                break;
            }
        }

        if (codigoRepetido) {
            printf("\nJá existe um produto com esse código! Digite outro:\n => ");
        } else {
            codigoValido = 1;
        }
    }


  // ~ uma atribuição direta ao valor id 
  produtoAtual->id = *contadorProdutos;




  // ~ Nesta parte do codigo, para ser mais prático, é perguntado ao usuario qual categoria ele quer atribuir ao 
  // ~ produto perguntanto para ele usando inteiros, e depois, no switch, atribuindo a string à category dependendo
  // ~ do resultado
  printf("\nInforme a Categoria do Produto: \n [1]: Alimentos \n [2]: Materiais \n [3]: Padaria\n\n => ");
  scanf("%d", &categoria);

  while((  categoria < 1  ) || (  categoria > 3  )) {
    printf("\n\nCategoria Invalida!\n Digite novamente [entre 1 à 3]:\n => ");
    scanf("%d", &categoria);
  }

  switch (categoria) {
    case 1:
      // ~ strcpy atribui à variavel listaProdutos[...] o valor da string direto, pois caso seja feito uma atribuição
      // ~ por igualdade ( listaProdutos[xxx] = xxx ) acaba dando um erro...
      strcpy(produtoAtual->category, "Alimentos");
      break;

    case 2:
      strcpy(produtoAtual->category, "Materiais");
      break;

    default:
      strcpy(produtoAtual->category, "Padaria");
      break;
  }

  printf("\n\n");




  
  // ~ O resto da atribuição de valores às variaveis
  printf("Digite o valor do produto na Compra:\n => ");
  scanf("%f", &produtoAtual->precoCompra);
  printf("\n\n");

  printf("Digite o valor do produto para Venda:\n => ");
  scanf("%f", &produtoAtual->precoVenda);
  printf("\n\n");

  printf("Digite a quantidade de Produtos:\n => ");
  scanf("%d", &produtoAtual->quant);
  printf("\n\n");

  while(  produtoAtual->quant < 0  ) {
    printf("\nQuantidade Invalida!\n Digite novamente:\n => ");
    scanf("%d", &produtoAtual->quant);
  }

  printf("Digite a quantidade de Estoque Minimo:\n => ");
  scanf("%d", &produtoAtual->quantMin);
  printf("\n\n");

  while((  produtoAtual->quantMin < 0 ) || (  produtoAtual->quantMin > produtoAtual->quant  )) {
    printf("\nQuantidade Invalida!\n Digite novamente [quant. min. tem que ser menor que a quantidade de estoque]:\n => ");
    scanf("%d", &produtoAtual->quantMin);
  }




  // ~ Calculo do Percentual de Lucro:  Valor da Compra / (Valor de Venda - Valor da Compra)
  float compra = produtoAtual->precoCompra;
  float vendas = produtoAtual->precoVenda;
  produtoAtual->lucro = ((vendas - compra) / compra) * 100;
  

    
  // ~ Uns printf dos valores atribuidos à este produto só.
  printf("Novo Produto Criado!\n\n");
  printf("Produto: [ %s ]\n", produtoAtual->nome);
  printf("Categoria:\t    %s\n", produtoAtual->category);
  printf("Valor Compra:\t %.2f\n", produtoAtual->precoCompra);
  printf("Valor Venda:\t  %.2f\n", produtoAtual->precoVenda);
  printf("Quantidade:\t   %d\n", produtoAtual->quant);
  printf("Estoque Min:\t  %d\n", produtoAtual->quantMin);
  printf("Lucro:\t        %.2f %% \n", produtoAtual->lucro);

  (*contadorProdutos)++;

    // ~ O retorno é nescessário pois atribui, no main.c, à variavel chamada *listaProdutos os valores que recebemos aqui.
    return *listaProdutos;
}



void mostrarTodosProdutos(  struct Product* listaProdutos, int contadorProdutos ) {

  printf("\n\n\nMostrando todos os produtos Cadastrados...\n\n");

  if (  contadorProdutos > 0  ) {
    for (  int i = 0; i < contadorProdutos; i++  ) {
      printf("Produto [%d] \n", i);
      printf("Nome:\t    %s\n", listaProdutos[i].nome);
      printf("Codigo:\t  %d\n", listaProdutos[i].codigo);
      printf("Categoria:\t  %s\n", listaProdutos[i].category);
      printf("Preço de Compra:\t     %.2f\n", listaProdutos[i].precoCompra);
      printf("Preço de Vendas:\t     %.2f\n", listaProdutos[i].precoVenda);
      printf("Lucro:\t               %.2f\n", listaProdutos[i].lucro);
      printf("Quantidade:\t %d\n", listaProdutos[i].quant);
      printf("Quant Min.:\t %d\n", listaProdutos[i].quantMin);
      printf("\n\n");
    }
  }
  else {
    printf("Não há produtos cadastrados no sistema!!!\n\n");
  }
}



void exportProdutos(  struct Product* listaProdutos, int contadorProdutos, FILE* productData  ) {
  


  printf("\n\n\n");
  printf("Exportando dados de Produtos para o arquivo ./data/userData.txt: ......");
  printf("\n\n");


  // ~ Abertura de um arquivo de sistema, para guardar as informações de todos os Produtos criados
  productData = fopen("./data/productData.txt", "w");
  if (productData == NULL) {  
    printf("Erro ao tentar abrir e gravar no arquivo productData.txt :| ");
    exit(1);  }



  if (  contadorProdutos > 0  ) {
    // ~ Loop para printar no arquivo as informações de cada usuario 
    for (  int i = 0; i < contadorProdutos; i++  ) {
      fprintf(productData, "\n\n"); 
  
      fprintf(productData, "Produto: [ %d ]\n", i);
      fprintf(productData, "Nome:\t         %s\n", listaProdutos[i].nome);
      fprintf(productData, "Categoria:\t    %s\n", listaProdutos[i].category);
      fprintf(productData, "Valor Compra:\t %.2f\n", listaProdutos[i].precoCompra);
      fprintf(productData, "Valor Venda:\t  %.2f\n", listaProdutos[i].precoVenda);
      fprintf(productData, "Quantidade:\t   %d\n", listaProdutos[i].quant);
      fprintf(productData, "Estoque Min:\t  %d\n", listaProdutos[i].quantMin);
      fprintf(productData, "Lucro:\t        %f % \n", listaProdutos[i].lucro);
    }

    printf("\n\n\nDados dos produtos gravados!\n");
  }
  else {
    printf("\n\n\nNão há produtos cadastrados no sistema!!!\n\n");
  }

  
  // ~ Essa função é importante para que, no final do codigo, o arquivo seja fechado, evitando erros e talz 
  fclose(productData);
}


// --------- Início de Pagamentos.c ---------

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

// --------- Início de Menus.c ---------

#include <stdio.h>

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

// --------- Início de main.c ---------

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
          menuVendas(  &listaPagamentos, carrinhoCompras, &listaProdutos, &opcaoSubMenu, &contadorPagamentos, contadorProdutos, &valorCaixa  );
        }
        

        menuPrincipal(  &opcaoMenu  );
        break;
     



      case 3:
        // ~ Funções localizada em Menus.c
        menuAbertCaixa(  &opcaoSubMenu, &valorCaixa, &isOpenCaixa  );
        menuPrincipal(  &opcaoMenu  );
        break;

      case 4:
        menuFechaCaixa(  listaPagamentos, contadorPagamentos, valorCaixa  );
        menuPrincipal(  &opcaoMenu  );
        break;

      case 5:
        menuRelatorios(  listaPagamentos, contadorPagamentos  );
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
  free(carrinhoCompras);
  return 0;
}


