#ifndef USUARIO_H
#define USUARIO_H



#include "Menus.h"
#include "Clientes.h"
#include "Produtos.h"
#include "Pagamentos.h"


/*
 *  Arquivo de declaração das Structs e funções relacionadas aos usuários do sistema.
 *  Aqui ficam os dados do sistema (login e senha) e as permissões de administrador.
 *
 *  Obs: Este cadastro NÃO é o mesmo dos clientes. Aqui é para os usuários que acessam
 *  o sistema da Dona Berê (como administradores ou funcionários comuns).
 */


// ~ Struct do Usuario do Sistema (login)
struct Usuario {
    int id;
    char login[13];   // Login entre 8 a 12 caracteres
    char senha[9];    // Senha entre 6 a 8 caracteres
    int tipo;         // 1 = Admin | 2 = Comum
};




// ~ Funções de Usuario do Sistema

// Cria um novo usuário do sistema (admin ou comum)
struct Usuario* novoUsuarioSistema(struct Usuario** listaUsuariosSistema, int* totalUsuarios);

// Login no sistema
struct Usuario* loginSistema(struct Usuario* listaUsuariosSistema, int totalUsuarios);

// Verifica se o usuário atual é admin
int verificaAdmin(struct Usuario* usuarioAtual, struct Usuario* listaUsuariosSistema, int totalUsuarios);

// Exporta os usuários cadastrados para um arquivo ./data/usuariosSistema.txt
void exportarUsuariosSistema(struct Usuario* listaUsuariosSistema, int totalUsuarios);

#endif