#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Produtos.h"
#include "Clientes.h"
#include "Usuario.h"
#include "Pagamentos.h"


// ~ Função para criar um novo usuário do sistema
struct Usuario* novoUsuarioSistema(struct Usuario** listaUsuariosSistema, int* totalUsuarios) {
    char loginTemp[13];
    int loginValido = 0, senhaValida = 0, tipoValido = 0;

    // ~ Realocação para adicionar novo usuario na lista
    *listaUsuariosSistema = realloc(*listaUsuariosSistema, sizeof(struct Usuario) * (*totalUsuarios + 1));
    if (*listaUsuariosSistema == NULL) {
        printf("Erro ao alocar memória para novo usuário do sistema.\n");
        exit(1);
    }

    struct Usuario* usuarioAtual = &(*listaUsuariosSistema)[*totalUsuarios];
    usuarioAtual->id = *totalUsuarios;

    // ~ Verificação do login
    while (!loginValido) {
        printf("Digite o login (8 a 12 caracteres):\n => ");
        scanf("%12s", loginTemp);

        int tam = strlen(loginTemp);
        if (tam < 8 || tam > 12) {
            printf("Login inválido!\n");
            continue;
        }

        // ~ Verificar duplicidade
        int duplicado = 0;
        for (int i = 0; i < *totalUsuarios; i++) {
            if (strcmp((*listaUsuariosSistema)[i].login, loginTemp) == 0) {
                duplicado = 1;
                break;
            }
        }

        if (duplicado) {
            printf("Login já existe.\n");
        } else {
            strcpy(usuarioAtual->login, loginTemp);
            loginValido = 1;
        }
    }

    // ~ Cadastro da senha
    while (!senhaValida) {
        printf("Digite a senha (6 a 8 caracteres):\n => ");
        scanf("%8s", usuarioAtual->senha);

        int tam = strlen(usuarioAtual->senha);
        if (tam < 6 || tam > 8) {
            printf("Senha inválida!\n");
        } else {
            senhaValida = 1;
        }
    }

    // ~ Definir tipo do usuario
    while (!tipoValido) {
        printf("Tipo do usuário [1] Admin | [2] Comum:\n => ");
        scanf("%d", &usuarioAtual->tipo);

        if (usuarioAtual->tipo != 1 && usuarioAtual->tipo != 2) {
            printf("Tipo inválido.\n");
        } else {
            tipoValido = 1;
        }
    }

    printf("Usuário criado com sucesso!\n");
    (*totalUsuarios)++;
    return *listaUsuariosSistema;
}



// ~ Função de login no sistema
struct Usuario* loginSistema(struct Usuario* listaUsuariosSistema, int totalUsuarios) {
    char login[13], senha[9];
    printf("\n--- Login ---\nLogin: ");
    scanf("%12s", login);
    printf("Senha: ");
    scanf("%8s", senha);

    for (int i = 0; i < totalUsuarios; i++) {
        if ((strcmp(listaUsuariosSistema[i].login, login) == 0) &&
            (strcmp(listaUsuariosSistema[i].senha, senha) == 0)) {
            printf("Login bem-sucedido.\n");
            return &listaUsuariosSistema[i];
        }
    }

    printf("Login ou senha inválidos.\n");
    return NULL;
}



// ~ Verifica se é administrador
int verificaAdmin(struct Usuario* usuarioAtual, struct Usuario* listaUsuariosSistema, int totalUsuarios) {
    if (usuarioAtual->tipo == 1) return 1;

    printf("\n\n--- Permissão de Administrador Necessária ---\n");
    struct Usuario* adminTemp = loginSistema(listaUsuariosSistema, totalUsuarios);
    if (adminTemp && adminTemp->tipo == 1) {
        printf("Permissão concedida!\n");
        return 1;
    }

    printf("Permissão negada.\n");
    return 0;
}



// ~ Exporta os usuarios do sistema para um arquivo .txt
void exportarUsuariosSistema(struct Usuario* listaUsuariosSistema, int totalUsuarios) {
    FILE* arq = fopen("./data/usuariosSistema.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < totalUsuarios; i++) {
        fprintf(arq, "ID: %d\nLogin: %s\nTipo: %s\n\n",
            listaUsuariosSistema[i].id,
            listaUsuariosSistema[i].login,
            listaUsuariosSistema[i].tipo == 1 ? "Administrador" : "Comum");
    }

    fclose(arq);
    printf("\nUsuários exportados para ./data/usuariosSistema.txt\n");
}