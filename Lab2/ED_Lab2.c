#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMTEAMS 1001
#define MAXELEMENTS 1001

typedef struct _line {
	struct _line *pre;
	int key;
	int team;
	struct _line *next;
} Line;

void initLine (Line **p) {
	*p = malloc(sizeof(Line));
	if (*p == NULL) {
		return;
	}
	(*p)->pre = NULL;
	(*p)->next = NULL;
	(*p)->key = -1;
}

void ENQUEUE (Line *p, int k, int t) {
	Line *tmp, *tmp2, *tmp3;
	tmp = p;
	tmp2 = malloc(sizeof(Line));
	tmp2->key = k;
	tmp2->team = t;
	
	if (p->pre == NULL) {
		p->next = tmp2;
		p->pre = tmp2;
		tmp2->pre = p;
		tmp2->next = NULL;
	} else {
		tmp = p->pre;
		while(tmp != p) {
			if (tmp->team == t) {
				if (tmp->next != NULL) {
					tmp3 = tmp->next;
					tmp->next = tmp2;
					tmp3->pre = tmp2;
					tmp2->next = tmp3;
					tmp2->pre = tmp;
				} else {
					tmp->next = tmp2;
					tmp2->pre = tmp;
					tmp2->next = NULL;
					p->pre = tmp2;
				}
				return;
			}
			tmp= tmp->pre;
		}
		tmp = p->pre;
		tmp->next = tmp2;
		tmp2->pre = tmp;
		tmp2->next = NULL;
		p->pre = tmp2;
	}
}

void DEQUEUE (Line *p) {
	if(p->next != NULL) {
		Line *p1, *p2;
		p1 = p->next;
		
		if(p1->next != NULL) {
			p2 = p1->next;
			p->next = p2;
			p2->pre = p;
		} else {
			p->next = NULL;
			p->pre = NULL;
		}
		
		printf("%d\n", p1->key);
	}
}

int isInTeam(int k, int t[][MAXELEMENTS], int numt) {
	for (int i = 1; i <= numt; i++) {
		for (int a = 0; a < MAXELEMENTS; a++) {
			if (t[i][a] == k) {
				return i;
			} else if (t[i][a] == -1) {
				break;
			}
		}
	}
	return 0;
}

int main () {
	
	int k = 1;
	char command[8];
	int t, nelem, elem, inteam;
	Line *pline;
	
	/* insere quantos times e começa escrevendo o número do caso se a quantidade de times não for 0*/
	while (t != 0) {
		scanf("%d", &t);
		if (t == 0) {
			break;
		}
		printf("Scenario #%d\n", k++);
		
		int loop = 1;
		int teams[NUMTEAMS][MAXELEMENTS];
		
		/* inicializa a fila */
		initLine(&pline);
		
		/* leia os integrantes dos times e associa cada elemento a um time com a matriz teams */
		for (int i = 1; i <= t; i++) {
			int a = 0;
			scanf("%d", &nelem);
			while (nelem-- > 0) {
				scanf("%d", &elem);
				teams[i][a] = elem;
				a++;
			}
			teams[i][a] = -1;
		}
		
		/* leitura dos comandos e modificação da fila */
		while (loop != 0) {
			scanf("%s", command);
			if (strcmp(command, "STOP") == 0) {
				loop = 0;
			} else if (strcmp(command, "ENQUEUE") == 0) {
				scanf("%d", &elem);
				inteam = isInTeam(elem,teams,t);
				ENQUEUE(pline, elem, inteam);	
			} else if (strcmp(command, "DEQUEUE") == 0) {
				DEQUEUE(pline);
			}
		}
		
		printf("\n");
	}
	free(pline);
}