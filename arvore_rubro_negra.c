/*
    Este código foi fornecido por
    costheta_z
*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura que representa cada nó
// em uma árvore rubro-negra
struct node {
    int d; // dado
    int c; // 1-vermelho, 0-preto
    struct node* p; // pai
    struct node* r; // filho direito
    struct node* l; // filho esquerdo
};

// raiz global da árvore
struct node* root = NULL;

// função para realizar a inserção BST de um nó
struct node* inserir_bst(struct node* trav, struct node* temp)
{
    // Se a árvore estiver vazia,
    // retorna um novo nó
    if (trav == NULL)
        return temp;

    // Caso contrário, percorre a árvore recursivamente
    if (temp->d < trav->d) 
    {
        trav->l = inserir_bst(trav->l, temp);
        trav->l->p = trav;
    }
    else if (temp->d > trav->d) 
    {
        trav->r = inserir_bst(trav->r, temp);
        trav->r->p = trav;
    }

    // Retorna o ponteiro do nó sem alterações
    return trav;
}

// Função que realiza rotação à direita
// no nó passado como parâmetro
void rotacao_direita(struct node* temp)
{
    struct node* left = temp->l;

    temp->l = left->r;

    if (temp->l)
        temp->l->p = temp;

    left->p = temp->p;

    if (!temp->p)
        root = left;
    else if (temp == temp->p->l)
        temp->p->l = left;
    else
        temp->p->r = left;

    left->r = temp;
    temp->p = left;
}

// Função que realiza rotação à esquerda
// no nó passado como parâmetro
void rotacao_esquerda(struct node* temp)
{
    struct node* right = temp->r;

    temp->r = right->l;

    if (temp->r)
        temp->r->p = temp;

    right->p = temp->p;

    if (!temp->p)
        root = right;
    else if (temp == temp->p->l)
        temp->p->l = right;
    else
        temp->p->r = right;

    right->l = temp;
    temp->p = right;
}

// Esta função corrige as violações
// causadas pela inserção BST
void corrigir_insercao(struct node* root, struct node* pt)
{
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;

    while ((pt != root) && (pt->c != 0)
           && (pt->p->c == 1)) 
    {
        parent_pt = pt->p;
        grand_parent_pt = pt->p->p;

        /*
            Caso A:
            O pai de pt é filho esquerdo
            do avô de pt
        */
        if (parent_pt == grand_parent_pt->l) 
        {
            struct node* uncle_pt = grand_parent_pt->r;

            /*
                Caso 1:
                O tio de pt também é vermelho.
                Apenas a troca de cores é necessária.
            */
            if (uncle_pt != NULL && uncle_pt->c == 1) 
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
            else 
            {
                /*
                    Caso 2:
                    pt é filho direito de seu pai.
                    É necessária uma rotação à esquerda.
                */
                if (pt == parent_pt->r) {
                    rotacao_esquerda(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /*
                    Caso 3:
                    pt é filho esquerdo de seu pai.
                    É necessária uma rotação à direita.
                */
                rotacao_direita(grand_parent_pt);

                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;

                pt = parent_pt;
            }
        }

        /*
            Caso B:
            O pai de pt é filho direito
            do avô de pt
        */
        else 
        {
            struct node* uncle_pt = grand_parent_pt->l;

            /*
                Caso 1:
                O tio de pt também é vermelho.
                Apenas a troca de cores é necessária.
            */
            if ((uncle_pt != NULL) && (uncle_pt->c == 1)) 
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
            else 
            {
                /*
                    Caso 2:
                    pt é filho esquerdo de seu pai.
                    É necessária uma rotação à direita.
                */
                if (pt == parent_pt->l) {
                    rotacao_direita(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /*
                    Caso 3:
                    pt é filho direito de seu pai.
                    É necessária uma rotação à esquerda.
                */
                rotacao_esquerda(grand_parent_pt);

                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;

                pt = parent_pt;
            }
        }
    }
}

// Função para imprimir o percurso em ordem
// da árvore já corrigida
void percurso_em_ordem(struct node* trav)
{
    if (trav == NULL)
        return;

    percurso_em_ordem(trav->l);
    printf("%d ", trav->d);
    percurso_em_ordem(trav->r);
}

// código principal
int main()
{
    int n = 7;
    int a[7] = { 7, 6, 5, 4, 3, 2, 1 };

    for (int i = 0; i < n; i++) {

        /*
            Aloca memória para o nó e inicializa:
            1. cor como vermelho;
            2. ponteiros pai, esquerdo e direito como NULL;
            3. dado como o i-ésimo valor do vetor.
        */
        struct node* temp
            = (struct node*)malloc(sizeof(struct node));

        temp->r = NULL;
        temp->l = NULL;
        temp->p = NULL;
        temp->d = a[i];
        temp->c = 1;

        /*
            Chama a função que realiza a inserção BST
            do nó recém-criado
        */
        root = inserir_bst(root, temp);

        /*
            Chama a função que preserva as propriedades
            da árvore rubro-negra
        */
        corrigir_insercao(root, temp);

        // A raiz da árvore sempre deve ser preta
        root->c = 0;
    }

    printf("Percurso em ordem da árvore criada\n");
    percurso_em_ordem(root);

    return 0;
}
