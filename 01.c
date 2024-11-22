#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

Produto cadastrarProduto() {
    Produto p1;
    int codigo;
    char nome[30];
    float preco;

    printf("Insira o codigo do produto: ");
    scanf("%d", &codigo);
    printf("Insira o nome do produto: ");
    scanf("%s", nome);
    printf("Insira o preco do produto: ");
    scanf("%f", &preco);

    p1.codigo = codigo;
    strcpy(p1.nome, nome);
    p1.preco = preco;

    return p1;
}

int temNoEstoque(int codigo, Produto *estoque, int index_estoque) {
    for (int i = 0; i < index_estoque; i++) {
        if (estoque[i].codigo == codigo) {
            return 1;
        }
    }
    return 0;
}

void listarProdutos(Produto *p, int tamanho) {
    printf("\n--- Produtos Disponiveis ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Codigo: %d\n", p[i].codigo);
        printf("Nome: %s\n", p[i].nome);
        printf("Preco: %.2f\n", p[i].preco);
        printf("-----------------------------\n");
    }
}

int temNoCarrinho(Carrinho *c, int index_carrinho, int codigo) {
    if (index_carrinho == -1) {
        printf("Carrinho vazio.\n");
        return 0;
    } else {
        for (int i = 0; i < index_carrinho; i++) {
            if (c[i].produto.codigo == codigo) {
                return 1;
            }
        }
    }
    return 0;
}

int acharNoCarrinhoPeloCodigo(Carrinho *c, int index_carrinho, int codigo) {
    if (index_carrinho == -1) {
        printf("Carrinho vazio.\n");
    } else {
        for (int i = 0; i < index_carrinho; i++) {
            if (c[i].produto.codigo == codigo) {
                return i;
            }
        }
        printf("Produto nao encontrado.\n");
    }
    return -1;
}

Produto pegarNoEstoquePorCodigo(Produto *estoque, int index_estoque, int codigo) {
    if (index_estoque == 0) {
        printf("Estoque vazio.\n");
    } else {
        for (int i = 0; i < index_estoque; i++) {
            if (estoque[i].codigo == codigo) {
                return estoque[i];
            }
        }
    }
    Produto vazio = {0};
    return vazio;
}

void comprarProduto(Produto *estoque, int codigo, int index_estoque, Carrinho *c, int *index_carrinho) {
    if (temNoEstoque(codigo, estoque, index_estoque)) {
        if (temNoCarrinho(c, *(index_carrinho), codigo)) {
            int pos = acharNoCarrinhoPeloCodigo(c, *(index_carrinho), codigo);
            c[pos].quantidade += 1;
            *(index_carrinho) -= 1;
        } else {
            c[*(index_carrinho)].produto = pegarNoEstoquePorCodigo(estoque, index_estoque, codigo);
            c[*(index_carrinho)].quantidade = 1;
        }
    } else {
        printf("Produto nao encontrado!\n");
    }
}

void visualizarCarrinho(Carrinho *carrinho, int index_carrinho) {
    if (index_carrinho == -1) {
        printf("Carrinho vazio!\n");
        return;
    }
    printf("\n--- Itens no Carrinho ---\n");
    for (int i = 0; i < index_carrinho; i++) {
        printf("Produto: %s | Quantidade: %d\n",
               carrinho[i].produto.nome,
               carrinho[i].quantidade);
        printf("-----------------------------\n");
    }
}

void sairDoSistema() {
    printf("Saindo do sistema... Ate logo!\n");
    exit(0);
}

void menu() {
    int opcao;
    Produto estoque[100];
    Carrinho carrinho[100];
    int index_carrinho = 0, index_estoque = 0;
    int codigo;

    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Fechar Pedido\n");
        printf("6. Sair do Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        system("cls");

        switch (opcao) {
            case 1:
                estoque[index_estoque] = cadastrarProduto();
                index_estoque++;
                break;
            case 2:
                listarProdutos(estoque, index_estoque);
                break;
            case 3:
                printf("Insira o codigo do produto desejado: ");
                scanf("%d", &codigo);
                comprarProduto(estoque, codigo, index_estoque, carrinho, &index_carrinho);
                index_carrinho++;
                break;
            case 4:
                visualizarCarrinho(carrinho, index_carrinho);
                break;
            case 5:
                printf("Pedido fechado! Obrigado por comprar.\n");
                index_carrinho = 0;  // Limpa o carrinho
                break;
            case 6:
                sairDoSistema();
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 6);
}

int main() {
    menu();
    return 0;
}
