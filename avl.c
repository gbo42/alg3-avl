#include "avl.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

tree *createTree(){
    tree *t = (tree *)malloc(sizeof(tree));
    t->root = NULL;
    return t;
}

node *createNode(int k){
    node *n = (node *)malloc(sizeof(node));
    if(n){
        n->p = NULL;
        n->l = NULL;
        n->r = NULL;
        n->k = k;
        n->h = 0;
    }
    return n;
}

void updateHeight(node *n){
        while(n){
            n->h = (MAX(nodeHeight(n->l), nodeHeight(n->r)) +1);
            n = n->p;
        }
}

int nodeHeight(node *n){
    if(n){
        return n->h;
    } else {
        return -1;
    }
}

void rotateLeft(tree *t, node *x){
    node *y = x->r;
    y->p = x->p;
    if(!(y->p)){
        t->root = y;
    } else {
        if(y->p->l == x){
            y->p->l = y;
        } else if(y->p->r == x){
            y->p->r = y;
        }
    }
    x->r = y->l;
    if(x->r){
        x->r->p = x;
    }
    y->l = x;
    x->p = y;
    updateHeight(x);
    updateHeight(y);
}

void rotateRight(tree *t, node *x){
    node *y = x->l;
    y->p = x->p;
    if(!(y->p)){
        t->root = y;
    } else {
        if(y->p->r == x){
            y->p->r = y;
        } else if(y->p->l == x){
            y->p->l = y;
        }
    }
    x->l = y->r;
    if(x->l){
        x->l->p = x;
    }
    y->r = x;
    x->p = y;
    updateHeight(x);
    updateHeight(y);
}

void rebalance(tree *t, node *n){
    while(n){
        updateHeight(n);
        if(nodeHeight(n->l) >= 2+nodeHeight(n->r)){
            if(nodeHeight(n->l->l) >= nodeHeight(n->l->r)){
                rotateRight(t, n);
            } else {
                rotateLeft(t, n->l);
                rotateRight(t, n);
            }
        } else if(nodeHeight(n->r) >= 2+nodeHeight(n->l)){
                if(nodeHeight(n->r->r) >= nodeHeight(n->r->l)){
                    rotateLeft(t, n);
                } else {
                    rotateRight(t, n->r);
                    rotateLeft(t, n);
                }
            }
	    n = n->p;
    }
}

void insertNode(tree *t, int k){
    printf("i %d\n", k);
    node *n = createNode(k);
    node *next = NULL;
    node *last = NULL;

	if(!t->root) {
		t->root = n;
    } else /*if (!findNode(t, k))*/{
		next = t->root;
		last = NULL;

		while(next) {
			last = next;

			if( k <= next->k ) {
				next = next->l;
			} else {
				next = next->r;
            }
		}

		if( k <= last->k ){
            last->l = n;
        } else {
            last->r = n;
        }
        n->p = last;
	}

    updateHeight(n);
    rebalance(t, n);
    printTree(t);
}

node *findNodePrint(tree *t, int k){
    printf("b %d\n", k);
    node *next = NULL;
    if(!t->root) {
		return NULL;
    } else {
		next = t->root;
        printf("%d", next->k);
		while(next) {
			if( k < next->k ) {
				next = next->l;

			} else if( k > next->k ) {
				next = next->r;

			} else if( k == next->k ) {
                printf("\n");
                return next;
			}
            printf(",%d", next->k);
		}
        printf("\n");
	}

    return NULL;
}

node *findNode(tree *t, int k){
    node *next = NULL;
    if(!t->root) {
		return NULL;
    } else {
		next = t->root;
		while(next) {
			if( k < next->k ) {
				next = next->l;

			} else if( k > next->k ) {
				next = next->r;

			} else if( k == next->k ) {
                return next;
			}
		}
	}

    return NULL;
}

void deleteNode(tree *t, int k){
    printf("r %d\n", k);
    node *n = findNode(t, k);

    if(n){
        if(n->r && n->l){
			node *temp = n->l;
            if(temp->r){
                while(temp->r){
                    temp = temp->r;
                }
                temp->p->r = temp->l;
                if(temp->l){
                    temp->l->p = temp->p;
                }
            } else if (temp->l){
                n->l = temp->l;
                n->l->p = n;
            } else {
                n->l = NULL;
            }
            n->k = temp->k;
            rebalance(t, temp->p);
            free(temp);
        } else if (n->r || n->l){
            node *temp = n->r?n->r:n->l;
            n->k = temp->k;
            n->r = temp->r;
            n->l = temp->l;
            if(temp->r){
                temp->r->p = n;
            } else if(temp->l) {
                temp->l->p = n;
            }
            rebalance(t, temp->p);
            free(temp);
        } else {
            if(n->p){
                if(n->p->r == n){
                    n->p->r = NULL;
                } else {
                    n->p->l = NULL;
                }
            } else {
                t->root = NULL;
            }
            rebalance(t, n);
            free(n);
        }
    }

    printTree(t);
}

void printTree(tree *t){
    if(t->root){
        printf("(%d,", t->root->k);
        printNode(t->root->l);
        printf(",");
        printNode(t->root->r);
        printf(")\n");
    } else {
        printf("()\n");
    }
}

void printNode(node *n){
    if(n){
        printf("(%d,", n->k);
        printNode(n->l);
        printf(",");
        printNode(n->r);
        printf(")");
    } else {
        printf("()");
    }
}

void deleteAll(node *n){
    if(n->l){
        deleteAll(n->l);
    }
    if(n->r){
        deleteAll(n->r);
    }
    free(n);
}
