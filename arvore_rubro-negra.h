#ifndef ARVORE_RUBRO_NEGRA_H
#define ARVORE_RUBRO_NEGRA_H

/*
 * Estrutura de um nó da árvore rubro-negra.
 * cor: PRETO = 0, VERMELHO = 1.
 */
#define PRETO 0
#define VERMELHO 1

typedef struct no_rubro_negro {
    int chave;
    int cor;
    struct no_rubro_negro *pai;
    struct no_rubro_negro *esq;
    struct no_rubro_negro *dir;
} TNoRB;

void inserirNo(TNoRB **arvore, TNoRB *pPai, TNoRB **pMain, int k);
TNoRB *obterAvo(TNoRB *arvore);
TNoRB *obterTio(TNoRB *arvore);
void rotacionarDireita(TNoRB **no);
void rotacionarEsquerda(TNoRB **no);
void corrigirArvoreRubroNegra(TNoRB **arvore, TNoRB **pMain);
void percorrerEmOrdem(TNoRB *raiz);
void rotacaoDuplaEsquerda(TNoRB **no);
void rotacaoDuplaDireita(TNoRB **no);
void removerNo(TNoRB **arvore, int k);
void tratarNoPretoIrmaoPretoFilhoVermelho(TNoRB *aRemover, TNoRB **arvore);
void tratarNoPretoIrmaoPretoFilhoPreto(TNoRB *aRemover, TNoRB **arvore);
void tratarNoPretoIrmaoVermelho(TNoRB *aRemover, TNoRB **arvore);
TNoRB *buscarNo(TNoRB *arvore, int k);
TNoRB *obterIrmao(TNoRB *pai, TNoRB *noAtual);
int ehFilhoEsquerdo(TNoRB *arvore);
TNoRB **maiorNaSubarvoreEsquerda(TNoRB **pMaiorNaSubarvoreEsquerda);

#endif
