Nodo *rotacaoSimplesEsquerda(Nodo *nodo)
{
    Nodo *auxiliar = nodo->filhoDireita;
    nodo->filhoDireita = auxiliar->filhoEsquerda;
    backup->filhoEsquerda = nodo;
    return auxiliar;
}
