#include <stdio.h>
#include <conio.h>
#include <malloc.h>
//Matheus Castro
struct nodo {
		int dados;
		struct nodo *prox;
	};
struct header {
		struct nodo *iniciol;	// primeiro nodo
		int qtde;			    //quantidade de nodos da lista
		struct nodo *fiml;		// �ltimo nodo
	};

void cria_header (struct header **lista, int *status);
void insere_esquerda (struct header *lista, int valor, int  *status);
void insere_direita(struct header *lista, int valor, int *status);
int remove_direita(struct header *lista , int *status);
int remove_esquerda( struct header *lista, int *status);
void mostra_lista(struct header *lista);
void libera_lista(struct header *lista);
void insere_antes_do_terceiro(struct header *lista, int valor);
void remove_quinto_elemento(struct header *lista);

void remove_quinto_elemento(struct header *lista)
{
	struct nodo  *aux, *quartoNodo; int contador;
	contador = 1;
if (lista->qtde >= 5)
{
	aux = lista->iniciol;
	while (contador != 5)
	{
		if (contador == 4)
		{
			quartoNodo = aux;
		}
		aux= aux->prox;
		contador++;
	}
	if (aux->prox == NULL)
	{
		lista->fiml = quartoNodo;
		quartoNodo->prox = NULL;
	}else
	{
		quartoNodo->prox = aux->prox;
	}
	free(aux);
	lista->qtde--;
	
}else
{
	printf("não tem 5 nodos\n");
}


}

void insere_antes_do_terceiro(struct header *lista, int valor)
{
	if (lista->qtde >= 3)
	{
     	struct nodo *novoNodo, *aux, *segundoNodo;
		novoNodo= (struct nodo *) malloc(sizeof(struct nodo));
		novoNodo->dados = valor;
		aux = lista->iniciol->prox->prox;
		novoNodo->prox = aux;
		segundoNodo = lista->iniciol->prox;
		segundoNodo->prox = novoNodo;
		lista->qtde++;
	}else
	{
		printf("não tem 3 nodos\n");
	}
	
	
}


void cria_header (struct header **lista, int *status) 
{
	*lista = (struct header *) malloc(sizeof(struct header));
	if (*lista == NULL)  
		*status = 0;
else	{
	   (*lista)->iniciol = NULL;
	   (*lista)->qtde = 0;
	   (*lista)->fiml = NULL;
		   *status = 1;
 		}

}

void insere_esquerda (struct header *lista, int valor, int  *status)
{
     struct nodo *p;
	p= (struct nodo *) malloc(sizeof(struct nodo));
	if (p == NULL)
    *status = 0;
    else	{
	   p->dados = valor;
	   p->prox = lista->iniciol;
	   lista->iniciol = p;
	   lista->qtde++;
       *status = 1;
	   if (lista->fiml == NULL) 	//Se � o primeiro nodo inserido na lista ...
	   	lista->fiml = p;
		}
}

void insere_direita(struct header *lista, int valor, int *status)
{
	struct nodo *p;
	p=(struct nodo *) malloc (sizeof(struct nodo));
	if (p==NULL) *status=0;
	else {
		p->dados = valor;
		p->prox = NULL;
		if (lista->iniciol == NULL)
			lista->iniciol = p;
		else
			lista->fiml->prox = p;
		lista->fiml = p;
		lista->qtde++;
		*status = 1;
	}
}
int remove_direita (struct header *lista , int *status)
{
     struct nodo *p;
     int valor=0;
      if (lista->qtde == 0) 	//Se lista vazia...
	 	*status = 0;
	else 	{
                        valor = lista->fiml->dados;
			if (lista->qtde == 1) 	//Se a lista tem apenas um nodo
				 lista->iniciol = NULL;
			else	{
					p = lista->iniciol;
					while (p->prox != lista->fiml)
						p=p->prox;
					p->prox = NULL;
				}
			free (lista->fiml);
			lista->qtde--;
			*status = 1;
			if (lista->qtde == 0)	//Se a lista ficou vazia ...
				lista->fiml = NULL;
			else 
         lista->fiml = p;
	}
       return valor;
}

int remove_esquerda( struct header *lista, int *status)
{
	struct nodo *p;
	int valor=0;
	if(lista->qtde == 0) *status = 0;
	else {
		valor = lista->iniciol->dados;
		if (lista->qtde == 1) lista->fiml = NULL;
		p=lista->iniciol;
		lista->iniciol = p->prox;
		free (p);
		lista->qtde--;
		*status = 1;
	}
	return valor;
}
void libera_lista (struct header *lista)
{ 
struct nodo *p;
	p = lista->iniciol;
	while (p) {
		lista->iniciol = lista->iniciol->prox;
		free(p);
		p = lista->iniciol;
	
	}
}

void mostra_lista (struct header *lista)
{ 
struct nodo *aux;
    aux = lista->iniciol;
	while (aux) {
       printf("Elemento: %i\n", aux->dados);
       aux = aux->prox;
	}
  getch();
}



int main()
{
   struct header *l;
   int valor, ok;
   cria_header(&l,&ok);
   if (ok == 0){
      printf("Descritor n�o cruado!\n"); getch();
      return 1;
   }
   printf("Digite um valor ou zero: ");
   scanf("%i", &valor); fflush(stdin);
   while (valor != 0)
   {
         insere_direita(l, valor, &ok);
         if (ok == 0) return 1;
         printf("Digite outro valor ou zero: ");
         scanf("%i", &valor); fflush(stdin);
   }
   
   mostra_lista(l);
   //Chamar as novas fun��es aqui.
   printf("digite um valor\n");
	scanf("%i", &valor); fflush(stdin);
	insere_antes_do_terceiro(l, valor);
	mostra_lista(l);
	remove_quinto_elemento(l);
	mostra_lista(l);
	printf("a lista tem agora %i", l->qtde);
   libera_lista(l);
   free(l); //libera header
   return 0;
}
