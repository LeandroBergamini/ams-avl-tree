void preOrdem (Nodo *endNodo){
if (endNodo != NULL)
{
    printf("%d", endNodo->numeroNodo);
    preOrdem(endNodo->filhoEsquerda);
    preOrdem(endNodo->filhoDireita);
}
return;
}

void emOrdem (Nodo *endNodo){
if (endNodo != NULL)
{
    emOrdem(endNodo->filhoEsquerda);
    printf("%d", endNodo->numeroNodo);
    emOrdem(endNodo->filhoDireita);
}   
return; 
}

void posOrdem (Nodo *endNodo){
if (endNodo != NULL)
{
    posOrdem(endNodo->filhoEsquerda);
    posOrdem(endNodo->filhoDireita);
    printf("%d", endNodo->numeroNodo);
}   
return; 
}