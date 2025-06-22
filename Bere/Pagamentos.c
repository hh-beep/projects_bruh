#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Produtos.h"
#include "Clientes.h"
#include "Usuario.h"
#include "Pagamentos.h"





// ================== Carrinho ==================

void iniciarCarrinho(struct Carrinho** carrinho) {
    *carrinho = malloc(sizeof(struct Carrinho));
    if (*carrinho == NULL) {
        printf("Erro ao alocar memória pro carrinho!\n");
        exit(1);
    }
    (*carrinho)->itens = NULL;
    (*carrinho)->totalItens = 0;
    (*carrinho)->totalAlimentos = 0;
    (*carrinho)->totalMateriais = 0;
    (*carrinho)->totalPadaria = 0;
    (*carrinho)->totalGeral = 0;
}

void adicionarItemNoCarrinho(struct Carrinho* carrinho, struct Produto* produto, int quantidade) {
    if (produto->quantidade < quantidade) {
        printf("Estoque insuficiente! Estoque atual: %d\n", produto->quantidade);
        return;
    }

    carrinho->itens = realloc(carrinho->itens, sizeof(struct ItemCarrinho) * (carrinho->totalItens + 1));
    if (carrinho->itens == NULL) {
        printf("Erro ao alocar memória para o item no carrinho!\n");
        exit(1);
    }

    float subtotal = produto->precoVenda * quantidade;

    carrinho->itens[carrinho->totalItens].produto = produto;
    carrinho->itens[carrinho->totalItens].quantidade = quantidade;
    carrinho->itens[carrinho->totalItens].precoUnitario = produto->precoVenda;
    carrinho->itens[carrinho->totalItens].subtotal = subtotal;
    carrinho->totalItens++;

    produto->quantidade -= quantidade;

    if (strcmp(produto->categoria, "Alimento") == 0)
        carrinho->totalAlimentos += subtotal;
    else if (strcmp(produto->categoria, "Material") == 0)
        carrinho->totalMateriais += subtotal;
    else if (strcmp(produto->categoria, "Padaria") == 0)
        carrinho->totalPadaria += subtotal;

    carrinho->totalGeral += subtotal;
}

void limparCarrinho(struct Carrinho* carrinho) {
    free(carrinho->itens);
    carrinho->itens = NULL;
    carrinho->totalItens = 0;
    carrinho->totalAlimentos = 0;
    carrinho->totalMateriais = 0;
    carrinho->totalPadaria = 0;
    carrinho->totalGeral = 0;
}



// ================== Pagamentos ==================

struct Pagamento* novoPagamento(struct Pagamento* listaPagamentos, struct Carrinho carrinho, int* contadorPagamentos, int tipoPagamento, float valorRecebido) {
    listaPagamentos = realloc(listaPagamentos, sizeof(struct Pagamento) * (*contadorPagamentos + 1));
    if (listaPagamentos == NULL) {
        printf("Erro ao alocar memória para pagamentos!\n");
        exit(1);
    }

    struct Pagamento* pagamentoAtual = &listaPagamentos[*contadorPagamentos];

    pagamentoAtual->id = *contadorPagamentos;
    pagamentoAtual->carrinho = carrinho;
    pagamentoAtual->valor = carrinho.totalGeral;
    strcpy(pagamentoAtual->status, "Pago");

    switch (tipoPagamento) {
        case 1:
            strcpy(pagamentoAtual->tipo, "Dinheiro");
            break;
        case 2:
            strcpy(pagamentoAtual->tipo, "Cartao");
            break;
        case 3:
            strcpy(pagamentoAtual->tipo, "Misto Dinheiro/Cartao");
            break;
        default:
            strcpy(pagamentoAtual->tipo, "Indefinido");
            break;
    }

    (*contadorPagamentos)++;

    printf("\nPagamento registrado com sucesso!\n");

    return listaPagamentos;
}

void listarPagamentosAbertos(struct Pagamento* listaPagamentos, int contadorPagamentos) {
    printf("\n--- Vendas em Aberto ---\n");
    int encontrou = 0;
    for (int i = 0; i < contadorPagamentos; i++) {
        if (strcmp(listaPagamentos[i].status, "Aberto") == 0) {
            printf("Venda [%d] | Cliente: %s | Valor: %.2f\n",
                   listaPagamentos[i].id, listaPagamentos[i].carrinho.cliente.nome, listaPagamentos[i].valor);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Não há vendas em aberto!\n");
    }
    printf("\n\n\n\n\n");
}



// ================== Caixa ==================

void abrirCaixa(float* valorCaixa, char* statusCaixa, struct Usuario* usuarioLogado, struct Usuario* listaUsuarios, int totalUsuarios) {
    if (!verificaAdmin(usuarioLogado, listaUsuarios, totalUsuarios)) return;

    do {
        printf("Digite o valor de abertura do caixa (>= 0):\n => ");
        scanf("%f", valorCaixa);
    } while (*valorCaixa < 0);

    *statusCaixa = 'S';

    printf("Caixa aberto com R$ %.2f\n", *valorCaixa);
}

void sangriaCaixa(float* valorCaixa, struct Usuario* usuarioLogado, struct Usuario* listaUsuarios, int totalUsuarios, struct Pagamento* listaPagamentos, int contadorPagamentos) {
    if (!verificaAdmin(usuarioLogado, listaUsuarios, totalUsuarios)) return;

    float totalDinheiro = 0;
    for (int i = 0; i < contadorPagamentos; i++) {
        if (strcmp(listaPagamentos[i].tipo, "Dinheiro") == 0 || strstr(listaPagamentos[i].tipo, "Misto") != NULL) {
            totalDinheiro += listaPagamentos[i].valor;
        }
    }

    printf("Valor disponível em dinheiro: R$ %.2f\n", totalDinheiro);
    printf("Quanto deseja retirar? (Minimo deixar R$50,00)\n => ");
    float retirada;
    scanf("%f", &retirada);

    if (retirada >= (totalDinheiro - 50)) {
        printf("Erro! É necessário deixar pelo menos R$50,00 no caixa.\n");
        return;
    }

    *valorCaixa -= retirada;
    printf("Sangria realizada: R$ %.2f | Caixa atual: R$ %.2f\n", retirada, *valorCaixa);
}

void fecharCaixa(float valorCaixa, struct Pagamento* listaPagamentos, int contadorPagamentos, struct Usuario* usuarioLogado, struct Usuario* listaUsuarios, int totalUsuarios) {
    if (!verificaAdmin(usuarioLogado, listaUsuarios, totalUsuarios)) return;

    int qtdVendas = contadorPagamentos;
    float faturamento = 0, dinheiro = 0, cartao = 0, misto = 0;

    for (int i = 0; i < contadorPagamentos; i++) {
        faturamento += listaPagamentos[i].valor;
        if (strcmp(listaPagamentos[i].tipo, "Dinheiro") == 0) dinheiro += listaPagamentos[i].valor;
        else if (strcmp(listaPagamentos[i].tipo, "Cartao") == 0) cartao += listaPagamentos[i].valor;
        else if (strstr(listaPagamentos[i].tipo, "Misto") != NULL) misto += listaPagamentos[i].valor;
    }

    float ajuste = faturamento - dinheiro - cartao - misto - valorCaixa;

    printf("\n===== Fechamento de Caixa =====\n");
    printf("Vendas: %d | Faturamento: R$ %.2f\n", qtdVendas, faturamento);
    printf("Dinheiro: R$ %.2f | Cartão: R$ %.2f | Misto: R$ %.2f\n", dinheiro, cartao, misto);
    printf("Abertura de caixa: R$ %.2f\n", valorCaixa);

    if (ajuste != 0) {
        printf("⚠️  Atenção: Divergência de R$ %.2f (%s)\n",
               ajuste, ajuste > 0 ? "SOBRA" : "FALTA");
    } else {
        printf("Caixa fechado corretamente. Sem divergências!\n");
    }
}



// ================== Exportação ==================

void exportarPagamentos(struct Pagamento* listaPagamentos, int contadorPagamentos) {
    FILE* arq = fopen("./data/pagamentosData.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo de pagamentos!\n");
        return;
    }

    for (int i = 0; i < contadorPagamentos; i++) {
        fprintf(arq, "Pagamento [%d]:\n", listaPagamentos[i].id);
        fprintf(arq, "Cliente: %s\n", listaPagamentos[i].carrinho.cliente.nome);
        fprintf(arq, "Valor: %.2f\n", listaPagamentos[i].valor);
        fprintf(arq, "Tipo: %s\n", listaPagamentos[i].tipo);
        fprintf(arq, "Status: %s\n\n", listaPagamentos[i].status);
    }

    fclose(arq);
    printf("\nPagamentos exportados para ./data/pagamentosData.txt\n");
}




struct Pagamento* realizarVenda(struct Produto* listaProdutos, int* totalProdutos,
    struct Cliente* listaClientes, int totalClientes, struct Usuario* usuarioAtual,
    struct Pagamento* listaPagamentos, int* totalPagamentos, struct Carrinho* carrinho) 
{

    // ~ Limpa o carrinho para nova venda
    limparCarrinho(carrinho);

    // ~ Escolhe cliente da venda
    printf("\n--- Clientes Cadastrados ---\n");
    mostrarTodosClientes(listaClientes, totalClientes);
    int idCliente;
    printf("Digite o ID do cliente para a venda:\n => ");
    scanf("%d", &idCliente);

    if (idCliente < 0 || idCliente >= totalClientes) {
        printf("Cliente inválido!\n");
        return listaPagamentos;
    }

    carrinho->cliente = listaClientes[idCliente];

    // ~ Adiciona produtos ao carrinho
    int adicionarMais = 1;
    while (adicionarMais) {
        printf("\n--- Produtos Cadastrados ---\n");
        mostrarTodosProdutos(listaProdutos, *totalProdutos);

        int idProduto, quantidade;
        printf("Digite o ID do produto que deseja adicionar:\n => ");
        scanf("%d", &idProduto);

        if (idProduto < 0 || idProduto >= *totalProdutos) {
            printf("Produto inválido!\n");
            continue;
        }

        printf("Digite a quantidade:\n => ");
        scanf("%d", &quantidade);

        adicionarItemNoCarrinho(carrinho, &listaProdutos[idProduto], quantidade);

        printf("Total atual do carrinho: R$ %.2f\n", carrinho->totalGeral);

        printf("Deseja adicionar mais um item? [1] Sim | [0] Não:\n => ");
        scanf("%d", &adicionarMais);
    }

    // ~ Data da venda
    printf("Informe a data da venda (DD MM AAAA):\n => ");
    scanf("%d %d %d", &carrinho->dia, &carrinho->mes, &carrinho->ano);

    // ~ Desconto
    float descontoPercentual, descontoValor = 0;
    printf("Deseja aplicar desconto? (0 = não, ou informe %%):\n => ");
    scanf("%f", &descontoPercentual);

    if (descontoPercentual > 0 && descontoPercentual <= 100) {
        descontoValor = carrinho->totalGeral * (descontoPercentual / 100.0f);
    }

    float totalFinal = carrinho->totalGeral - descontoValor;
    printf("\nTotal com desconto: R$ %.2f\n", totalFinal);

    // ~ Pagamento
    int tipoPagamento;
    float valorRecebido, restante = 0;
    char pagamentoOk = 0;

    do {
        printf("\nFormas de pagamento:\n");
        printf("[1] Dinheiro\n[2] Cartão\n[3] Voltar ao Menu\n => ");
        scanf("%d", &tipoPagamento);

        if (tipoPagamento == 3) return listaPagamentos;

        printf("Informe o valor recebido:\n => R$ ");
        scanf("%f", &valorRecebido);

        if (tipoPagamento == 1 && valorRecebido < totalFinal) {
            printf("Valor insuficiente em dinheiro. Deseja pagar o restante no cartão? [1] Sim | [0] Não\n => ");
            int complemento;
            scanf("%d", &complemento);
            if (complemento == 1) {
                restante = totalFinal - valorRecebido;
                printf("Pagamento misto: R$ %.2f em dinheiro + R$ %.2f em cartão.\n", valorRecebido, restante);
                tipoPagamento = 3;
                pagamentoOk = 1;
            }
        } else if (tipoPagamento == 2 && valorRecebido < totalFinal) {
            printf("Pagamento no cartão não cobre o total. Pagar restante em dinheiro? [1] Sim | [0] Não\n => ");
            int complemento;
            scanf("%d", &complemento);
            if (complemento == 1) {
                restante = totalFinal - valorRecebido;
                printf("Pagamento misto: R$ %.2f em cartão + R$ %.2f em dinheiro.\n", valorRecebido, restante);
                tipoPagamento = 4;
                pagamentoOk = 1;
            }
        } else if (tipoPagamento == 1) {
            float troco = valorRecebido - totalFinal;
            printf("Troco a devolver: R$ %.2f\n", troco);
            pagamentoOk = 1;
        } else if (tipoPagamento == 2) {
            int statusCartao;
            printf("Pagamento passou na maquininha? [1] Sim | [0] Não:\n => ");
            scanf("%d", &statusCartao);
            if (statusCartao == 1) pagamentoOk = 1;
        } else {
            pagamentoOk = 1;
        }
    } while (!pagamentoOk);

    // ~ Registra o pagamento com status "Pago"
    listaPagamentos = novoPagamento(listaPagamentos, *carrinho, totalPagamentos, tipoPagamento, totalFinal);

    printf("Venda registrada com sucesso!\n");
    return listaPagamentos;
}





// ~ Função para pagar uma venda que está com status "Aberto"
void pagarVendaAberta(struct Pagamento* listaPagamentos, int contadorPagamentos) {
    int encontrou = 0;

    // ~ Mostra vendas em aberto
    printf("\n--- Vendas em Aberto ---\n");
    for (int i = 0; i < contadorPagamentos; i++) {
        if (strcmp(listaPagamentos[i].status, "Aberto") == 0) {
            printf("Venda [%d] | Cliente: %s | Valor: R$ %.2f\n",
                   listaPagamentos[i].id,
                   listaPagamentos[i].carrinho.cliente.nome,
                   listaPagamentos[i].valor);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma venda em aberto encontrada.\n");
        return;
    }

    // ~ Solicita ID da venda
    int id;
    printf("\nDigite o número da venda que deseja pagar:\n => ");
    scanf("%d", &id);

    if (id < 0 || id >= contadorPagamentos || strcmp(listaPagamentos[id].status, "Aberto") != 0) {
        printf("Venda inválida ou já paga.\n");
        return;
    }

    // ~ Escolhe o tipo de pagamento
    int tipoPagamento;
    printf("Escolha a forma de pagamento:\n[1] Dinheiro\n[2] Cartão\n[3] Misto Dinheiro/Cartão\n => ");
    scanf("%d", &tipoPagamento);

    switch (tipoPagamento) {
        case 1:
            strcpy(listaPagamentos[id].tipo, "Dinheiro");
            break;
        case 2:
            strcpy(listaPagamentos[id].tipo, "Cartao");
            break;
        case 3:
            strcpy(listaPagamentos[id].tipo, "Misto Dinheiro/Cartao");
            break;
        default:
            printf("Tipo inválido. Venda não atualizada.\n");
            return;
    }

    // ~ Atualiza status
    strcpy(listaPagamentos[id].status, "Pago");
    printf("Venda [%d] paga com sucesso!\n", id);
}


















// ~ Os coiso de relatorio aqui ->
// ~ Mostra todos os clientes ordenados por nome


void listarClientesQueCompraram(struct Pagamento* listaPagamentos, int totalPagamentos) {
    int d, m, a, d2, m2, a2;
    printf("\nDigite o período desejado:\nData Inicial (DD MM AAAA): ");
    scanf("%d %d %d", &d, &m, &a);
    printf("Data Final (DD MM AAAA): ");
    scanf("%d %d %d", &d2, &m2, &a2);

    printf("\n--- Clientes que compraram no período ---\n");
    for (int i = 0; i < totalPagamentos; i++) {
        struct Carrinho c = listaPagamentos[i].carrinho;

        // ~ Verifica se está no intervalo
        if ((c.ano > a || (c.ano == a && c.mes > m) || (c.ano == a && c.mes == m && c.dia >= d)) &&
            (c.ano < a2 || (c.ano == a2 && c.mes < m2) || (c.ano == a2 && c.mes == m2 && c.dia <= d2))) {
            printf("Cliente: %s | Data: %02d/%02d/%04d | Valor: R$ %.2f\n",
                   c.cliente.nome, c.dia, c.mes, c.ano, listaPagamentos[i].valor);
        }
    }
}




void listarClientesOrdemAlfabetica(struct Cliente* listaClientes, int totalClientes) {
    printf("\n--- Clientes em Ordem Alfabética ---\n");

    // ~ Cria cópia temporária para ordenação
    struct Cliente temp[totalClientes];
    memcpy(temp, listaClientes, sizeof(struct Cliente) * totalClientes);

    // ~ Ordena por nome (bubble sort simples)
    for (int i = 0; i < totalClientes - 1; i++) {
        for (int j = 0; j < totalClientes - i - 1; j++) {
            if (strcmp(temp[j].nome, temp[j + 1].nome) > 0) {
                struct Cliente aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    for (int i = 0; i < totalClientes; i++) {
        printf("Cliente: %s | CPF: %lld\n", temp[i].nome, temp[i].cpf);
    }
}



// ~ Mostra todos os produtos em ordem alfabética
void listarProdutosOrdenados(struct Produto* listaProdutos, int totalProdutos) {
    printf("\n--- Produtos em Ordem Alfabética ---\n");

    struct Produto temp[totalProdutos];
    memcpy(temp, listaProdutos, sizeof(struct Produto) * totalProdutos);

    for (int i = 0; i < totalProdutos - 1; i++) {
        for (int j = 0; j < totalProdutos - i - 1; j++) {
            if (strcmp(temp[j].nome, temp[j + 1].nome) > 0) {
                struct Produto aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    for (int i = 0; i < totalProdutos; i++) {
        printf("Produto: %s | Categoria: %s | Estoque: %d\n", temp[i].nome, temp[i].categoria, temp[i].quantidade);
    }
}



// ~ Mostra produtos mais vendidos (por nome)
void produtosMaisVendidos(struct Pagamento* listaPagamentos, int totalPagamentos) {
    printf("\n--- Produtos Mais Vendidos ---\n");

    struct {
        char nome[100];
        int totalVendidos;
    } ranking[100];

    int usados = 0;

    for (int i = 0; i < totalPagamentos; i++) {
        for (int j = 0; j < listaPagamentos[i].carrinho.totalItens; j++) {
            struct Produto* p = listaPagamentos[i].carrinho.itens[j].produto;
            int qtd = listaPagamentos[i].carrinho.itens[j].quantidade;

            // ~ Verifica se já está no ranking
            int achou = 0;
            for (int k = 0; k < usados; k++) {
                if (strcmp(ranking[k].nome, p->nome) == 0) {
                    ranking[k].totalVendidos += qtd;
                    achou = 1;
                    break;
                }
            }

            if (!achou) {
                strcpy(ranking[usados].nome, p->nome);
                ranking[usados].totalVendidos = qtd;
                usados++;
            }
        }
    }

    for (int i = 0; i < usados; i++) {
        printf("Produto: %s | Total vendido: %d\n", ranking[i].nome, ranking[i].totalVendidos);
    }
}



// ~ Mostra todas as vendas feitas em um período
void listarVendasPorPeriodo(struct Pagamento* listaPagamentos, int totalPagamentos) {
    int d, m, a, d2, m2, a2;
    printf("\nDigite o período desejado:\nData Inicial (DD MM AAAA): ");
    scanf("%d %d %d", &d, &m, &a);
    printf("Data Final (DD MM AAAA): ");
    scanf("%d %d %d", &d2, &m2, &a2);

    printf("\n--- Vendas no Período ---\n");
    for (int i = 0; i < totalPagamentos; i++) {
        struct Carrinho c = listaPagamentos[i].carrinho;

        if ((c.ano > a || (c.ano == a && c.mes > m) || (c.ano == a && c.mes == m && c.dia >= d)) &&
            (c.ano < a2 || (c.ano == a2 && c.mes < m2) || (c.ano == a2 && c.mes == m2 && c.dia <= d2))) {
            printf("Venda: %d | Cliente: %s | Valor: R$ %.2f | Data: %02d/%02d/%04d\n",
                   listaPagamentos[i].id, c.cliente.nome, listaPagamentos[i].valor,
                   c.dia, c.mes, c.ano);
        }
    }
}




// ~ Mostra total de vendas por tipo de pagamento
void faturamentoPorTipoPagamento(struct Pagamento* listaPagamentos, int totalPagamentos) {
    float dinheiro = 0, cartao = 0, misto = 0;

    for (int i = 0; i < totalPagamentos; i++) {
        if (strcmp(listaPagamentos[i].tipo, "Dinheiro") == 0) dinheiro += listaPagamentos[i].valor;
        else if (strcmp(listaPagamentos[i].tipo, "Cartao") == 0) cartao += listaPagamentos[i].valor;
        else if (strstr(listaPagamentos[i].tipo, "Misto") != NULL) misto += listaPagamentos[i].valor;
    }

    printf("\n===== Faturamento Consolidado =====\n");
    printf("Total em Dinheiro: R$ %.2f\n", dinheiro);
    printf("Total em Cartão:   R$ %.2f\n", cartao);
    printf("Total em Misto:    R$ %.2f\n", misto);
    printf("TOTAL GERAL:       R$ %.2f\n", dinheiro + cartao + misto);
}



