#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ~ Tá, vamos começar le Berê
// ~ Aq pra baixo vai ter tdas as estructs de nossotro sistemas  

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

// ~ Struct do Usuario do Sistema (login)
struct Usuario {
    int id;
    char login[13];   // Login entre 8 a 12 caracteres
    char senha[9];    // Senha entre 6 a 8 caracteres
    int tipo;         // 1 = Admin | 2 = Comum
};

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



/*
 * Tá... Aqui vai ter todas as declarações do nosso sistema le BêRê
 */

// Cadastrar um novo produto
struct Produto* novoProduto(struct Produto** listaProdutos, int* contadorProdutos);

// Mostrar todos os produtos
void mostrarTodosProdutos(struct Produto* listaProdutos, int contadorProdutos);

// Exportar produtos para arquivo
void exportarProdutos(struct Produto* listaProdutos, int contadorProdutos);

// Cadastrar um novo cliente
struct Cliente* novoCliente(struct Cliente** listaClientes, int* contadorClientes);

// Mostrar todos os clientes cadastrados
void mostrarTodosClientes(struct Cliente* listaClientes, int contadorClientes);

// Exportar os clientes para um arquivo
void exportarClientes(struct Cliente* listaClientes, int contadorClientes);

// Cria um novo usuário do sistema (admin ou comum)
struct Usuario* novoUsuarioSistema(struct Usuario** listaUsuariosSistema, int* totalUsuarios);

// Login no sistema
struct Usuario* loginSistema(struct Usuario* listaUsuariosSistema, int totalUsuarios);

// Verifica se o usuário atual é admin
int verificaAdmin(struct Usuario* usuarioAtual, struct Usuario* listaUsuariosSistema, int totalUsuarios);

// Exporta os usuários cadastrados para um arquivo ./data/usuariosSistema.txt
void exportarUsuariosSistema(struct Usuario* listaUsuariosSistema, int totalUsuarios);

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












// ~ AGORA, as funções, clarop


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

    // ~ Uhhh, aq ele  faqqz averificação dos coiso  
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

    // ~ Rua e n úmero
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

        // ~ el tamanho de la streng
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
        // ~ strcmp verifica se uma string é ingual outra streng
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
        printf("Atenção: Divergência de R$ %.2f (%s)\n",
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














// ~ AGORAA, pra n faltar a tradição

// ~~~~~ Lê BêRê ~~~~~~~
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