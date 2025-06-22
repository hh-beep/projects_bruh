#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Produtos.h"
#include "Clientes.h"
#include "Usuario.h"
#include "Pagamentos.h"




void menuPrincipal(int* opcaoMenu) {
    printf("\n==== MENU PRINCIPAL ====\n");
    printf("1. Cadastros\n");
    printf("2. Vendas\n");
    printf("3. Abertura de Caixa\n");
    printf("4. Fechamento de Caixa\n");
    printf("5. Relatorios\n");
    printf("6. Sair\n");
    printf("Escolha uma opcao:\n => ");
    scanf("%d", opcaoMenu);
}


void menuCadastros(int* opcaoSubMenu) {
    printf("\n==== MENU CADASTROS ====\n");
    printf("1. Cadastro de Usuarios (do sistema)\n");
    printf("2. Cadastro de Clientes\n");
    printf("3. Cadastro de Produtos\n");
    printf("4. Voltar ao Menu Principal\n");
    printf("Escolha uma opcao:\n => ");
    scanf("%d", opcaoSubMenu);
}


void menuVendas(int* opcaoSubMenu) {
    printf("\n==== MENU VENDAS ====\n");
    printf("1. Nova Venda\n");
    printf("2. Retirada de Caixa (Sangria)\n");
    printf("3. Pagamento de Vendas em Aberto\n");
    printf("4. Voltar ao Menu Principal\n");
    printf("Escolha uma opcao:\n => ");
    scanf("%d", opcaoSubMenu);
}


void menuCaixa(int* opcaoSubMenu) {
    printf("\n==== MENU CAIXA ====\n");
    printf("1. Abrir Caixa\n");
    printf("2. Fechar Caixa\n");
    printf("3. Voltar ao Menu Principal\n");
    printf("Escolha uma opcao:\n => ");
    scanf("%d", opcaoSubMenu);
}


void menuRelatorios(int* opcaoSubMenu) {
    printf("\n==== MENU RELATORIOS ====\n");
    printf("1. Listagem de Clientes\n");
    printf("2. Listagem de Produtos\n");
    printf("3. Listagem de Produtos com Estoque Mínimo ou Zerado\n");
    printf("4. Listagem de Vendas\n");
    printf("5. Faturamento Consolidado\n");
    printf("6. Voltar ao Menu Principal\n");
    printf("Escolha uma opcao:\n => ");
    scanf("%d", opcaoSubMenu);
}
