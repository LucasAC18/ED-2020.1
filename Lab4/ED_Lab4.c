#include <stdio.h>
#include <stdlib.h>

void init (int n, int** conj, int** rank) {
	*conj = malloc((n+1)*sizeof(int));
	*rank = malloc((n+1)*sizeof(int));
	
	for (int index=1; index <= n; index++) {
		(*conj)[index] = index;
		(*rank)[index] = 0;
	}
}

int find (int a, int conj[]) {
	if (a != conj[a]) {
		conj[a] = find(conj[a], conj);
	}
	return conj[a];
}

void une (int a, int b, int conj[], int rank[]) {
	a = find(a, conj);
	b = find(b, conj);
	
	if (a != b) {
		if (rank[a] <= rank[b]) {
			conj[a] = conj[b];
			if (rank[a] == rank[b]) {
				rank[b]++;
			}
		}
		else {
			conj[b] = conj[a];
		}
	}
}

void bubblesort(int V[], int n){ 
    int tmp;
	
	if (n < 1) {
		return;
	}
 
    for (int i = 1; i < n; i++) {
		if (V[i] > V[i+1]) {
			tmp = V[i];
			V[i] = V[i+1];
			V[i+1] = tmp;
		}
	}
	bubblesort(V, n-1);
}

int main () {
	int m,n,i,j,nelem,menor;
	int c = 1;
	int* conj;
	int* rank;
	
	scanf("%d", &n);
	scanf("%d", &m);
	
	/* Repete até que os valores de n e m ambos forem 0 */	
	while(n != 0 && m != 0) {
		
		/* inicializa o conjunto com os n elementos dados e define o rank de cada um dos elementos com 0 */
		init(n, &conj, &rank);
		
		/* pelas próximas m linhas, leia os valores de i e j e una esses alunos */
		for (int index=1; index <= m; index++) {
			scanf("%d", &i);
			scanf("%d", &j);
			
			une(i, j, conj, rank);
		}	
		
		/* para descobrir o número de religiões usarei um sort nos conjuntos e contarei quantos valores diferentes o array possui */
		bubblesort(conj, n);
		menor = conj[1];
		nelem = 1;
		for (int index = 1; index <= n; index++) {
			if(conj[index] != menor) {
				menor = conj[index];
				nelem++;
			}
		}
		
		printf("Case %d: %d\n", c++, nelem);
		
		/* Lê os valores de n e m novamente */
		scanf("%d", &n);
		scanf("%d", &m);
	}
}