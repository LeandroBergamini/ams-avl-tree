short fatorDeBalanceamento(Nodo *nodo)
{
    if nodo
        ->filhoEsquerda
            nodo->alturaEsquerda = nodo->filhoEsquerda->alturaNodo;
    else
        nodo->alturaEsquerda = 0;

    if nodo
        ->filhoDireita
            nodo->alturaEsquerda = nodo->filhoDireita->alturaNodo;
    else
        nodo->alturaDireita = 0;

    return nodo->alturaDireita - nodo->alturaEsquerda; // calculo do FB
}