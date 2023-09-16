Nodo *rotacaoDupla(Nodo *y) //realiza rotacao a direita
{
    rotacaoEsquerda(y->filhoEsquerda);
    return rotacaoDireita(y);
}