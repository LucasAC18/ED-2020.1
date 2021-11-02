#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 8

void init(int* V[], int *nelem, int *tam) {
	*tam = TAM;
	*V = (int *) malloc((*tam)*sizeof(int));
	if (*V == NULL) {
		return;
	} else {
		*nelem = 0;
	}
}

void overflow(int *V[], int *tam) {
	int *tmp = (int *) malloc((*tam)*2*sizeof(int));
	if (tmp == NULL) {
		return;
	}
	for (int i = 0; i <= (*tam-1); i++) {
		tmp[i] = (*V)[i];
	}
	*tam = *tam*2;
	free(*V);
	*V = tmp;
}

void insere(int *V[], int x, int *nelem, int *tam) {
	(*V)[*nelem] = x;
	(*nelem)++;
	if (*nelem == *tam) {
		overflow(V, tam);
	}
}

void merge(int V[], int inicio, int meio, int fim) {
	int i = inicio;
	int j = meio+1;
    int *aux;
	int cont = 0;
	int tamanho = fim-inicio+1;
    aux = (int*)malloc(tamanho * sizeof(int));

    while(i <= meio && j <= fim){
        if(V[i] < V[j]) {
            aux[cont] = V[i];
            i++;
        } else {
            aux[cont] = V[j];
            j++;
        }
        cont++;
    }

    while(i <= meio){
        aux[cont] = V[i];
        cont++;
        i++;
    }

    while(j <= fim) {
        aux[cont] = V[j];
        cont++;
        j++;
    }

    for(cont = inicio; cont <= fim; cont++){
        V[cont] = aux[cont-inicio];
    }
    free(aux);
}

void mergesort(int V[], int inicio, int fim){
    if (inicio < fim) {
        int meio = (fim+inicio)/2;

        mergesort(V, inicio, meio);
        mergesort(V, meio+1, fim);
        merge(V, inicio, meio, fim);
    }
}

void quicksort(int V[], int inicio, int fim) {
	int i = inicio;
	int f = fim;
	int pivo = V[(inicio + fim)/2];
	int tmp;
	
	while(i <= f) {
		while (V[i] < pivo && i < fim) {
			i++;
		}
		
		while (V[f] > pivo && f > inicio) {
			f--;
		}
		
		if (i <= f) {
			tmp = V[i];
			V[i] = V[f];
			V[f] = tmp;
			i++;
			f--;
		}
	}
	
	if (f > inicio) {
		quicksort(V, inicio, f+1);
	}
	
	if (i < fim) {
		quicksort(V, i, fim);
	}
}

void bubblesort(int V[], int n){ 
    int tmp;
	
	if (n < 1) {
		return;
	}
 
    for (int i = 0; i < n; i++) {
		if (V[i] > V[i+1]) {
			tmp = V[i];
			V[i] = V[i+1];
			V[i+1] = tmp;
		}
	}
	bubblesort(V, n-1);
}

int main (int argc, char *argv[]) {
	
	int x;
	int *nums;
	int tam;
	int nelem;
	
	init(&nums, &nelem, &tam);
	
	
	while (!feof(stdin)) {
		if(scanf("%d", &x) != 0) {
			insere(&nums, x, &nelem, &tam);	
		} else {
			break;
		}
	}

	if (argc > 1 && strcmp(argv[1],"-m") == 0) {
		mergesort(nums, 0, nelem-2);
		for (int i = 0; i < nelem-1; i++) {
			printf("%d\n", nums[i]);
		}
	} 
	else if (argc > 1 && strcmp(argv[1],"-q") == 0) {
		quicksort(nums, 0, nelem-2);
		for(int i = 0; i < nelem-1; i++) {
			printf("%d\n", nums[i]);
		}
	} 
	else {
		bubblesort(nums, nelem-2);
		for(int i = 0; i < nelem-1; i++) {
			printf("%d\n", nums[i]);
		}
	}
}