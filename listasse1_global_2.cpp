#include <stdio.h>
#include <conio.h>
#include <malloc.h>

void insere_direita(int valor, int *sinal);
void mostra_lista();
void libera_lista();
void substitui(int valor);
struct nodo *maior_lista();
void troca_segundo_ultimo();
void insere_antes_quarto(int valor);
int remove_esquerda();
int remove_direita();
int remove_segundo();
void remova_primeiro_par();
void inverte_maior_menor();

struct nodo
{
	int dados;
	struct nodo *prox;
} *inicio = NULL, *fim;

void inverte_maior_menor()
{
	struct nodo *aux, *maior, *menor;
	aux = inicio;
	maior->dados = aux->dados;
	menor->dados = aux->dados;
	if (aux != NULL)
	{
		while (aux != NULL)
		{
			if (aux->dados > maior->dados)
			{
				maior->dados = aux->dados;
			}
			if (aux->dados < menor->dados)
			{
				menor->dados = aux->dados;
			}
			
				aux = aux->prox;
			
		}

		aux->dados = maior->dados;
		maior->dados = menor->dados;
		menor->dados = aux->dados;
	}
	else
		printf("A lista não possui 2 nodos!");
}

void remova_primeiro_par()
{
	struct nodo *aux, *ant;
	int par;
	if (inicio->prox != NULL)
	{
		aux = inicio;
		ant = inicio;
		while (aux->prox != NULL)
		{
			if (aux->dados % 2 == 0)
			{

				ant->prox = aux->prox;
				free(aux);
				break;
			}
			if (aux != NULL)
			{
				ant = aux;
				aux = aux->prox;
			}
		}
	}
}

int remove_segundo()
{
	int valor = 0;
	struct nodo *aux;
	aux = inicio;
	if (aux != NULL && aux->prox != NULL)
	{
		aux = aux->prox;
		valor = aux->dados;
		inicio->prox = aux->prox;
		if (aux == fim)
			fim = inicio;
		free(aux);
	}
	else
		printf("A lista não possui 2 nodos!");
	return valor;
}

int remove_direita()
{
	struct nodo *p, *aux;
	int valor = 0;
	if (inicio == NULL)
		return 0;
	else
	{
		if (inicio->prox == NULL)
		{
			valor = inicio->dados;
			free(inicio);
			fim = inicio = NULL;
		}
		else
		{
			aux = inicio;
			while (aux->prox != NULL) //para no ultimo
			{
				p = aux;
				aux = aux->prox;
			}
			valor = aux->dados;
			p->prox = NULL;
			fim = p;
			free(aux);
			return valor;
		}
	}
}

int remove_esquerda()
{
	struct nodo *aux;
	int valor = 0;
	if (inicio == NULL)
		return 0;
	else
	{
		aux = inicio;
		valor = aux->dados;
		inicio = inicio->prox;
		if (inicio == NULL)
			fim = NULL;
		free(aux);
	}
	return valor;
}

void troca_segundo_ultimo()
{
	int troca;
	if (inicio != NULL && inicio->prox != NULL && inicio->prox->prox != NULL)
	{
		troca = inicio->prox->dados;
		inicio->prox->dados = fim->dados;
		fim->dados = troca;
	}
	else
		printf("A lista não contem pelo menos 3 elementos!\n");
}

void insere_antes_quarto(int valor)
{
	int c = 1;
	struct nodo *p, *novo, *aux;
	aux = inicio;
	while (aux != NULL && c < 4)
	{
		p = aux;
		aux = aux->prox;
		c++;
	} // p sai no terceiro e aux no quarto
	if (c == 4)
	{
		novo = (struct nodo *)malloc(sizeof(struct nodo));
		if (novo != NULL)
		{
			novo->dados = valor;
			p->prox = novo;
			novo->prox = aux;
		}
	}
	else
		printf("A lista não contem pelo menos 4 elementos!\n");
}

void insere_direita(int valor, int *sinal)
{
	struct nodo *aux;
	aux = (struct nodo *)malloc(sizeof(struct nodo));
	if (aux)
	{
		aux->dados = valor;
		aux->prox = NULL;
		if (inicio == NULL)
			inicio = aux;
		else
			fim->prox = aux;
		fim = aux;
		*sinal = 1;
	}
	else
		*sinal = 0;
}

void mostra_lista()
{
	struct nodo *p;
	p = inicio;
	while (p)
	{
		printf("Elemento= %i\n", p->dados);
		p = p->prox;
	}
	printf("Fim da lista\n");
	getch();
}

void libera_lista()
{
	struct nodo *p;
	p = inicio;
	while (p)
	{
		inicio = inicio->prox;
		free(p);
		p = inicio;
	}
}

void substitui(int valor)
{
	struct nodo *aux = inicio;
	while (aux != NULL && aux->dados != valor)
		aux = aux->prox;
	if (aux != NULL)
	{
		printf("Digite um novo valor:");
		scanf("%i", &aux->dados);
		fflush(stdin);
	}
	else
		printf("Elemento não encontrado");
}

struct nodo *maior_lista()
{
	struct nodo *p, *d;
	int m;
	p = inicio;
	m = p->dados;
	while (p)
	{
		if (p->dados > m)
		{
			m = p->dados;
			d = p;
		}
		p = p->prox;
	}
	return d;
}

int main()
{
	int valor, i, ok;
	struct nodo *aux;
	printf("Digite 5 valores:\n");
	for (i = 1; i <= 5; i++) // insere 5 elementos pelo inicio da lista
	{
		scanf("%i", &valor);
		fflush(stdin);
		insere_direita(valor, &ok);
		if (!ok)
		{
			printf("Erro ao inserir este valor!\n");
			getch();
		}
	}
	mostra_lista();

	inverte_maior_menor();
	mostra_lista();

	//remova_primeiro_par();
	//mostra_lista();

	//   troca_segundo_ultimo();
	//   mostra_lista();

	//   insere_antes_quarto (99);
	//   mostra_lista();

	//   valor = remove_esquerda();
	//   printf("Valor removido %i\n", valor);
	//   mostra_lista();

	//   valor = remove_direita();
	//   printf("Valor removido %i\n", valor);
	//   mostra_lista();

	//   valor = remove_segundo();
	//   printf("Valor removido %i\n", valor);
	//   mostra_lista();

	//printf("Digite o valor a substituir:");
	//scanf("%i", &valor); fflush(stdin);
	//substitui(valor);
	//mostra_lista();

	//aux = maior_lista();
	//printf("Maior valor da lista: %i\n", aux->dados);
	//printf("FIM!!!\n");

	libera_lista();
	getch();
}
