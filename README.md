# Sistema de Gerenciamento de Estoque e Carrinho

Este programa simula um sistema de gerenciamento de estoque e carrinho de compras, permitindo cadastrar produtos, listar os disponíveis, adicionar itens ao carrinho e finalizar a compra.

## **Funcionalidades**

1. **Cadastrar Produto**
   - Permite cadastrar um novo produto com código único, nome e preço.
   - Valida se o código já existe no sistema.

2. **Listar Produtos**
   - Exibe todos os produtos cadastrados no estoque.

3. **Comprar Produto**
   - Adiciona produtos ao carrinho ou incrementa a quantidade se o produto já estiver no carrinho.

4. **Visualizar Carrinho**
   - Lista todos os itens do carrinho com suas quantidades e preços.

5. **Fechar Pedido**
   - Exibe o total da compra e limpa o carrinho.

6. **Sair**
   - Encerra o programa.

## **Tratamento de Erros**

- Verificação de entradas inválidas em códigos e preços.
- Mensagens de erro para estoque ou carrinho vazio.
- Código duplicado ao cadastrar produto.

## **Como Compilar e Executar**

1. Clone este repositório ou copie o código para um arquivo chamado `main.c`.
2. Compile o programa com:
   ```bash
   gcc main.c -o sistema


## Detalhes Técnicos
1. Linguagem: C
2. Entrada validada para evitar erros de execução.
3. Mensagens de erro amigáveis para o usuário.