#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Produtos.h"
#include "Clientes.h"
#include "Usuario.h"
#include "Pagamentos.h"


int main() {
    //setlocale(LC_ALL, "Portuguese");

    // ~ Variáveis de controle geral
    float valorCaixa = 0;
    char statusCaixa = 'N';

    int opcaoMenu, opcaoSubMenu = 0;

    // ~ Usuários do sistema
    struct Usuario* listaUsuarios = NULL;
    int totalUsuarios = 0;
    struct Usuario* usuarioLogado = NULL;


    // ~ Cria usuário admin padrão se nenhum estiver carregado
    if (totalUsuarios == 0) {
        listaUsuarios = malloc(sizeof(struct Usuario));
        listaUsuarios[0].id = 0;
        strcpy(listaUsuarios[0].login, "admin");
        strcpy(listaUsuarios[0].senha, "admin123");
        listaUsuarios[0].tipo = 1;
        totalUsuarios = 1;

        printf("\n>>> Usuário admin criado automaticamente (login: admin | senha: admin123)\n");
    }


    // ~ Clientes
    struct Cliente* listaClientes = NULL;
    int totalClientes = 0;

    // ~ Produtos
    struct Produto* listaProdutos = NULL;
    int totalProdutos = 0;

    // ~ Pagamentos
    struct Pagamento* listaPagamentos = NULL;
    int totalPagamentos = 0;

    // ~ Carrinho
    struct Carrinho* carrinho = NULL;
    iniciarCarrinho(&carrinho);


    // ~ LOGIN INICIAL
    do {
        printf("\n==== LOGIN NO SISTEMA ====\n");
        usuarioLogado = loginSistema(listaUsuarios, totalUsuarios);
    } while (usuarioLogado == NULL);



    // ~ MENU PRINCIPAL
    do {
        menuPrincipal(&opcaoMenu);

        switch (opcaoMenu) {
            case 1:
                do {
                    menuCadastros(&opcaoSubMenu);

                    switch (opcaoSubMenu) {
                        case 1:
                            novoUsuarioSistema(&listaUsuarios, &totalUsuarios);
                            break;
                        case 2:
                            novoCliente(&listaClientes, &totalClientes);
                            break;
                        case 3:
                            novoProduto(&listaProdutos, &totalProdutos);
                            break;
                    }
                } while (opcaoSubMenu != 4);
                break;


            case 2:
                do {
                    menuVendas(&opcaoSubMenu);

                    switch (opcaoSubMenu) {
                        case 1:
                            listaPagamentos = realizarVenda(
                                listaProdutos, &totalProdutos, listaClientes, 
                                totalClientes, usuarioLogado, listaPagamentos, 
                                &totalPagamentos, carrinho);
                            break;

                        case 2:
                            sangriaCaixa(&valorCaixa, usuarioLogado, listaUsuarios, totalUsuarios, listaPagamentos, totalPagamentos);
                            break;

                        case 3:
                            listarPagamentosAbertos(listaPagamentos, totalPagamentos);
                            pagarVendaAberta(listaPagamentos, totalPagamentos);
                            break;
                    }

                } while (opcaoSubMenu != 4);
                break;


            case 3:
                abrirCaixa(&valorCaixa, &statusCaixa, usuarioLogado, listaUsuarios, totalUsuarios);
                break;


            case 4:
                fecharCaixa(valorCaixa, listaPagamentos, totalPagamentos, usuarioLogado, listaUsuarios, totalUsuarios);
                break;


            case 5:
                do {
                    menuRelatorios(&opcaoSubMenu);

                    switch (opcaoSubMenu) {
                        case 1:
                            listarClientesOrdemAlfabetica(listaClientes, totalClientes);
                            break;
                        case 2:
                            listarClientesQueCompraram(listaPagamentos, totalPagamentos);
                            break;
                        case 3:
                            listarProdutosOrdenados(listaProdutos, totalProdutos);
                            break;
                        case 4:
                            produtosMaisVendidos(listaPagamentos, totalPagamentos);
                            break;
                        case 5:
                            listarVendasPorPeriodo(listaPagamentos, totalPagamentos);
                            break;
                        case 6:
                            faturamentoPorTipoPagamento(listaPagamentos, totalPagamentos);
                            break;
                    }

                } while (opcaoSubMenu != 7);
                break;


            case 6:
                printf("Saindo do sistema...\n");

                // Exportar os dados
                if (totalUsuarios > 0) exportarUsuariosSistema(listaUsuarios, totalUsuarios);
                if (totalClientes > 0) exportarClientes(listaClientes, totalClientes);
                if (totalProdutos > 0) exportarProdutos(listaProdutos, totalProdutos);
                if (totalPagamentos > 0) exportarPagamentos(listaPagamentos, totalPagamentos);

                break;

            default:
                printf("Opção inválida.\n");
                break;
        }

    } while (opcaoMenu != 6);


    // ~ Liberação de memória
    free(listaUsuarios);
    free(listaClientes);
    free(listaProdutos);
    free(listaPagamentos);
    limparCarrinho(carrinho);
    free(carrinho);

    return 0;
}