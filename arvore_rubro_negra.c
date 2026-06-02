/*
 * Árvore Rubro-Negra para números inteiros.
 *
 * Código adaptado e padronizado em português a partir do projeto:
 * https://github.com/othonalberto/redblack_tree
 *
 * Referência original: implementação de Red Black Tree desenvolvida por
 * Othon Briganó e Pedro Warmling Botelho.
 *
 * Observação: esta versão mantém a lógica do código-base e traduz/padroniza
 * nomes de funções, constantes e comentários para facilitar a apresentação
 * didática em português.
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "arvore_rubro_negra.h"

#define PRETO 0
#define VERMELHO 1

/*
 * Insere uma nova chave na árvore seguindo a regra de inserção de uma ABB.
 * Após inserir, a função de correção é chamada para restaurar as propriedades
 * da árvore rubro-negra.
 */
void inserirNo(TNoRB **arvore, TNoRB *pPai, TNoRB **pMain, int k) {
    assert(arvore);

    if (*arvore == NULL) {
        *arvore = (TNoRB*)malloc(sizeof(TNoRB));
        if (*arvore == NULL) return;

        (*arvore)->chave = k;
        (*arvore)->cor = VERMELHO;

        (*arvore)->esq = NULL;
        (*arvore)->dir = NULL;
        (*arvore)->pai = pPai;
    } else {

        if (k < (*arvore)->chave) {
            inserirNo(&((*arvore)->esq), *arvore, pMain, k);
            corrigirArvoreRubroNegra(&((*arvore)->esq), pMain);
        } else if (k > (*arvore)->chave) {
            inserirNo(&((*arvore)->dir), *arvore, pMain, k);
            corrigirArvoreRubroNegra(&((*arvore)->dir), pMain);
        }
    }
    
    if (*arvore == *pMain)
            (*arvore)->cor = PRETO;

}

/*
 * Retorna o avô de um nó, quando ele existir.
 */
TNoRB *obterAvo(TNoRB *arvore) {
    if ((arvore != NULL) && (arvore->pai != NULL))
            return (arvore->pai)->pai;
    else
        return NULL;
}

/*
 * Retorna o tio de um nó, ou seja, o irmão do pai do nó.
 */
TNoRB *obterTio(TNoRB *arvore) {
    TNoRB *nAvo = obterAvo(arvore);
    if (nAvo == NULL) return NULL;

    if (arvore->pai == nAvo->esq)
        return nAvo->dir;
    else
        return nAvo->esq;

}

/*
 * Executa uma rotação simples à direita a partir do nó informado.
 * A rotação é usada para corrigir violações de balanceamento.
 */
void rotacionarDireita(TNoRB **no) {
    assert(no);

    if (*no == NULL) return;

    TNoRB *aux = *no;
    *no = aux->esq;
    aux->esq = (*no)->dir;
    (*no)->dir = aux;

    (*no)->pai = aux->pai;
    if(aux->dir != NULL)
        (aux->dir)->pai = aux;

    aux->pai = *no;

    aux->cor = VERMELHO;
    (*no)->cor = PRETO;

}

/*
 * Executa uma rotação simples à esquerda a partir do nó informado.
 * A rotação é usada para corrigir violações de balanceamento.
 */
void rotacionarEsquerda(TNoRB **no) {
    assert(no);

    if (*no == NULL) return;

    TNoRB *aux = *no;
    *no = aux->dir;
    aux->dir = (*no)->esq;
    (*no)->esq = aux;

    (*no)->pai = aux->pai;
    if (aux->esq != NULL)
        (aux->esq)->pai = aux;

    aux->pai = *no;
 
    aux->cor = VERMELHO;
    (*no)->cor = PRETO;
}

/*
 * Corrige a árvore após uma inserção.
 * Trata os casos de pai vermelho, tio vermelho, rotações simples e rotações duplas.
 */
void corrigirArvoreRubroNegra(TNoRB **arvore, TNoRB **pMain) {
    assert(arvore);

    TNoRB *nAvo = NULL;
    TNoRB *nTio = NULL;

    if((*arvore)->pai != NULL) {
        if((*arvore)->pai->cor == PRETO) return;

        if((*arvore)->cor == VERMELHO) {
            nTio = obterTio(*arvore); 
            if (nTio != NULL && nTio->cor == VERMELHO) {
                nAvo = obterAvo(*arvore);
                (*arvore)->pai->cor = PRETO;
                nTio->cor = PRETO;
                if (nAvo->pai != NULL) {
                    nAvo->cor = VERMELHO;
                } 
            } else {
                nAvo = obterAvo(*arvore);
                if (nAvo != NULL) {
                    if ((*arvore)->pai == nAvo->esq) { // caso em que o pai é filho esquerdo do avô
                        if ((*arvore) == (nAvo->esq)->esq) {
                            if (nAvo->pai != NULL) {
                                if ((nAvo->pai)->esq == nAvo)
                                    rotacionarDireita(&((nAvo->pai)->esq));
                                else
                                    rotacionarDireita(&((nAvo->pai)->dir));
                            } else {
                                rotacionarDireita(pMain);
                            }


                       } else {
                           if (nAvo->pai != NULL) {
                               if ((nAvo->pai)->esq == nAvo) {
                                    rotacaoDuplaDireita(&((nAvo->pai)->esq));
                               } else
                                   rotacaoDuplaDireita(&((nAvo->pai)->dir));
                           } else { 
                                rotacaoDuplaDireita(pMain);
                           }
                      }
                   } else { 
                       if ((*arvore) == ((nAvo->dir)->dir)) {
                           if (nAvo->pai != NULL) {
                               if (((nAvo->pai)->esq) == nAvo) {
                                    rotacionarEsquerda(&((nAvo->pai)->esq));
                               } else
                                   rotacionarEsquerda(&((nAvo->pai)->dir));
                           } else {
                                rotacionarEsquerda(pMain);
                           }

                       } else {
                           if (nAvo->pai != NULL) {
                               if((nAvo->pai)->esq == nAvo) {
                                    rotacaoDuplaEsquerda(&((nAvo->pai)->esq));
                               } else {
                                   rotacaoDuplaEsquerda(&((nAvo->pai)->dir));
                               }
                           } else {
                                    rotacaoDuplaEsquerda(pMain);
                           }
                       }
                }
                }
            }
        }
    }
}
    

/*
 * Percorre a árvore em ordem: esquerda, raiz e direita.
 * Em uma árvore de busca, esse percurso imprime as chaves em ordem crescente.
 */
void percorrerEmOrdem(TNoRB *raiz) {
    if (raiz == NULL) return;

    percorrerEmOrdem(raiz->esq);
    printf("Endereço: %p\nChave: %d, Cor: %d\nPai: %p\nFilho esquerdo: %p\nFilho direito: %p\n\n", raiz, raiz->chave, raiz->cor, raiz->pai, raiz->esq, raiz->dir);
    percorrerEmOrdem(raiz->dir);
}

/*
 * Executa rotação dupla à esquerda.
 * Primeiro faz uma rotação à direita no filho direito; depois, uma rotação à esquerda no nó atual.
 */
void rotacaoDuplaEsquerda(TNoRB **no) {
    assert(no);

    rotacionarDireita(&((*no)->dir));
    rotacionarEsquerda(no);

}

/*
 * Executa rotação dupla à direita.
 * Primeiro faz uma rotação à esquerda no filho esquerdo; depois, uma rotação à direita no nó atual.
 */
void rotacaoDuplaDireita(TNoRB **no) {
    assert(no);

    rotacionarEsquerda(&((*no)->esq));
    rotacionarDireita(no);
}

/*
 * Remove um nó da árvore a partir da chave informada.
 * Quando necessário, aciona os tratamentos de remoção para preservar as propriedades rubro-negras.
 */
void removerNo(TNoRB **arvore, int k){
    assert(arvore);

    if((*arvore) == NULL) return;

    TNoRB *aRemover = *arvore;

    aRemover = buscarNo(aRemover, k);

    if(aRemover == NULL) return;

    if(aRemover->dir == NULL && aRemover->esq == NULL){
        if(aRemover->pai == NULL){
            free(aRemover);
            *arvore = NULL;
            return;
        } else {
            if(aRemover->cor == VERMELHO && aRemover->dir == NULL && aRemover->esq == NULL){
                if(ehFilhoEsquerdo(aRemover) == 1){
                    free(aRemover);
                    aRemover->pai->esq = NULL;
                } else {
                    free(aRemover);
                    aRemover->pai->dir = NULL;
                }
                return;
            } else {
                TNoRB *nIrmao = obterIrmao(aRemover->pai,aRemover);
                    if(nIrmao == NULL) return;

                if(aRemover->cor == PRETO && nIrmao->cor == PRETO){
                    if(nIrmao->dir == NULL && nIrmao->esq == NULL){
                        tratarNoPretoIrmaoPretoFilhoPreto(aRemover, arvore);
                        return;
                    } else if(nIrmao->esq->cor == PRETO && nIrmao->dir->cor == PRETO){
                        tratarNoPretoIrmaoPretoFilhoPreto(aRemover, arvore);
                        return;
                    }
                    else if(nIrmao->dir->cor == PRETO && nIrmao->esq == NULL){
                        tratarNoPretoIrmaoPretoFilhoPreto(aRemover, arvore);
                        return;
                    }
                    else if(nIrmao->esq->cor == PRETO && nIrmao->dir == NULL){
                        tratarNoPretoIrmaoPretoFilhoPreto(aRemover, arvore);
                        return;
                    }
                } else if(aRemover->cor == PRETO && nIrmao->cor == PRETO && (nIrmao->esq->cor == VERMELHO || nIrmao->dir->cor == VERMELHO)){
                    if(nIrmao->esq != NULL){
                        tratarNoPretoIrmaoPretoFilhoVermelho(aRemover, arvore);
                        return;
                    } else if (nIrmao->dir != NULL){
                        tratarNoPretoIrmaoPretoFilhoVermelho(aRemover, arvore);
                        return;
                    }
                } else if(aRemover->cor == PRETO && nIrmao->cor == VERMELHO){
                    tratarNoPretoIrmaoVermelho(aRemover, arvore);
                }
            }

            return;
        }
    } else if (aRemover->dir == NULL || aRemover->esq == NULL){
        if(aRemover->dir != NULL){
            aRemover->chave = aRemover->dir->chave;
            free(aRemover->dir);
            aRemover->dir = NULL;
        } else {
            aRemover->chave = aRemover->esq->chave;
            free(aRemover->esq);
            aRemover->esq = NULL;
        }
    } else {
        TNoRB **nSubstituto = maiorNaSubarvoreEsquerda(&(aRemover->esq));
        TNoRB *auxSubstituto = *nSubstituto;

        aRemover->chave = (*nSubstituto)->chave;
        (*nSubstituto)->pai->esq = (*nSubstituto)->esq;


        if(aRemover->cor == VERMELHO){
            if(aRemover->esq == NULL && aRemover == aRemover->pai->esq && (aRemover->dir->dir != NULL || aRemover->dir->esq != NULL)){
                if(aRemover->dir->dir != NULL){
                    rotacionarDireita(&(aRemover->esq));
                    rotacionarEsquerda(&aRemover);
                }
                if(aRemover->dir->esq != NULL){
                    rotacionarDireita(&(aRemover->dir));
                    rotacionarEsquerda(&aRemover);
                }
            } else if(aRemover->esq == NULL && aRemover == aRemover->pai->dir && (aRemover->esq->dir != NULL || aRemover->esq->esq != NULL)){
                if(aRemover->esq->dir != NULL){
                    rotacionarEsquerda(&(aRemover->esq));
                    rotacionarDireita(&aRemover);
                }
                if(aRemover->esq->esq != NULL){
                    rotacionarEsquerda(&(aRemover->esq));
                    rotacionarDireita(&aRemover);
                }
            }

            aRemover->cor = PRETO;
            if(aRemover->esq != NULL)
                aRemover->esq->cor = VERMELHO;
            if(aRemover->dir != NULL)
                aRemover->dir->cor = VERMELHO;
        }
        free(auxSubstituto);
    }
}

/*
 * Trata o caso de remoção em que o nó removido é preto,
 * o irmão é preto e há filho vermelho disponível para rotação/recoloração.
 */
void tratarNoPretoIrmaoPretoFilhoVermelho(TNoRB *aRemover, TNoRB **arvore){
    assert(arvore);

    TNoRB *paiARemover = aRemover->pai;

    if(ehFilhoEsquerdo(aRemover) == 1){
        free(aRemover);
        aRemover->pai->esq = NULL;
    } else {
        free(aRemover);
        aRemover->pai->dir = NULL;
    }

    if(paiARemover->esq == NULL){
        if(paiARemover->pai == NULL){
            if((paiARemover->dir)->dir == NULL){
                rotacionarDireita(&((*arvore)->dir));
            }
            rotacionarEsquerda(arvore);
        } 
        else {
            if((paiARemover->dir)->dir == NULL){
                rotacionarDireita(&(paiARemover->dir));
            }
            rotacionarEsquerda(&paiARemover);
        }
    } 
    else {
        if(paiARemover->pai == NULL){
            if((paiARemover->esq)->esq == NULL){
                rotacionarEsquerda(&((*arvore)->esq));
            }
            rotacionarDireita(arvore);
        } else {
            if((paiARemover->dir)->dir == NULL){
                rotacionarEsquerda(&(paiARemover->esq));
            }
            rotacionarDireita(&paiARemover);
        }
    }
    return;
}

/*
 * Trata o caso de remoção em que o nó removido é preto,
 * o irmão é preto e os filhos relevantes também são pretos ou nulos.
 */
void tratarNoPretoIrmaoPretoFilhoPreto(TNoRB *aRemover, TNoRB **arvore){
    assert(arvore);

    TNoRB *paiARemover = aRemover->pai;
    TNoRB *nIrmao = obterIrmao(paiARemover, aRemover);

    tratarNoPretoIrmaoVermelho(aRemover, arvore);

    paiARemover->cor = PRETO;
    nIrmao->cor = VERMELHO;
}

/*
 * Trata o caso de remoção em que o nó removido é preto e o irmão é vermelho.
 */
void tratarNoPretoIrmaoVermelho(TNoRB *aRemover, TNoRB **arvore){
    assert(arvore);

    TNoRB *paiARemover = aRemover->pai;

    tratarNoPretoIrmaoPretoFilhoVermelho(aRemover,arvore);

    paiARemover->cor = PRETO;
    if(paiARemover->esq != NULL)
        (paiARemover->esq)->cor = VERMELHO;
    if(paiARemover->dir != NULL)
        (paiARemover->dir)->cor = VERMELHO;
}

/*
 * Busca uma chave na árvore rubro-negra.
 * Retorna o ponteiro para o nó encontrado ou NULL caso a chave não exista.
 */
TNoRB *buscarNo(TNoRB *arvore, int k){
    if (arvore == NULL) return NULL;

    if (arvore->chave == k) return arvore;

    if (k < arvore->chave)
        return buscarNo(arvore->esq, k);
    else
        return buscarNo(arvore->dir, k);
}

/*
 * Retorna o irmão de um nó com base no ponteiro para o pai.
 */
TNoRB *obterIrmao(TNoRB *pai, TNoRB *noAtual){
    if(pai == NULL) return NULL;

    if(pai->dir->chave == noAtual->chave)
        return pai->esq;
    else
        return pai->dir;
}

/*
 * Verifica se o nó informado é filho esquerdo de seu pai.
 * Retorna 1 para verdadeiro e 0 para falso.
 */
int ehFilhoEsquerdo(TNoRB *arvore){
    if(arvore->pai->esq == arvore)
        return 1;
    else
        return 0;
}

/*
 * Retorna o maior nó da subárvore esquerda.
 * Esse nó é usado como substituto durante a remoção de um nó com dois filhos.
 */
TNoRB **maiorNaSubarvoreEsquerda(TNoRB **pMaiorEsq){
    assert(pMaiorEsq);
    
    if (*pMaiorEsq == NULL) return NULL;

    if ((*pMaiorEsq)->dir == NULL)
        return pMaiorEsq;
    else
        return maiorNaSubarvoreEsquerda(&((*pMaiorEsq)->dir));
}
