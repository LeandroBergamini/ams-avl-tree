Nodo *rde(Nodo *nodo)
{
    rotacaoDireita(nodo->filhoDireita);
    return rotacaoEsquerda(nodo);
}

// Rotação Dupla a Esquerda