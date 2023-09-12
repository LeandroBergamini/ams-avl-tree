
Nodo *rotacaoSimples(Nodo *y) //realiza rotacao a direita
{
    Nodo *backup = y->filhoEsquerda;
    y->filhoEsquerda = backup->filhoDireita;
    backup->filhoDireita-> = y;
    return backup;
}

Nodo *rotacaoDupla(Nodo *y) //realiza rotacao a direita
{
    rotacaoEsquerda(y->filhoEsquerda);
    return rotacaoDireita(y);
}




