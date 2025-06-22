#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Produtos.h"
#include "Clientes.h"
#include "Usuario.h"
#include "Pagamentos.h"


// ~ Função para criar um novo cliente
struct Cliente* novoCliente(struct Cliente** listaClientes, int* contadorClientes) {
    int codigoValido = 0, codigoRepetido = 0;

    *listaClientes = realloc(*listaClientes, sizeof(struct Cliente) * (*contadorClientes + 1));
    if (*listaClientes == NULL) {
        printf("Erro ao alocar memoria para o cliente!\n");
        exit(1);
    }

    struct Cliente* clienteAtual = &(*listaClientes)[*contadorClientes];
    clienteAtual->id = *contadorClientes;

    // ~ Nome completo
    printf("Digite o nome completo do cliente:\n => ");
    scanf(" %[^\n]%*c", clienteAtual->nome);

    // ~ Nome social
    printf("Digite o nome social do cliente:\n => ");
    scanf(" %[^\n]%*c", clienteAtual->nomeSocial);

    // ~ Código do cliente (validando se já existe)
    while (!codigoValido) {
        printf("Digite o código do cliente [1000 a 9999]:\n => ");
        scanf("%d", &clienteAtual->codigo);

        if (clienteAtual->codigo < 1000 || clienteAtual->codigo > 9999) {
            printf("Código inválido! Digite um valor entre 1000 e 9999.\n");
            continue;
        }

        codigoRepetido = 0;
        for (int i = 0; i < *contadorClientes; i++) {
            if ((*listaClientes)[i].codigo == clienteAtual->codigo) {
                codigoRepetido = 1;
                break;
            }
        }

        if (codigoRepetido) {
            printf("Já existe um cliente com esse código! Digite outro.\n");
        } else {
            codigoValido = 1;
        }
    }

    // ~ CPF
    printf("Digite o CPF (somente números):\n => ");
    scanf("%lld", &clienteAtual->cpf);

    // ~ Rua e número
    printf("Digite a rua e o número:\n => ");
    scanf(" %[^\n]%*c", clienteAtual->ruaNumero);

    // ~ Bairro
    printf("Digite o bairro:\n => ");
    scanf(" %[^\n]%*c", clienteAtual->bairro);

    // ~ Telefone
    printf("Digite o telefone (somente números):\n => ");
    scanf(" %[^\n]%*c", clienteAtual->telefone);

    // ~ Confirmação
    printf("\nCliente cadastrado com sucesso!\n");
    printf("Nome: %s\n", clienteAtual->nome);
    printf("Nome Social: %s\n", clienteAtual->nomeSocial);
    printf("Codigo: %d\n", clienteAtual->codigo);
    printf("CPF: %lld\n", clienteAtual->cpf);
    printf("Endereco: %s, Bairro: %s\n", clienteAtual->ruaNumero, clienteAtual->bairro);
    printf("Telefone: %s\n", clienteAtual->telefone);

    (*contadorClientes)++;

    return *listaClientes;
}


// ~ Mostrar todos os clientes
void mostrarTodosClientes(struct Cliente* listaClientes, int contadorClientes) {
    if (contadorClientes <= 0) {
        printf("\nNenhum cliente cadastrado!\n");
        return;
    }

    printf("\n--- Lista de Clientes ---\n");
    for (int i = 0; i < contadorClientes; i++) {
        printf("Cliente [%d]:\n", i);
        printf("Nome: %s | Nome Social: %s | Código: %d\n", 
               listaClientes[i].nome, listaClientes[i].nomeSocial, listaClientes[i].codigo);
        printf("CPF: %lld | Endereço: %s, Bairro: %s | Tel: %s\n\n",
               listaClientes[i].cpf, listaClientes[i].ruaNumero, listaClientes[i].bairro, listaClientes[i].telefone);
    }
}


// ~ Exportar os clientes para arquivo
void exportarClientes(struct Cliente* listaClientes, int contadorClientes) {
    FILE* arq = fopen("./data/clientesData.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de clientes!\n");
        return;
    }

    for (int i = 0; i < contadorClientes; i++) {
        fprintf(arq, "Cliente [%d]:\n", i);
        fprintf(arq, "Nome: %s\n", listaClientes[i].nome);
        fprintf(arq, "Nome Social: %s\n", listaClientes[i].nomeSocial);
        fprintf(arq, "Codigo: %d\n", listaClientes[i].codigo);
        fprintf(arq, "CPF: %lld\n", listaClientes[i].cpf);
        fprintf(arq, "Endereco: %s, Bairro: %s\n", listaClientes[i].ruaNumero, listaClientes[i].bairro);
        fprintf(arq, "Telefone: %s\n\n", listaClientes[i].telefone);
    }

    fclose(arq);
    printf("\nClientes exportados para ./data/clientesData.txt\n");
}
