#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
#define RANGE 100

/* Estrutura para nós da árvore */
typedef struct node{
  struct node *esq;
  struct node *dir;
  int val;
  int altura;
}node;

int altura(node *raiz){
  if(raiz == NULL){
    return 0;
  }
  return raiz->altura;
}

int balance(node *raiz){
  if(raiz == NULL){
    return 0;
  }
  return altura(raiz->esq) - altura(raiz->dir);
}

int max(int a, int b){
  if(a>b){
    return a;
  }
    return b;
}

void rotateRight(node *p){
  node *q, *temp;

  q = p->esq;
  temp = q->dir;
  q->dir = p;
  p->esq = temp;
  p = q;
}

void rotateLeft(node *p){
  node *q, *temp;

  q = p->dir;
  temp = q->esq;
  q->esq = p;
  p->dir = temp;
  p = q;
}

void rotateLeftRight(node *p){
  rotateLeft(p->esq);
  rotateRight(p);
}

void rotateRightLeft(node *p){
  rotateRight(p->dir);
  rotateLeft(p);
}

void insert(node *raiz, int value ) {
	node *novo = NULL;
	node *next = NULL;
	node *last = NULL;
    int b;

	if( raiz == NULL ) {
        novo = (node *) malloc (sizeof(node));
        novo->val = value;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
		raiz = novo;
	} else {
		next = raiz;
		last = NULL;

		while( next != NULL ) {
			last = next;
			if( value <= next->val ) {
				next = next->esq;
			} else if( value > next->val ) {
				next = next->dir;
			}
		}

        novo = (node *) malloc (sizeof(node));
        novo->val = value;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;

		if( value < last->val ) last->esq = novo;
		if( value > last->val ) last->dir = novo;

        if(raiz->val != value){
          raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));
          b = balance(raiz);

          if(b > 1 && (raiz->esq->val > value)){
            rotateRight(raiz);
          }
          else if(b < -1 && (raiz->dir->val < value)){
            rotateLeft(raiz);
          }
          else if(b > 1 && (raiz->esq->val < value)){
            rotateLeftRight(raiz);
          }
          else if(b < -1 && (raiz->dir->val > value)){
            rotateRightLeft(raiz);
          }
        }
	}

}

node *destroyTree(node *raiz){
  if(raiz->dir != NULL){
    destroyTree(raiz->dir);
  }
  if(raiz->esq != NULL){
    destroyTree(raiz->esq);
  }
  free(raiz);
  return NULL;
}

void printInOrderTree(node *raiz){
  if(raiz != NULL){
    printInOrderTree(raiz->esq);
    printf("%d \n", raiz->val);
    printInOrderTree(raiz->dir);
  }
}

int main(void){
  node *raiz = (node *) malloc (sizeof(node));
  int i, t;
  srand((unsigned)time(NULL));
  for(i = 0; i < MAX; i++){
      t = rand() % RANGE;
    insert(raiz, t);
  }
  printInOrderTree(raiz);
  destroyTree(raiz);
  return 0;
}
