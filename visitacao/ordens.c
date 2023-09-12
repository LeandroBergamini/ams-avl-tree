void preOrdem (nodo *endNodo){
if (nodo != NULL)
{
    printf("%d", endNodo->numeroNodo);
    preOrdem(endNodo->filhoEsquerda);
    preOrdem(endNodo->filhoDireita);
}
return;
}

void emOrdem (nodo *endNodo){
if (nodo != NULL)
{
    emOrdem(endNodo->filhoEsquerda);
    printf("%d", endNodo->numeroNodo);
    emOrdem(endNodo->filhoDireita);
}   
return; 
}

void posOrdem (nodo *endNodo){
if (nodo != NULL)
{
    posOrdem(endNodo->filhoEsquerda);
    posOrdem(endNodo->filhoDireita);
    printf("%d", endNodo->numeroNodo);
}   
return; 
}