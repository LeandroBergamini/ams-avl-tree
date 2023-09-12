short inserirNodo(Nodo *novoNodo, Nodo **ponteiroNodo, Nodo *nodo)
{
    if ((*ponteiroNodo)) {

        if (novoNodo->numeroNodo < nodo->numeroNodo) {

            if (nodo->filhoEsquerda) {
                return inserirNodo(novoNodo, ponteiroNodo, nodo->filhoEsquerda);
            } else {
                nodo->filhoEsquerda = novoNodo;
                return nodo->nivelNodo;
            }

        } else {

            if (nodo->filhoDireita) {
                return inserirNodo(novoNodo, ponteiroNodo, nodo->filhoDireita);
            } else {
                nodo->filhoDireita = novoNodo;
                return nodo->nivelNodo;
            }

        }

    } else {
        (*ponteiroNodo) = novoNodo;
        return 0;

    }
}