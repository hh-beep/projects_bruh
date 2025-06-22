#ifndef MENUS_H
#define MENUS_H


#include "Usuario.h"
#include "Clientes.h"
#include "Produtos.h"
#include "Pagamentos.h"

// ~ Funções dos menus principais do sistema

void menuPrincipal(int* opcaoMenu);
void menuCadastros(int* opcaoSubMenu);
void menuVendas(int* opcaoSubMenu);
void menuCaixa(int* opcaoSubMenu);
void menuRelatorios(int* opcaoSubMenu);

#endif
