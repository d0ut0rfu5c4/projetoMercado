/*
Projeto 02 - Mercado)

Deve-se desenvolver uma aplicação onde ao ser inicializada apresente ao usuário um menu onde seja
possível cadastrar, listar e comprar produtos, além de visualizar carrinho de compra ou sair da aplicação.

Ao adicionar um produto no carrinho de compras, deve-se verificar se já existe um mesmo produto no
carrinho, bastando alterar a quantidade.

Ao finalizar a compra deve ser apresentado ao usuário o total de acordo com os produtos e quantidades
inseridas no carrinho de compra.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // biblioteca usada para dar pausas no programa quando o mesmo já estiver rodando.
//OBS: no Linux deve ser a biblioteca unistd.h, no windows é window.h

// vamos utilizar 2 structs, a primeira conterá os elemetos do produto.
// a outra vai conter as informações do carrinho.

typedef struct {
    int codigo; // código do produto.
    char nome[150]; // um array do nome do produto que pode ir até 30 caracteres.
    float preco; // preço do produto
} Produto; // nome da struct

typedef struct {
    Produto produto; //  o carrinho será composto por produtos, e estes produtos pegarão as informações da struct acima.
    int quantidade; // quantidade do produto no carrinho.
} Carrinho;// nome da struct

void infoProduto(Produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int *temNoCarrinho(int codigo); //é um array que irá retornar se X produto tem no carrinho.
void fecharPedido();

static int contador_produto = 0; //para se saber a quantidade de produtos cadastrados.
static int contador_carrinho = 0; //para saber a quantidade total de produtos no carrinho.

//OBS: como inicialmente ainda não há produto cadastrado, o contador_produto deve começar de 0.
//OBS 2: como inicialmente ainda não há produto no carrinho, o contador_carrinho deve começar de 0.

static Carrinho carrinho[50]; //cabem até 50 produtos no carrinho.
static Produto produtos[50]; //a loja tem até 50 produtos que podem ser cadastrados.

int main () {
    menu();
    return 0;
}

void infoProduto(Produto prod) {
    printf("\n\t O Código do seu produto é: %d\n\t Nome do produto: %s\n\t Preço: R$ %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);
    // o strtok é uma função específica da bibblioteca string.h e ela tira o \n no final da string
}

void menu() {
    printf("\n\t############################################################################################################################\n");
    printf("\n\t --------------------------------------------- Bem vindo(a) ao Mercadinho do Jão -------------------------------------------\n");

    printf("\n\t Selecione uma opção abaixo : \n");
    printf("\n\t 1 - Cadastrar produto\n");
    printf("\n\t 2 - Listar produtos\n");
    printf("\n\t 3 - Comprar produto\n");
    printf("\n\t 4 - Vizualizar carrinho\n");
    printf("\n\t 5 - Fechar pedido\n");
    printf("\n\t 6 - Sair do Mercadinho do Jão\n");

    int opcao;
    scanf("%d", &opcao);
    getchar(); // se formos receber uma string depois de um int ou um float, para não pular o dado com o \n (enter).

    switch (opcao) {
        case 1:
            cadastrarProduto();
            break;
        case 2:
            listarProdutos();
            break;
        case 3:
            comprarProduto();
            break;
        case 4:
            visualizarCarrinho();
            break;
        case 5:
            fecharPedido();
            break;
        case 6:
            printf("\n\t Volte sempre!\n");
            sleep(2); //sleep(2) no Linux, //Sleep é uma função da biblioteca windows.h
            exit(0);
        default:
            printf("\n\t Opção inválida !");
            sleep(2);
            menu();
            break;
    }
}

void cadastrarProduto() {
    printf("\n\t ######################################################\n");

    printf("\n\t Digite o nome do produto: ");
    fgets(produtos[contador_produto].nome, 30, stdin);

    printf("\n\t Digite o preço do produto: ");
    scanf("%f", &produtos[contador_produto].preco);

    printf("\n\t O produto %s foi cadastrado como êxito.\n", strtok(produtos[contador_produto].nome, "\n"));

    produtos[contador_produto].codigo = (contador_produto + 1);
    contador_produto++; 

    /*
    OBS 2: o contador_produto começa de 0 porque ainda não há produtos cadastrados,
    quando contador_produtos for incrementado, ele foi cadastrado com sucesso,

    ou seja: o contador_produtos será incrementado de uma em uma unidade.
    */
    
    sleep(2);
    menu();
}

void listarProdutos() {
    if (contador_produto > 0) {
        printf("\n\t Listagem de produtos.\n");
        printf("\n\t -----------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < contador_produto; i++) {
            infoProduto(produtos[i]);
            printf("\n\t *******************************************************************************************\n");
            sleep(1);
        }
        sleep(2);
        menu();
    } else {
        printf("\n\t Não temos ainda produtos cadastrados.\n");
        sleep(2);
        menu();
    }
}

void comprarProduto() {
    //primeiro ponto: para comprar um produto, é necessário q o mesmo exista, isto é, que ele esteja cadastrado no sistema.
    if (contador_produto > 0) {
        printf("\n\t Informe o código do produto que deseja adicionar ao carrinho.\n");

        printf("\n\t ======================================== Produtos disponíveis ===================================================\n"); //possa ser que o usuário esqueça o código,, para isso, deve - se fazer uma listagem para servir de lembrete para o usuário.
        for (int i = 0; i < contador_produto; i++) {
            infoProduto(produtos[i]);
            printf("\n\t ====================================================================\n");
            sleep(1);
        }
        int codigo;
        scanf("%d", &codigo);
        getchar();

        int tem_mercado = 0;
        for (int i = 0; i < contador_produto; i++) {
            if (produtos[i].codigo == codigo) {
                tem_mercado = 1;
                /*
                este teste lógico sere para checar se o código que o usuário digitou,
                se exite o produto com este código cadastrado no mercado.
                */

               if (contador_carrinho > 0) { 
                    int * retorno = temNoCarrinho(codigo);

                    if (retorno[0] == 1) {
                        carrinho[retorno[1]].quantidade++;
                        printf("\n\t Aumentei a quantidade do produto %s já existente no carrinho.\n",
								strtok(carrinho[retorno[1]].produto.nome, "\n"));
                        sleep(2);
                        menu();
                    } else {
                        Produto p = pegarProdutoPorCodigo(codigo);
                        carrinho[contador_carrinho].produto = p;
                        carrinho[contador_carrinho].quantidade = 1;
                        contador_carrinho++;
                        printf("\n\t O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                        sleep(2);
                        menu();

                        /* aqui já existe um produto no carrinho, mas este produto não está lá*/
                    }
               } else {
                    Produto p = pegarProdutoPorCodigo(codigo);
                    carrinho[contador_carrinho].produto = p;
                    carrinho[contador_carrinho].quantidade = 1;
                    contador_carrinho++;
                    printf("\n\t O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                    sleep(2);
                    menu();
               }
               /*
               aqui existe um produto, mas o produto não está no carrinho, entáo será adicionado.
               */
            }
        
        }
        if (tem_mercado < 1) {
            printf("\n\t Não foi encontrado o produto com o código %d informado.\n", codigo);
            sleep(2);
            menu();
        }
    } else {
        printf("\n\t Ainda não existem produtos cadastrados para a venda...\n");
        sleep(2);
        menu();
    }
}

void visualizarCarrinho() {
     if (contador_carrinho > 0) {
        printf("\n\t Produtos no carrinho.\n");
        printf("\n\t -----------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < contador_carrinho; i++) {
            infoProduto(carrinho[i].produto);
            printf("\n\t Quantidade : %d\n", carrinho[i].quantidade);
            printf("\n\t *******************************************************************************************\n");
            sleep(1);
        }
        sleep(2);
        menu();
    } else {
        printf("\n\t Não temos ainda produtos no carrinho.\n");
        sleep(2);
        menu();
    }
}

Produto pegarProdutoPorCodigo(int codigo) {
    Produto p;
    for (int i = 0; i < contador_produto; i++) {
        if (produtos[i].codigo == codigo) {
            p = produtos[i];
        }
    }
    return p;
}

int *temNoCarrinho(int codigo) {
    int static retorno[] = {0, 0};
    for (int i = 0; i < contador_carrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            retorno[0] = 1; //temm oo produto com este codigo no carrinho.
            retorno[i] = i; //o indice do produto no carrinho.
        }
    }
    return retorno;
}

/*
este ponteiro é necessário para podermos definir se um determinado produto tem
ou não no carrinho, por isso, deve - se retornar i, para não ter que repetir o 
produto cadastrado.
*/

void fecharPedido() {
    if (contador_carrinho > 0) {
        float valorTotal = 0.0; // deve começar em zero pq possa ser que ainda não tenha produtos, sem produtos, não há gastos
        printf("\n\t Produtos do Carrinho\n");
        printf("\n\t @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        for (int i = 0; i < contador_carrinho; i++) {
            Produto p = carrinho[i].produto;
            int quantidade = carrinho[i].quantidade;
            valorTotal += p.preco * quantidade;
            infoProduto(p);
            printf("\n\t Quantidade: %d\n", quantidade);
            printf("\n\t ################################################################################################\n");
            sleep(1);
        }
        printf("\n\t Sua fatura é: R$ %.2f\n", valorTotal);

        //limpar carrinho
        contador_carrinho = 0;
        printf("\n\t Ficamos muito felizes por sua preferência, volte sempre...\n");
        sleep(5);
        menu();
    } else {
        printf("\n\t Você ainda não tem nenhum produto no carrinho.\n");
        sleep(3);
        menu();
    }
}