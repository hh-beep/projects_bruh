#ifndef CADASTRO_H
#define CADASTRO_H

/*
 *  Declarações de Criação de Usuarios
 *
 *
 *  Aqui neste arquivo conterá toda as informações/declarações de funções criadas no 
 *  arquivo Cadastro.c, além de ter a declaração da struct User e struct Product, usada para criar 
 *  usuarios e produtos no sistema.
 *
 *
 */
struct User {
  int id;
  int codigo;
  char nome[100];
  char social[100];
  long long cpf;
  int cep;
  long long telefone;
};



struct User* novoUsuario(  struct User** listaUsuarios, int* contadorUsuarios );

void mostrarTodosUsuarios(  struct User* listaUsuarios, int contadorUsuarios  );

void exportUsuarios(  struct User* listaUsuarios, int contadorUsuarios, FILE* userData  );





//  Declarações de funções de Criação de Produto



struct Product {
  int id;
  int codigo;
  char nome[100];
  char category[100];
  float precoCompra;
  float precoVenda;
  float lucro;
  int quant;
  int quantMin;
};



struct Product* novoProduto (  struct Product** listaProdutos, int* contadorProdutos  );

void mostrarTodosProdutos(  struct Product* listaUsuarios, int contadorProdutos  );

void exportProdutos(  struct Product* listaProdutos, int contadorProdutos, FILE* productData  );

#endif
