//Criando um sistema de inventário utilizando lista linear em C
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 10
#define MAX_STRING 50

struct item {
    char nome[MAX_STRING];
    int quantidade;
};

typedef struct mochila {
    struct item items[MAX_ITEMS];
    int itemCount;
};

//Protótipos das funções
void mostrarMenu();
void adicionarItem(struct mochila *m, char *nome, int quantidade);
void removerItem(struct mochila *m, char *nome, int quantidade);
void mostrarInventario(struct mochila *m);
void liberarMochila(struct mochila *m); // Função para liberar memória alocada

// Função principal

int main () {
    struct mochila *minhaMochila = (struct mochila *)malloc(sizeof(struct mochila));
    minhaMochila->itemCount = 0;
    int escolha, quantidade;
    char nome[MAX_STRING];

    printf("Você está caindo, nas suas costas uma mochila e preso a ela, uma corda\n");
    printf("VOCÊ PUXA, E REZA!\n");
    printf("=============================\n");
    printf("Backpack Simulator - By Pedro\n");
    printf("=============================\n");
    printf("Você pousou em segurança, e sente uma vontade incontrolável de preencher sua mochila.\n");

    do {
        mostrarMenu();
        printf("O que deseja fazer? ");
        scanf("%d", &escolha);
        getchar(); // Consome o newline deixado pelo scanf

        switch (escolha) {
            case 1:
                printf("Digite o nome do item a ser adicionado: ");
                fgets(nome, MAX_STRING, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                adicionarItem(minhaMochila, nome, quantidade);
                break;
            case 2:
                printf("Digite o nome do item a ser removido: ");
                fgets(nome, MAX_STRING, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                removerItem(minhaMochila, nome, quantidade);
                break;
            case 3:
                mostrarInventario(minhaMochila);
                break;
            case 4:
                printf("Saindo do sistema de inventário.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 4);
    printf("Você já está cansado de carregar essa mochila, você joga ela fora e acorda :)\n");
    printf("GAME OVER!\n");

    liberarMochila(minhaMochila);
    return 0;
}

// Função para mostrar o menu
void mostrarMenu() {
    printf("=== Sistema de Inventário ===\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Mostrar Inventário\n");
    printf("4. Sair\n");
    printf("=============================\n");
}

// Função para adicionar item na mochila
void adicionarItem(struct mochila *m, char *nome, int quantidade) {
    if (m->itemCount >= MAX_ITEMS) {
        printf("Você sente o peso de sua mochila e seu corpo já não é mais capaz de suportar a caminhada extença e cansativa.\n");
        printf("Você se deita para descansar, mas ao fechar os olhos, uma matilha de lobos te ataca e você não resiste...\n");
        printf("GAME OVER!\n");
        exit(1);
    }
    strcpy(m->items[m->itemCount].nome, nome);
    m->items[m->itemCount].quantidade = quantidade;
    m->itemCount++;
    if (quantidade > 1)
        printf("%d %ss adicionados à mochila.\n", quantidade, nome);
    else
        printf("%d %s adicionado à mochila.\n", quantidade, nome);
}

// Função para remover item da mochila
void removerItem(struct mochila *m, char *nome, int quantidade) {
    for (int i = 0; i < m->itemCount; i++) {
        if (strcmp(m->items[i].nome, nome) == 0) {
            if (m->items[i].quantidade >= quantidade) {
                m->items[i].quantidade -= quantidade;
                if (m->items[i].quantidade == 0) {
                    // Remover o item completamente
                    for (int j = i; j < m->itemCount - 1; j++) {
                        m->items[j] = m->items[j + 1];
                    }
                    m->itemCount--;
                }
                if (quantidade == 1)
                    printf("%d %s removido da mochila.\n", quantidade, nome);
                else
                printf("%d %ss removidos da mochila.\n", quantidade, nome);
                return;
            } else {
                printf("Quantidade insuficiente de %s na mochila.\n", nome);
                return;
            }
        }
    }
    printf("Você não tem %s na mochila.\n", nome);
}

// Função para mostrar o inventário
void mostrarInventario(struct mochila *m) {
    printf("================ Inventário da Mochila ================\n");
    printf("| %-30s | %-10s |\n", "Item", "Quantidade");
    printf("|-------------------------------|------------|\n");
    for (int i = 0; i < m->itemCount; i++) {
        printf("| %-30s | %-10d |\n", m->items[i].nome, m->items[i].quantidade);
    }
    if (m->itemCount == 0) {
        printf("| %-42s |\n", "Mochila vazia.");
    }
    printf("=======================================================\n");
}

// Função para liberar memória alocada
void liberarMochila(struct mochila *m) {
    free(m);
}