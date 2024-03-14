#include <iostream>

using namespace std;

typedef struct no {
	char info;
	char fb;
	struct no* esq, * dir;
}*AVL;

void ins_avl(AVL*, char, char*);
void RD(AVL*);
void RE(AVL*);
void NP(AVL);

int main(void)
{
	char H;
	AVL T1 = NULL;
	ins_avl(&T1, 20, &H);
	ins_avl(&T1, 10, &H);
	ins_avl(&T1, 40, &H);
	ins_avl(&T1, 30, &H);
	ins_avl(&T1, 50, &H);
	ins_avl(&T1, 25, &H);
	NP(T1);
	return 1;
}


void ins_avl(AVL* T, char X, char* H)
{
	if (*T == NULL)
	{
		*T = new no;
		(*T)->info = X;
		(*T)->esq = (*T)->dir = NULL;
		(*T)->fb = 0;
		*H = 1;
	}
	else
		if (X < (*T)->info)
		{
			ins_avl(&(*T)->esq, X, H);
			if (*H)
			{
				switch ((*T)->fb)
				{
				case 1: (*T)->fb = 0; *H = 0; break;
				case 0: (*T)->fb = -1; break;
				case -1:RD(T); *H = 0; break;
				}
			}
		}
		else
			if (X > (*T)->info)
			{
				ins_avl(&(*T)->dir, X, H);
				if (*H)
				{
					switch ((*T)->fb)
					{
					case -1: (*T)->fb = 0; *H = 0; break;
					case 0: (*T)->fb = 1; break;
					case 1: RE(T); *H = 0; break;
					}
				}
			}
}

void RD(AVL* T)
{
	AVL pB = (*T)->esq;
	if (pB->fb == -1) //rotação simples
	{
		(*T)->esq = pB->dir;
		pB->dir = *T;
		(*T)->fb = 0;
		*T = pB;
	}
	else //rotação dupla
	{
		AVL pC = pB->dir;
		pB->dir = pC->esq;
		pC->esq = pB;
		(*T)->esq = pC->dir;
		pC->dir = *T;
		if (pC->fb == -1) (*T)->fb = 1; else (*T)->fb = 0;
		if (pC->fb == 1) pB->fb = -1; else pB->fb = 0;
		*T = pC;
	}
	(*T)->fb = 0;
}

void RE(AVL* T)
{
	AVL pB = (*T)->dir;
	if (pB->fb == 1) //rotação simples
	{
		(*T)->dir = pB->esq;
		pB->esq = *T;
		(*T)->fb = 0;
		*T = pB;
	}
	else //rotação dupla
	{
		AVL pC = pB->esq;
		pB->esq = pC->dir;
		pC->dir = pB;
		(*T)->dir = pC->esq;
		pC->esq = *T;
		if (pC->fb == 1) (*T)->fb = -1; else (*T)->fb = 0;
		if (pC->fb == -1) pB->fb = 1; else pB->fb = 0;
		*T = pC;
	}
	(*T)->fb = 0;
}

void NP(AVL T) //notação do ponto
{
	if (T != NULL)
	{
		cout << (int)T->info << " ";
		NP(T->esq);
		NP(T->dir);
	}
	else
		cout << ".";
}