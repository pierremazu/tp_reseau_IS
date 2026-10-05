#include <stdio.h>
#include <stdlib.h>

typedef struct liste_chainee{
    int head;
    struct liste_chainee* tail;
}liste_chainee;

void push(liste_chainee** l, int val){
    liste_chainee* chainon = malloc(sizeof(liste_chainee));
    if(!chainon) exit(EXIT_FAILURE);
    chainon->head = val;
    chainon->tail = *l;
    *l = chainon;
}

int pop(liste_chainee** l){
    liste_chainee* l_temp = (*l)->tail;
    int val = (*l)->head;
    free(*l);
    *l = l_temp;
    return val;
}

int length(liste_chainee* l){
    int n = 0;
    while(l!=NULL){
        n++;
        l = l->tail;
    }
    return n;
}

liste_chainee* liste_n_premier_entier(int n){
    liste_chainee* result = NULL;
    while(n>=0){
        push(&result,n);
        n--;
    }
    return result;
}

void print_list(liste_chainee* l){
    while(l!=NULL){
        printf("<%p>:%i\n",l,l->head);
        l = l->tail;
    }
}

int main(void){
    liste_chainee* ma_liste = liste_n_premier_entier(5);
    printf("longueur : %d\n",length(ma_liste));
    print_list(ma_liste);
    pop(&ma_liste);
    print_list(ma_liste);
}