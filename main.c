/* ------------ Include / Import ------------ */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#include "struct.h"
#include "adicionais.c"

#include "insercao/insercao.c"
#include "fatorBalanceamento/fatorBalanceamento.c"
// #include "balanceamentoEsquerda/rotacaoSimples.c"
// #include "balanceamentoDireita/rotacaoSimples.c"
// #include "balanceamentoEsquerda/rotacaoDupla.c"
// #include "balanceamentoDireita/rotacaoDupla.c"
// #include "remocao/remocao.c"
// #include "visitacao/ordens.c"
#include "apresentacao/apresentacao.c"

/* -------------------------------------------- */

/* ------------ Funcionalidades ------------- */

int main();

short verificarArvoreVazia(Nodo *nodo);

Nodo *alocarNodo();

Nodo *verificarExistenciaNodo(Nodo *nodo, int alvo);

void construirNodo(Nodo **pRaiz, Nodo *nodo);

void alterarDadosNodo(Nodo *nodo, short nivel);

void buscarNodoDesbalanceado(Nodo **alvo, short *rotacao, Nodo *nodo);

void encontrarPaiNodo(Nodo **pai, short *lado, int numero, Nodo *nodo);

void balancearArvore(Nodo **pRaiz);

void removerNodo(Nodo **pRaiz);

/* -------------------------------------------- */

// main: Funcao principal.

int main()
{

    setlocale(LC_ALL, "Portuguese");

    short opcao = -1;
    Nodo *pRaiz = NULL;
    Nodo *novoNodo = NULL;

    while (opcao != 0)
    {

        menu(&opcao);

        switch (opcao)
        {

        case 1:

            if (!confirmacao())
                continue;

            printf(" <> Alocando nodo.\n");
            novoNodo = alocarNodo();

            if (novoNodo)
            {
                printf(" <> Nodo alocado.\n");
                printf(" <> Construindo nodo.\n\n");
                construirNodo(&pRaiz, novoNodo);
                printf(" <> Nodo construido.\n");
                printf(" <> Alterando dados do(s) nodo(s).\n");
                alterarDadosNodo(pRaiz, 1);
                printf(" <> Dados alterados.\n");
                printf(" <> Verificando balanceamento.\n");
                balancearArvore(&pRaiz);
                printf(" <> Verificacao concluida.\n");
            }
            else
                printf(" <> Nao ha espaco de memoria disponivel!\n");

            break;

        case 2:

            if (verificarArvoreVazia(pRaiz))
                printf(" <> A arvore esta vazia!\n");
            else
            {
                if (!confirmacao())
                    continue;

                removerNodo(&pRaiz);

                if (!verificarArvoreVazia(pRaiz))
                {
                    printf(" <> Alterando dados do(s) nodo(s).\n");
                    alterarDadosNodo(pRaiz, 1);
                    printf(" <> Dados alterados.\n");
                    printf(" <> Verificando balanceamento.\n");
                    balancearArvore(&pRaiz);
                    printf(" <> Verificacao concluida.\n");
                }
            }

            break;

        case 3:

            if (verificarArvoreVazia(pRaiz))
                printf(" <> A arvore esta vazia!\n");
            else
            {
                /* Funcao VISITACAO */
                printf(" <> Pre-ordem: ");
                //preOrdem(pRaiz);
                printf("\n");

                printf(" <> Em-ordem.: ");
                //emOrdem(pRaiz);
                printf("\n");

                printf(" <> Pos-ordem: ");
                //posOrdem(pRaiz);
                printf("\n\n\n");
            }

            break;

        case 5:

            if (verificarArvoreVazia(pRaiz))
                printf(" <> A arvore esta vazia!\n");
            else
                mostrarArvoreSimplificada(pRaiz, pRaiz->alturaNodo);

            break;

        case 6:

            if (verificarArvoreVazia(pRaiz))

                printf(" <> A arvore esta vazia!\n");

            else
            {

                printf("----------------------------------------------------------------");
                for (int i = 1; i < (pRaiz->alturaNodo + 2); i++)
                    printf("-------");
                printf("-\n");

                printf("| Numero | Nivel | Altura | Grau | Fator | Esquerda | Direita |\n");

                printf("                                                                ");
                for (int i = 1; i < (pRaiz->alturaNodo + 2); i++)
                    printf("       ");
                printf("|\n");

                mostrarArvoreDetalhada(pRaiz, (pRaiz->alturaNodo + 1));
                printf("\n");

                printf("----------------------------------------------------------------");
                for (int i = 1; i < (pRaiz->alturaNodo + 2); i++)
                    printf("-------");
                printf("-\n\n\n");
            }

            break;

        case 0:

            if (pRaiz)
            {
                printf(" <> Liberando espaco de memoria preenchido.\n");
                limparMemoria(pRaiz);
                printf(" <> Espaco liberado.\n");
            }
            encerrarPrograma();

            break;
        }
    }

    return 0;
}

// verificarArvoreVazia: Verifica se a arvore esta vazia.

short verificarArvoreVazia(Nodo *nodo)
{

    if (nodo)
        return 0;

    else
        return 1;
};

// alocarNodo: Verifica se ha espaco de memoria e aloca um nodo.

Nodo *alocarNodo()
{

    Nodo *ponteiroNovo = (Nodo *)malloc(sizeof(Nodo));

    return ponteiroNovo;
};

// verificarExistenciaNodo: Verifica se existe um no com o valor passado pela variavel alvo.

Nodo *verificarExistenciaNodo(Nodo *nodo, int alvo)
{

    if (nodo)
    {

        if (nodo->numeroNodo == alvo)
            return nodo;

        else if (nodo->numeroNodo > alvo)
            return verificarExistenciaNodo(nodo->filhoEsquerda, alvo);

        else
            return verificarExistenciaNodo(nodo->filhoDireita, alvo);
    }
    else
        return NULL;
};

// construirNodo: Constroi o nodo colocando dados dentro do mesmo.

void construirNodo(Nodo **pRaiz, Nodo *nodo)
{
    while (1)
    {
        printf(" </> Informe um numero de ate 4 digitos para o nodo: ");
        scanf("%d", &nodo->numeroNodo);
        printf("\n");

        if (verificarExistenciaNodo(*pRaiz, nodo->numeroNodo))
            printf(" </> Ja existe um nodo com este numero!\n\n");
        else
            break;
    }

    printf(" </> Inserindo nodo na arvore.\n");
    nodo->nivelNodo = inserirNodo(nodo, pRaiz, (*pRaiz)) + 1; /* Funcao INSERCAO */
    printf(" </> Nodo inserido.\n");

    nodo->grauNodo = 0;

    nodo->alturaNodo = 1;

    nodo->filhoDireita = NULL;

    nodo->alturaDireita = 0;

    nodo->filhoEsquerda = NULL;

    nodo->alturaEsquerda = 0;

    nodo->fatorBalanceamento = 0;

    return;
};

// alterarDadosNodo: Vai alterar os dados de cada nodo.

void alterarDadosNodo(Nodo *nodo, short nivel)
{
    if (nodo)
    {
        alterarDadosNodo(nodo->filhoEsquerda, (nivel + 1));
        alterarDadosNodo(nodo->filhoDireita, (nivel + 1));

        nodo->nivelNodo = nivel;

        if (nodo->filhoEsquerda && nodo->filhoDireita)
            nodo->grauNodo = 2;
        else if (nodo->filhoEsquerda || nodo->filhoDireita)
            nodo->grauNodo = 1;
        else
            nodo->grauNodo = 0;

        nodo->fatorBalanceamento = fatorDeBalanceamento(nodo); /* FATORBALANCEAMENTO */

        nodo->alturaNodo = max(nodo->alturaEsquerda, nodo->alturaDireita) + 1;
    }

    return;
};

// buscarNodoDesbalanceado: Procura nodos desbalanceados.

void buscarNodoDesbalanceado(Nodo **alvo, short *rotacao, Nodo *nodo)
{
    if (nodo)
    {
        if (nodo->fatorBalanceamento == -2)
        {
            if (nodo->filhoEsquerda->fatorBalanceamento == -2 || nodo->filhoEsquerda->fatorBalanceamento == 2)
                buscarNodoDesbalanceado(alvo, rotacao, nodo->filhoEsquerda);
            else
            {
                (*alvo) = nodo;
                if (nodo->filhoEsquerda->fatorBalanceamento == -1)
                    *rotacao = 1;
                else
                    *rotacao = 2;

                return;
            }
        }
        else if (nodo->fatorBalanceamento == 2)
        {
            if (nodo->filhoDireita->fatorBalanceamento == -2 || nodo->filhoDireita->fatorBalanceamento == 2)
                buscarNodoDesbalanceado(alvo, rotacao, nodo->filhoDireita);
            else
            {
                (*alvo) = nodo;
                if (nodo->filhoDireita->fatorBalanceamento == -1)
                    *rotacao = -2;
                else
                    *rotacao = -1;

                return;
            }
        }
        else
        {
            buscarNodoDesbalanceado(alvo, rotacao, nodo->filhoEsquerda);
            buscarNodoDesbalanceado(alvo, rotacao, nodo->filhoDireita);
        }
    }

    return;
};

// encontrarPaiNodo: Encontra o pai do nodo.

void encontrarPaiNodo(Nodo **pai, short *lado, int numero, Nodo *nodo)
{
    if (nodo->numeroNodo != numero)
    {
        if (nodo->filhoEsquerda->numeroNodo == numero)
        {
            (*pai) = nodo;
            *lado = -1;
            return;
        }
        else if (nodo->filhoDireita->numeroNodo == numero)
        {
            (*pai) = nodo;
            *lado = 1;
            return;
        }
        else
        {
            if (nodo->numeroNodo > numero)
                return encontrarPaiNodo(pai, lado, numero, nodo->filhoEsquerda);
            else
                return encontrarPaiNodo(pai, lado, numero, nodo->filhoDireita);
        }
    }
    else
    {
        (*pai) = NULL;
        *lado = 0;
        return;
    }
};

// balancearArvore: Vai chamar a rotacao para balancear a arvore.

void balancearArvore(Nodo **pRaiz)
{
    Nodo *pai = NULL;
    Nodo *alvo = NULL;
    short lado;
    short rotacao;

    printf(" </> Buscando nodos desbalanceados.\n");
    buscarNodoDesbalanceado(&alvo, &rotacao, (*pRaiz));

    if (alvo)
    {
        printf(" </> Nodo encontrado.\n");
        printf(" </> Buscando pai do nodo.\n");
        encontrarPaiNodo(&pai, &lado, alvo->numeroNodo, (*pRaiz));

        if ((*pRaiz) != alvo)
        {
            printf(" </> Pai do nodo encontrado\n\n");
            printf(" </> Pai....: %d.\n", pai->numeroNodo);
            printf(" </> Alvo...: %d.\n", alvo->numeroNodo);
            printf(" </> Lado...: %hd.\n", lado);
            printf(" </> Rotacao: %hd.\n", rotacao);

            if (lado == -1)
            {
                if (rotacao == -2)
                {
                    pai->filhoEsquerda = /* Funcao RDE */
                        printf(" </> RDE para %d que e filho de %d.\n\n", alvo->numeroNodo, pai->numeroNodo);
                }
                else if (rotacao == -1)
                {
                    pai->filhoEsquerda = /* Funcao RSE */
                        printf(" </> RSE para %d que e filho de %d.\n\n", alvo->numeroNodo, pai->numeroNodo);
                }
                else if (rotacao == 1)
                {
                    pai->filhoEsquerda = /* Funcao RSD */
                        printf(" </> RSD para %d que e filho de %d.\n\n", alvo->numeroNodo, pai->numeroNodo);
                }
                else
                {
                    pai->filhoEsquerda = /* Funcao RDD */
                        printf(" </> RDD para %d que e filho de %d.\n\n", alvo->numeroNodo, pai->numeroNodo);
                }
            }
            else if (lado == 1)
            {
                if (rotacao == -2)
                {
                    pai->filhoDireita = /* Funcao RDE */
                        printf(" </> RDE para %d que e filho de %d.\n\n", alvo->numeroNodo, pai->numeroNodo);
                }
                else if (rotacao == -1)
                {
                    pai->filhoDireita = /* Funcao RSE */
                        printf(" </> RSE para %d que e filho de %d.\n\n", alvo->numeroNodo, pai->numeroNodo);
                }
                else if (rotacao == 1)
                {
                    pai->filhoDireita = /* Funcao RSD */
                        printf(" </> RSD para %d que e filho de %d.\n\n", alvo->numeroNodo, pai->numeroNodo);
                }
                else
                {
                    pai->filhoDireita = /* Funcao RDD */
                        printf(" </> RDD para %d que e filho de %d.\n\n", alvo->numeroNodo, pai->numeroNodo);
                }
            }
        }
        else
        {
            printf(" </> O nodo desbalanceado e a raiz.\n\n");
            printf(" </> Raiz...: %d.\n", alvo->numeroNodo);
            printf(" </> Rotacao: %hd.\n", rotacao);

            if (rotacao == -2)
            {
                *pRaiz = /* Funcao RDE */
                    printf(" </> RDE para %d que e a raiz.\n\n", alvo->numeroNodo);
            }
            else if (rotacao == -1)
            {
                *pRaiz = /* Funcao RSE */
                    printf(" </> RSE para %d que e a raiz.\n\n", alvo->numeroNodo);
            }
            else if (rotacao == 1)
            {
                *pRaiz = /* Funcao RSD */
                    printf(" </> RSD para %d que e a raiz.\n\n", alvo->numeroNodo);
            }
            else
            {
                *pRaiz = /* Funcao RDD */
                    printf(" </> RDD para %d que e a raiz.\n\n", alvo->numeroNodo);
            }
        }

        printf(" </> Rotacao bem sucedido.\n");
        printf(" </> Balanceamento completo.\n");
        printf(" </> Alterando dados do(s) nodo(s).\n");
        alterarDadosNodo((*pRaiz), 1);
        printf(" </> Dados alterados.\n\n\n");
    }
    else
        printf(" </> Nao ha nodo(s) desbalanceado(s).\n");
};

// removerNodo: Determina o nodo a ser removido.

void removerNodo(Nodo **pRaiz)
{
    mostrarArvoreSimplificada((*pRaiz), (*pRaiz)->alturaNodo);

    Nodo *alvo = NULL;
    int numero;
    while (1)
    {
        printf(" <> Informe o numero do nodo: ");
        scanf("%d", &numero);
        printf("\n");
        printf(" <> Buscando nodo.\n");
        alvo = verificarExistenciaNodo((*pRaiz), numero);

        if (!alvo)
            printf(" <> Nao existe um nodo com este numero!\n\n");
        else
            printf(" <> Nodo encontrado.\n");
        break;
    }

    //remover((*pRaiz), alvo->numeroNodo); /* Funca REMOCAO */

    printf(" <> Remocao do nodo concluida.\n");

    return;
};