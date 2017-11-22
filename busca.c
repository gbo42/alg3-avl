#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

char c;
int k;

int main(){
    tree *t = createTree();
    while(scanf("%c", &c) != EOF){
        scanf("%d", &k);
        switch (c) {
            case 'i':
                insertNode(t, k);
                break;
            case 'r':
                deleteNode(t, k);
                break;
            case 'b':
                findNodePrint(t, k);
                break;
        }
    }
    if(t->root){
        deleteAll(t->root);
    }
    free(t);
    return 0;
}
