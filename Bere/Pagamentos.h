#ifndef PAGAMENTOS_H
#define PAGAMENTOS_H

// Declaração antecipada para evitar erro de tipo incompleto
struct Produto;
struct Cliente;
struct Usuario;

#include "Produtos.h"
#include "Clientes.h"
#include "Usuario.h"
/*
 * Arquivo responsável pela declaração das Structs e funções relacionadas a:
 * -> Vendas
 * -> Carrinho de Compras
 * -> Caixa (Abertura, Fechamento, Sangria)
 * -> Pagamentos
 */


// ~ Struct dos itens no carrinho
struct ItemCarrinho {
    struct Produto* produto;
    int quantidade;
    float precoUnitario;
    float subtotal;
};


// ~ Struct do carrinho completo
struct Carrinho {
    struct ItemCarrinho* itens;
    int totalItens;

    float totalAlimentos;
    float totalMateriais;
    float totalPadaria;
    float totalGeral;

    struct Cliente cliente; // Cliente vinculado na venda
    int dia, mes, ano;
};


// ~ Struct dos pagamentos
struct Pagamento {
    int id;
    float valor;
    char tipo[30]; // Dinheiro, Cartao, Misto Dinheiro, Misto Cartao
    struct Carrinho carrinho;

    char status[10]; // Aberto ou Pago
};


// ~ Funções do Carrinho
void iniciarCarrinho(struct Carrinho** carrinho);
void adicionarItemNoCarrinho(struct Carrinho* carrinho, struct Produto* produto, int quantidade);
void limparCarrinho(struct Carrinho* carrinho);


// ~ Funções de Pagamento
struct Pagamento* novoPagamento(struct Pagamento* listaPagamentos, struct Carrinho carrinho, int* contadorPagamentos, int tipoPagamento, float valorRecebido);
void listarPagamentosAbertos(struct Pagamento* listaPagamentos, int contadorPagamentos);


// ~ Operações de Caixa
void abrirCaixa(float* valorCaixa, char* statusCaixa, struct Usuario* usuarioLogado, struct Usuario* listaUsuarios, int totalUsuarios);
void sangriaCaixa(float* valorCaixa, struct Usuario* usuarioLogado, struct Usuario* listaUsuarios, int totalUsuarios, struct Pagamento* listaPagamentos, int contadorPagamentos);
void fecharCaixa(float valorCaixa, struct Pagamento* listaPagamentos, int contadorPagamentos, struct Usuario* usuarioLogado, struct Usuario* listaUsuarios, int totalUsuarios);


// ~ Exportação
void exportarPagamentos(struct Pagamento* listaPagamentos, int contadorPagamentos);


struct Pagamento* realizarVenda(struct Produto* listaProdutos, int* totalProdutos,
    struct Cliente* listaClientes, int totalClientes, struct Usuario* usuarioAtual,
    struct Pagamento* listaPagamentos, int* totalPagamentos, struct Carrinho* carrinho);


void pagarVendaAberta(struct Pagamento* listaPagamentos, int contadorPagamentos);




// ~ Os coiso de relatorio aq
void listarClientesOrdemAlfabetica(struct Cliente* listaClientes, int totalClientes);
void listarClientesQueCompraram(struct Pagamento* listaPagamentos, int totalPagamentos);
void listarProdutosOrdenados(struct Produto* listaProdutos, int totalProdutos);
void produtosMaisVendidos(struct Pagamento* listaPagamentos, int totalPagamentos);
void listarVendasPorPeriodo(struct Pagamento* listaPagamentos, int totalPagamentos);
void faturamentoPorTipoPagamento(struct Pagamento* listaPagamentos, int totalPagamentos);

// ~ meuDeus. 


#endif
