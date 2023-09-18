Nodo *rse(Nodo *nodo)
{
    Nodo *auxiliar = nodo->filhoDireita;
    nodo->filhoDireita = backup->filhoEsquerda;
    backup->filhoEsquerda-> = nodo;
    return auxiliar;
}

// Rotação Simples a Esquerda