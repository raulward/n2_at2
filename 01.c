#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um produto
typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

// Estrutura para representar um item no carrinho
typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

// Função que verifica se um código de produto já está cadastrado no estoque
int codigoExiste(int codigo, Produto *estoque, int tamanho_estoque) {
    for (int i = 0; i < tamanho_estoque; i++) {
        if (estoque[i].codigo == codigo) {
            return 1;
        }
    }
    return 0;
}

// Função para cadastrar um novo produto no estoque
Produto cadastrarProduto(Produto *estoque, int tamanho_estoque) {
    Produto p1;
    int codigo_valido = 0;

    while (!codigo_valido) {
        printf("Insira o código do produto: ");
        if (scanf("%d", &p1.codigo) != 1 || p1.codigo <= 0) {
            printf("Erro: Código inválido! Tente novamente.\n");
            continue;
        }
        if (codigoExiste(p1.codigo, estoque, tamanho_estoque)) {
            printf("Erro: Código já cadastrado! Informe outro código.\n");
        } else {
            codigo_valido = 1;
        }
    }

    printf("Insira o nome do produto: ");
    scanf("%s", p1.nome);

    printf("Insira o preço do produto: ");
    if (scanf("%f", &p1.preco) != 1 || p1.preco < 0) {
        printf("Erro: Preço inválido!\n");
        exit(1);
    }

    return p1;
}

// Verifica se o estoque contém o produto pelo código
int temNoEstoque(int codigo, Produto *estoque, int index_estoque) {
    if (index_estoque == 0) {
        printf("Erro: Estoque vazio!\n");
        return 0;
    }

    for (int i = 0; i < index_estoque; i++) {
        if (estoque[i].codigo == codigo) {
            return 1;
        }
    }
    return 0;
}

// Lista todos os produtos disponíveis no estoque
void listarProdutos(Produto *estoque, int tamanho) {
    if (tamanho == 0) {
        printf("Erro: Estoque vazio!\n");
        return;
    }

    printf("\n--- Produtos Disponíveis ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Código: %d | Nome: %s | Preço: R$ %.2f\n",
               estoque[i].codigo, estoque[i].nome, estoque[i].preco);
        printf("-----------------------------\n");
    }
}

// Adiciona um produto ao carrinho
void comprarProduto(Produto *estoque, int codigo, int index_estoque, Carrinho *carrinho, int *index_carrinho) {
    if (index_estoque == 0) {
        printf("Erro: Estoque vazio!\n");
        return;
    }
    if (!temNoEstoque(codigo, estoque, index_estoque)) {
        printf("Erro: Produto não encontrado no estoque!\n");
        return;
    }

    for (int i = 0; i < *index_carrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            carrinho[i].quantidade++;
            printf("Produto já no carrinho. Quantidade incrementada.\n");
            return;
        }
    }

    carrinho[*index_carrinho].produto = estoque[codigo - 1];
    carrinho[*index_carrinho].quantidade = 1;
    (*index_carrinho)++;
    printf("Produto adicionado ao carrinho.\n");
}

// Exibe o carrinho de compras
void visualizarCarrinho(Carrinho *carrinho, int index_carrinho) {
    if (index_carrinho == 0) {
        printf("Erro: Carrinho vazio!\n");
        return;
    }

    printf("\n--- Itens no Carrinho ---\n");
    for (int i = 0; i < index_carrinho; i++) {
        printf("Produto: %s | Preço: %.2f | Quantidade: %d\n",
               carrinho[i].produto.nome,
               carrinho[i].produto.preco,
               carrinho[i].quantidade);
        printf("-----------------------------\n");
    }
}

// Fecha o pedido e exibe o total
void fecharPedido(Carrinho *carrinho, int index_carrinho) {
    if (index_carrinho == 0) {
        printf("Erro: Carrinho vazio! Não é possível fechar o pedido.\n");
        return;
    }

    float total = 0.0f;
    for (int i = 0; i < index_carrinho; i++) {
        total += carrinho[i].produto.preco * carrinho[i].quantidade;
    }
    printf("Total da compra: R$ %.2f\n", total);
}

// Exibe o menu principal
void menu() {
    Produto estoque[50];
    Carrinho carrinho[50];
    int index_estoque = 0, index_carrinho = 0, opcao;

    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Fechar Pedido\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Erro: Entrada inválida! Tente novamente.\n");
            exit(1);
        }

        printf("\033[H\033[J");

        switch (opcao) {
            case 1:
                estoque[index_estoque] = cadastrarProduto(estoque, index_estoque);
                index_estoque++;
                break;
            case 2:
                listarProdutos(estoque, index_estoque);
                break;
            case 3: {
                int codigo;
                printf("Informe o código do produto: ");
                if (scanf("%d", &codigo) != 1) {
                    printf("Erro: Código inválido!\n");
                    break;
                }
                comprarProduto(estoque, codigo, index_estoque, carrinho, &index_carrinho);
                break;
            }
            case 4:
                visualizarCarrinho(carrinho, index_carrinho);
                break;
            case 5:
                fecharPedido(carrinho, index_carrinho);
                index_carrinho = 0; // Limpa o carrinho após fechar o pedido
                break;
            case 6:
                printf("Saindo do sistema...\n");
                return;
            default:
                printf("Erro: Opção inválida! Tente novamente.\n");
        }
    } while (1);
}

int main() {
    menu();
    return 0;
}
