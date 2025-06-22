#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Produtos.h"
#include "Clientes.h"
#include "Usuario.h"
#include "Pagamentos.h"



// ~ Função para cadastrar um novo produto
struct Produto* novoProduto(struct Produto** listaProdutos, int* contadorProdutos) {
    int codigoValido = 0, codigoRepetido = 0;
    int categoriaTemp;

    *listaProdutos = realloc(*listaProdutos, sizeof(struct Produto) * (*contadorProdutos + 1));
    if (*listaProdutos == NULL) {
        printf("Erro ao alocar memória para produto!\n");
        exit(1);
    }

    struct Produto* produtoAtual = &(*listaProdutos)[*contadorProdutos];
    produtoAtual->id = *contadorProdutos;

    // ~ Nome
    printf("Digite o nome do produto:\n => ");
    scanf(" %[^\n]%*c", produtoAtual->nome);

    // ~ Código
    while (!codigoValido) {
        printf("Digite o código do produto [1000 a 9999]:\n => ");
        scanf("%d", &produtoAtual->codigo);

        if (produtoAtual->codigo < 1000 || produtoAtual->codigo > 9999) {
            printf("Código inválido! Digite um valor entre 1000 e 9999.\n");
            continue;
        }

        codigoRepetido = 0;
        for (int i = 0; i < *contadorProdutos; i++) {
            if ((*listaProdutos)[i].codigo == produtoAtual->codigo) {
                codigoRepetido = 1;
                break;
            }
        }

        if (codigoRepetido) {
            printf("Já existe um produto com esse código! Digite outro.\n");
        } else {
            codigoValido = 1;
        }
    }

    // ~ Categoria
    printf("Escolha a categoria:\n [1] Alimento\n [2] Material\n [3] Padaria\n => ");
    scanf("%d", &categoriaTemp);

    while (categoriaTemp < 1 || categoriaTemp > 3) {
        printf("Categoria inválida! Digite novamente:\n => ");
        scanf("%d", &categoriaTemp);
    }

    switch (categoriaTemp) {
        case 1:
            strcpy(produtoAtual->categoria, "Alimento");
            break;
        case 2:
            strcpy(produtoAtual->categoria, "Material");
            break;
        default:
            strcpy(produtoAtual->categoria, "Padaria");
            break;
    }

    // ~ Preço de compra
    printf("Digite o preço de compra do produto:\n => ");
    scanf("%f", &produtoAtual->precoCompra);

    // ~ Margem de lucro
    printf("Digite a margem de lucro (em %%):\n => ");
    scanf("%f", &produtoAtual->margemLucro);

    // ~ Preço de venda calculado automaticamente
    produtoAtual->precoVenda = produtoAtual->precoCompra + (produtoAtual->precoCompra * produtoAtual->margemLucro / 100);

    // ~ Quantidade em estoque
    printf("Digite a quantidade de produtos em estoque:\n => ");
    scanf("%d", &produtoAtual->quantidade);

    // ~ Estoque mínimo
    printf("Digite a quantidade de estoque mínimo:\n => ");
    scanf("%d", &produtoAtual->estoqueMinimo);

    while (produtoAtual->estoqueMinimo < 0 || produtoAtual->estoqueMinimo > produtoAtual->quantidade) {
        printf("Quantidade de estoque mínimo inválida!\nDigite novamente:\n => ");
        scanf("%d", &produtoAtual->estoqueMinimo);
    }

    // ~ Confirmação
    printf("\nProduto cadastrado com sucesso!\n");
    printf("Produto: %s | Categoria: %s | Código: %d\n", produtoAtual->nome, produtoAtual->categoria, produtoAtual->codigo);
    printf("Compra: R$ %.2f | Venda: R$ %.2f | Margem: %.2f%%\n", 
           produtoAtual->precoCompra, produtoAtual->precoVenda, produtoAtual->margemLucro);
    printf("Quantidade: %d | Estoque Mínimo: %d\n", produtoAtual->quantidade, produtoAtual->estoqueMinimo);

    (*contadorProdutos)++;

    return *listaProdutos;
}


// ~ Mostrar todos os produtos cadastrados
void mostrarTodosProdutos(struct Produto* listaProdutos, int contadorProdutos) {
    if (contadorProdutos <= 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n--- Lista de Produtos ---\n");
    for (int i = 0; i < contadorProdutos; i++) {
        printf("Produto [%d]: %s | Código: %d | Categoria: %s\n", 
               i, listaProdutos[i].nome, listaProdutos[i].codigo, listaProdutos[i].categoria);
        printf("Compra: R$ %.2f | Venda: R$ %.2f | Margem: %.2f%%\n",
               listaProdutos[i].precoCompra, listaProdutos[i].precoVenda, listaProdutos[i].margemLucro);
        printf("Quantidade: %d | Estoque Mínimo: %d\n\n", 
               listaProdutos[i].quantidade, listaProdutos[i].estoqueMinimo);
    }
}


// ~ Exportar produtos para arquivo
void exportarProdutos(struct Produto* listaProdutos, int contadorProdutos) {
    FILE* arq = fopen("./data/produtosData.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos!\n");
        return;
    }

    for (int i = 0; i < contadorProdutos; i++) {
        fprintf(arq, "Produto [%d]:\n", i);
        fprintf(arq, "Nome: %s\n", listaProdutos[i].nome);
        fprintf(arq, "Categoria: %s\n", listaProdutos[i].categoria);
        fprintf(arq, "Codigo: %d\n", listaProdutos[i].codigo);
        fprintf(arq, "PrecoCompra: %.2f\n", listaProdutos[i].precoCompra);
        fprintf(arq, "MargemLucro: %.2f%%\n", listaProdutos[i].margemLucro);
        fprintf(arq, "PrecoVenda: %.2f\n", listaProdutos[i].precoVenda);
        fprintf(arq, "Quantidade: %d\n", listaProdutos[i].quantidade);
        fprintf(arq, "EstoqueMinimo: %d\n\n", listaProdutos[i].estoqueMinimo);
    }

    fclose(arq);
    printf("\nProdutos exportados para ./data/produtosData.txt\n");
}
