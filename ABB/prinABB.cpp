#include <iostream>
#include <queue>
#include <stack>
using namespace std;

typedef int Elem;

typedef struct no
{
	struct no* esq;
	Elem info;
	struct no* dir;
}*Arvb;

Arvb novono(Arvb , Elem , Arvb );
void Tins(Arvb *, Elem );
void preordem(Arvb );
void emordem(Arvb );
void posordem(Arvb );
void emnivel(Arvb );
Arvb find(Arvb , Elem );
void folhas(Arvb T);
Arvb maior(Arvb);
Arvb alt(Arvb T);
int max(int, int);
void iterativo(Arvb);
int nos(Arvb);
void posOrdemPilha(Arvb);
char findC(Arvb, Elem);
void del(Arvb T, Elem x);
Arvb remmaior(Arvb* );
char rem(Arvb* T, Elem x);
void apagatodos(Arvb*);
char eb(Arvb);

void main()
{
	Arvb T1 = NULL;
	Tins(&T1, 5);
	Tins(&T1, 3);
	//Tins(&T1, 1);
	//Tins(&T1, 4);
	Tins(&T1, 8);

	if (eb(T1))
		cout << "E estritamente binaria" << endl;
	else
		cout << "Nao e estritamente binaria" << endl;
}

char eb(Arvb T)
{
	/*if (T->dir and T->esq and eb(T->esq) and eb(T->dir))
		return 0;
	if (not T->dir and not T->esq)
		return 1;*/
	return (not T->dir and not T->esq)
		or (T->dir and T->esq and eb(T->esq) and eb(T->dir));
}

void apagatodos(Arvb* T)
{
	if (*T == NULL) return;
	apagatodos(&(*T)->esq);
	apagatodos(&(*T)->dir);
	delete *T;
	*T = NULL;
}

void posOrdemPilha(Arvb T)
{
	stack <Arvb> p;
	stack<int> c;
	if (T != NULL)
	{
		p.push(T);
		while (not p.empty())
		{
			T = p.top();
			p.pop();
			c.push(T->info);
			if (T->esq)
				p.push(T->esq);
			if (T->dir)
				p.push(T->dir);
		}
		while (not c.empty())
		{
			cout << c.top() << " ";
			c.pop();
		}
	};
}

int nos(Arvb T)
{
	if (T!=NULL)
	{
		return 1 + nos(T->esq) + nos(T->dir);
	}
	else
		return 0;

}

void iterativo(Arvb T)
{
	stack <Arvb> p;
	while (T != NULL or not p.empty())
	{
		if (T != NULL)
		{
			p.push(T);
			T = T->esq;
		}
		else
		{
			T = p.top();
			p.pop();
			cout << T->info << " ";
			T = T->dir;
		}
	}
}

int max(int D, int E)
{
	if (E >= D)
		return E;
	return D;
}

Arvb alt(Arvb T)
{
	if (!T) return 0;
	return 1 + max(alt(T->esq), alt(T->dir));
}

Arvb find(Arvb T, Elem X)
{
	if (T == NULL) return NULL;
	if (X < T->info)
		return find(T->esq, X);
	else
		if (X > T->info)
			return find(T->dir, X);
		else
			return T;
}

Arvb maior(Arvb T)
{
	if (T->dir != NULL)
		return maior(T->dir);
	else
		return T;
}

Arvb novono(Arvb e, Elem x, Arvb d)
{
	Arvb aux = new no;
	aux->esq = e;
	aux->dir = d;
	aux->info = x;
	return aux;
}

void Tins(Arvb* T, Elem x)
{
	if (*T == NULL)
		*T = novono(NULL, x, NULL);
	else
	{
		if (x < (*T)->info)
			Tins(&((*T)->esq), x);
		else
			if (x > (*T)->info)
				Tins(&((*T)->dir), x);
	}
}

void preordem(Arvb T)
{
	if (T != NULL)
	{
		cout << T->info << " ";
		preordem(T->esq);
		preordem(T->dir);
	}
}

void folhas(Arvb T)
{
	if (T != NULL)
	{
		if(T->dir == NULL && T->esq == NULL)
			cout << T->info << ' ';
		folhas(T->esq);
		folhas(T->dir);
	}
}

void emordem(Arvb T)
{
	if (T != NULL)
	{
		emordem(T->esq);
		cout << T->info << ' ';
		emordem(T->dir);
	}
}

void posordem(Arvb T)
{
	if (T != NULL)
	{
		posordem(T->esq);
		posordem(T->dir);
		cout << T->info << ' ';
	}
}

void emnivel(Arvb T)
{
	queue <Arvb> fila;
	Arvb p;
	if (T != NULL)
	{
		fila.push(T);
		while (!fila.empty())
		{
			p = fila.front();
			fila.pop();
			cout << p->info << ' ';
			if (p->esq != NULL)
				fila.push(p->esq);
			if (p->dir != NULL)
				fila.push(p->dir);
		}
	}
}

char findC(Arvb T, Elem x)
{
	if (T == NULL) return 0;
	if (T->info == x)return 1;
	else
		if (x < T->info) findC(T->esq, x);
		else
		{
			return findC(T->dir, x);
		}
}

void del(Arvb T, Elem x)
{
	Arvb aux = NULL;

}

Arvb remmaior(Arvb* P)
{

	if (*P == NULL) abort();
	while ((*P)->dir != NULL)
	{
		P = &(*P)->dir;
	}
	Arvb aux = *P;
	*P = aux->esq;
	return aux;
}

char rem(Arvb* T, Elem X)
{
	if (!*T) return 0;
	if (X == (*T)->info)
	{
		Arvb aux = *T;
		if (aux->esq == NULL)
			*T = aux->dir;
		else
			if (aux->dir == NULL)
				*T = aux->esq;
			else //existe sub árvore esquerda e direita
			{
				aux = remmaior(&aux->esq);
				(*T)->info = aux->info;
			}
		delete aux;
		return 1;
	}
	else
		if (X < (*T)->info)
			return rem(&(*T)->esq, X);
		else
			return rem(&(*T)->dir, X);
}