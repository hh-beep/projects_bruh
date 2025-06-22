#ifndef CLIENTES_H
#define CLIENTES_H

/*
 *  Arquivo de declaração da Struct e funções relacionadas aos CLIENTES.
 *  Aqui NÃO é login do sistema, são os clientes que compram na mercearia.
 */


// ~ Struct de Cliente
struct Cliente {
    int id;
    int codigo;
    char nome[100];
    char nomeSocial[100];
    long long cpf;
    char ruaNumero[100];
    char bairro[100];
    char telefone[20];
};




// ~ Funções

// Cadastrar um novo cliente
struct Cliente* novoCliente(struct Cliente** listaClientes, int* contadorClientes);

// Mostrar todos os clientes cadastrados
void mostrarTodosClientes(struct Cliente* listaClientes, int contadorClientes);

// Exportar os clientes para um arquivo
void exportarClientes(struct Cliente* listaClientes, int contadorClientes);

#endif
