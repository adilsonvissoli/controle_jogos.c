#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define T 100
typedef char string[T];

typedef struct dados_jogo {
    string nome;
    int ano;
    string genero;
    string produtora;
    float valor;
} jogo_t;

typedef struct node{
    jogo_t dados_jogo;
    struct node *prox;
} node_t;

int menu();
jogo_t novo_jogo();
node_t *novo_node(jogo_t jogo);
void inserir_jogo_lista_inicio(node_t *node, node_t **lista);
void inserir_jogo_lista_fim(node_t *node, node_t **lista);
node_t *localizar_ultimo_node_na_lista(node_t *node);
node_t *localizar_primeiro_node_na_lista(node_t);
void mostrar_dados_jogo(jogo_t dados_jogo);
void excluir_na_lista(node_t *node, node_t **listar);
void retirar_enter(string str);
void formatar_maiuscula(string str);
void listar_jogos_cadastrados(node_t *lista);
int sub_menu_cadastro();
void exportar_dados_arquivo_texto(char* nome, node_t *lista);

int main()
{
    int opc_p, opc_s;
    node_t *lista = NULL;

    do {
        opc_p = menu();

        switch (opc_p) {
            case 1: do {
                        opc_s = sub_menu_cadastro();

                        if(opc_s == 1){
                            inserir_jogo_lista_inicio(novo_node(novo_jogo()), &lista);
                            break;
                        } else if(opc_s == 2){
                            inserir_jogo_lista_inicio(novo_node(novo_jogo()), &lista);
                            break;
                        } else if(opc_s == 3){
                            break;
                        }
                    } while(opc_s != 0);
                break;
            case 2: listar_jogos_cadastrados(lista);
                    break;
            case 3: break;
            case 4: break;
            case 5: exportar_dados_arquivo_texto("jogos.txt", lista);
                    break;
        }

    } while(opc_p != 0);

    return 0;
}

int menu()
{
    int opc;

    printf("|=====CADASTRO DE JOGOS=====|\n");
    printf("-----------------------------\n");
    printf("1.Cadastrar novo jogo\n");
    printf("2.Listar jogos cadastrados\n");
    printf("3.Encontrar um jogo por nome\n");
    printf("4.Excluir jogo da lista\n");
    printf("5.Exportar dados para arquivo txt\n");
    printf("-----------------------------\n");
    printf("--->");
    scanf("%i", &opc);
    getchar();

    return opc;
}

int sub_menu_cadastro()
{
    int opc;

    printf("|=====INSERÇÃO NA LISTA=====|\n");
    printf("-----------------------------\n");
    printf("1.Pelo início\n");
    printf("2.Pelo fim\n");
    printf("3.Pelo meio\n");
    printf("0.Sair\n");
    printf("-----------------------------\n");
    printf("--->");
    scanf("%i", &opc);
    getchar();

    return opc;
}

jogo_t novo_jogo()
{
    jogo_t novo;

    printf("Nome do jogo........: ");
    fgets(novo.nome, T, stdin);
    retirar_enter(novo.nome);
    formatar_maiuscula(novo.nome);

    printf("Ano de lançamento...: ");
    scanf("%i", &novo.ano);
    getchar();

    printf("Gênero do jogo......: ");
    fgets(novo.genero, T, stdin);
    retirar_enter(novo.genero);
    formatar_maiuscula(novo.genero);

    printf("Produtora do jogo...: ");
    fgets(novo.produtora, T, stdin);
    retirar_enter(novo.produtora);
    formatar_maiuscula(novo.produtora);

    printf("Valor...............: ");
    scanf("%f", &novo.valor);
    getchar();

    return novo;
}

node_t *novo_node(jogo_t jogo)
{
    node_t *novo = NULL;

    novo = (node_t*)calloc(1, sizeof(node_t));

    novo->dados_jogo = jogo;
    novo->prox = NULL;

    return novo;
}

void inserir_jogo_lista_inicio(node_t *node, node_t **lista)
{
    if(*lista) { //*lista != NULL
        node->prox = *lista;
    }
    *lista = node;
}

void inserir_jogo_lista_fim(node_t *node, node_t **lista)
{
    node_t *ultimo = NULL;
    if(!*lista){ // *lista == NULL
        *lista = node;
    } else {
        ultimo = localizar_ultimo_node_na_lista(*lista);
        ultimo->prox = node;
    }
}

node_t *localizar_ultimo_node_na_lista(node_t *lista)
{
    for(lista; lista->prox; lista= lista->prox); //lista->prox != NULL

    return lista;
}

node_t *localizar_primeiro_node_na_lista(node_t)
{

}

void mostrar_dados_jogo(jogo_t dados_jogo)
{
    printf("Nome do jogo........: %s\n", dados_jogo.nome);
    
    printf("Ano de lançamento...: %i\n", dados_jogo.ano);

    printf("Gênero do jogo......: %s\n", dados_jogo.genero);
    
    printf("Produtora do jogo...: %s\n", dados_jogo.produtora);
    
    printf("Valor...............: %.2f\n\n", dados_jogo.valor);
}

void excluir_na_lista(node_t *node, node_t **listar)
{

}

void retirar_enter(string str)
{
    *(str+strlen(str)-1) = '\0';
}

void formatar_maiuscula(string str)
{
    for (int i = 0; i < strlen(str); i++){
        *(str+i) = toupper(*(str+i));
    }
}

void listar_jogos_cadastrados(node_t *lista)
{
    while (lista) {
        mostrar_dados_jogo(lista->dados_jogo);
        lista = lista->prox;
    }
}

void exportar_dados_arquivo_texto(char* nome, node_t *lista)
{
    FILE *fd  = NULL;

    fd = fopen(nome, "w");

    if(!fd) return;

    for (lista; lista != NULL; lista = lista->prox){
        fprintf(fd, "Nome do jogo........: %s\n", lista->dados_jogo.nome);
    
        fprintf(fd, "Ano de lançamento...: %i\n", lista->dados_jogo.ano);

        fprintf(fd, "Gênero do jogo......: %s\n", lista->dados_jogo.genero);
    
        fprintf(fd, "Produtora do jogo...: %s\n", lista->dados_jogo.produtora);
    
        fprintf(fd, "Valor...............: %.2f\n\n", lista->dados_jogo.valor);
    }

    fclose(fd);
}