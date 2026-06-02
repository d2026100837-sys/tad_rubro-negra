/*
 * Programa principal para testar a Árvore Rubro-Negra.
 *
 * Compatível com os arquivos:
 * - arvore_rubro_negra_pt.c
 * - arvore_rubro_negra.h
 */

#include <stdio.h>
#include "arvore_rubro_negra.h"

int main(void) {
    TNoRB *arvore = NULL;
    int opcao = -1;
    int elemento = 0;

    do {
        printf("\n===== MENU - ÁRVORE RUBRO-NEGRA =====\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Ver árvore em ordem\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Encerrando o programa.\n");
            return 1;
        }

        switch (opcao) {
            case 1:
                printf("Elemento a inserir: ");
                if (scanf("%d", &elemento) != 1) {
                    printf("Entrada inválida.\n");
                    return 1;
                }

                inserirNo(&arvore, NULL, &arvore, elemento);
                printf("Elemento %d inserido.\n", elemento);
                break;

            case 2:
                printf("Elemento a remover: ");
                if (scanf("%d", &elemento) != 1) {
                    printf("Entrada inválida.\n");
                    return 1;
                }

                removerNo(&arvore, elemento);
                printf("Operação de remoção do elemento %d concluída.\n", elemento);
                break;

            case 3:
                printf("\nPercurso em ordem da árvore:\n");
                percorrerEmOrdem(arvore);
                break;

            case 4:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

        printf("=====================================\n");
    } while (opcao != 4);

    return 0;
}
