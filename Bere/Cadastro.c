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


  // ~ Verificação se o codigo do usuario é valido (ou seja, se é entre 1000 e 9999 ou se não é repetido)
  while (!codigoValido) {
    printf("Digite o codigo do usuario [1000 a 9999]:\n => ");
    scanf("%d", &((*listaUsuarios)[*contadorUsuarios].codigo));

    if ((*listaUsuarios)[*contadorUsuarios].codigo < 1000 || 
        (*listaUsuarios)[*contadorUsuarios].codigo > 9999) {
        printf("\nCódigo inválido! Digite um valor entre [1000] e [9999]\n");
        continue;
    }

    codigoRepetido = 0;
    for (int i = 0; i < *contadorUsuarios; i++) {
        if ((*listaUsuarios)[i].codigo == (*listaUsuarios)[*contadorUsuarios].codigo) {
            codigoRepetido = 1;
            break;
        }
    }

    if (codigoRepetido) {
        printf("\nJá existe um usuário com esse código! Digite outro:\n");
    } else {
        codigoValido = 1;
    }
  } 

  getchar();
  printf("Digite o nome social: \n => ");
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
