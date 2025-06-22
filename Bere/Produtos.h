#ifndef PRODUTOS_H
#define PRODUTOS_H



#include "Menus.h"
#include "Usuario.h"
#include "Clientes.h"
#include "Pagamentos.h"


/*
 * Arquivo responsável pela declaração da Struct e funções relacionadas aos PRODUTOS.
 * Aqui estão os produtos da mercearia da Dona Berê.
 */


// ~ Struct de Produto
struct Produto {
    int id;
    int codigo;
    char nome[100];
    char categoria[100];  // Alimento | Material | Padaria
    float precoCompra;
    float precoVenda;
    float margemLucro;    // percentual
    int quantidade;
    int estoqueMinimo;
};


// ~ Funções

// Cadastrar um novo produto
struct Produto* novoProduto(struct Produto** listaProdutos, int* contadorProdutos);

// Mostrar todos os produtos
void mostrarTodosProdutos(struct Produto* listaProdutos, int contadorProdutos);

// Exportar produtos para arquivo
void exportarProdutos(struct Produto* listaProdutos, int contadorProdutos);

#endif
