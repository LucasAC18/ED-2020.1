#include<stdio.h>
#include<stdlib.h>

typedef struct _no {
	int chave;
	struct _no *esq;
	struct _no *dir;
	int altura;
} No;

int qualAltura (No *n) {
	if (n == NULL) return 0;
	return n->altura;
}

void atualizaAltura (No *n) {
	int e = qualAltura(n->esq);
	int d = qualAltura(n->dir);
	int max = (e > d)? e : d;
	
	n->altura = max + 1;
}

void preOrdem(No *raiz) {
	if (raiz == NULL) return;
	printf("%d\n", raiz->chave);
	preOrdem(raiz->esq);
	preOrdem(raiz->dir);
}

No* rotacaoEsquerda(No *n) {
	No* filho = n->dir;
	No* T = filho->esq;
	
	filho->esq = n;
	n->dir = T;
	
	atualizaAltura(n);
	atualizaAltura(filho);
	
	return filho;
}

No* rotacaoDireita(No *n) {
	No* filho = n->esq;
	No* T = filho->dir;
	
	filho->dir = n;
	n->esq = T;
	
	atualizaAltura(n);
	atualizaAltura(filho);
	
	return filho;
}

No* insereNo (No *t, int k) {
	
	/* insere o novo nó como uma árvore binária de busca. Caso a raíz esteja vazia simplesmente adiciona o novo nó e retorna */
	if (t == NULL) {
		No *n = (No*) malloc(sizeof(No));
		n->dir = NULL;
		n->esq = NULL;
		n->altura = 1;
		n->chave = k;
		return n;
	} else if (k < t->chave) {
		t->esq = insereNo(t->esq, k);
	} else if (k >= t->chave) {
		t->dir = insereNo(t->dir, k);
	}
	
	/* atualiza a altura do pai */
	atualizaAltura(t);
	
	/* checa a altura de cada filho */
	int e = qualAltura(t->esq);
	int d = qualAltura(t->dir);
	
	/* checa o balanceamento da árvore. A diferença entre as alturas dos filhos precisa ser entre -1 e 1 */
	int balanceamento = e - d;
	
	if (balanceamento < -1) {
		if (k < t->dir->chave) {
			t->dir = rotacaoDireita(t->dir);
		}
		return rotacaoEsquerda(t);
	} else if (balanceamento > 1) {
		if (k >= t->esq->chave) {
			t->esq = rotacaoEsquerda(t->esq);
		}
		return rotacaoDireita(t);
	}
	
	return t;
}

int main () {
	No* raiz = NULL;
	int x;
	
	while(scanf("%d", &x) != EOF) {
		raiz = insereNo(raiz, x);
	}
	
	preOrdem(raiz);
	
	free(raiz);
	return 0;
}