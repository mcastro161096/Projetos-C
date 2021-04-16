#include <stdio.h>
#include <conio.h>
#include <malloc.h>

#define max 5

void cria_lista (struct aponta_header **listad);
void insere_esquerda (struct aponta_header *listad , int valor);
void insere_direita (struct aponta_header  *listad , int valor);
int remover_esquerda( struct aponta_header *listad);
int remove_direita (struct aponta_header *listad);
void mostra_lista (struct aponta_header *listad);
void libera_lista (struct aponta_header **listad );


   struct aponta_nodo {
        	struct aponta_nodo *ant ;
        	int dados;
			struct aponta_nodo *prox ;
    };

    struct aponta_header {
 		struct aponta_nodo *inicio;
           int qtde;
 		struct aponta_nodo *fim ;
    };


// Procedimento para criar uma lista. 
void cria_lista (struct aponta_header **listad)
{
   struct aponta_header *lista=NULL;
   lista = (struct aponta_header *) malloc(sizeof(struct aponta_header));
   if (lista != NULL)
   {
             lista->inicio = NULL;
             lista->qtde   = 0;
             lista->fim    = NULL;
    }
	*listad=lista;
}

// Inserção de um nodo antes do 1o nodo (com header) 
void insere_esquerda (struct aponta_header *listad , int valor)
{
 	struct aponta_nodo *p, *aux ; 
	p= (struct aponta_nodo *) malloc(sizeof(struct aponta_nodo));
	if( p != NULL) {
                  p->dados = valor;
                  p->ant = NULL;
                  p->prox = listad->inicio;
                  if (p->prox != NULL)
                  {
                         aux = listad->inicio;
                         aux->ant = p;
                   }
                  listad->inicio = p;
 				  listad->qtde++;
                  if (listad->fim == NULL) 	//Se lista estava vazia...
                     listad->fim = p;
       }
}

void insere_direita (struct aponta_header  *listad , int valor)
{
 	struct aponta_nodo  *p, *aux;
	p= (struct aponta_nodo *) malloc(sizeof(struct aponta_nodo));
	if (p != NULL) {
                  p->dados = valor;
                  p->ant = listad->fim;
                  if (p->ant != NULL)
                  {
                        aux = listad->fim;
                        aux->prox = p;
                  }
                  p->prox = NULL;
                  listad->fim  = p;
 	              listad->qtde++;
                  if (listad->inicio == NULL)  //Se lista estava vazia...
                                listad->inicio = p;
                }
}

//remove primeiro nodo da lista
int remover_esquerda( struct aponta_header *listad) 
{
	struct aponta_nodo *p;
	int valor=0;
	if(listad->qtde == 0)  return 0;
	else
	{
		valor = listad->inicio->dados;
		p = listad->inicio;
		listad->inicio = p->prox;
		if (listad->qtde == 1)   //apenas 1 nodo
			listad->fim = NULL;
		else
			listad->inicio->ant = NULL;  
			//existe um posterior
		free (p);
		listad->qtde--;
	} 
	return valor;
}


// Remove o ultimo nodo da lista 
int remove_direita (struct aponta_header *listad) 
{
 	struct aponta_nodo *p, *aux ;
     	int valor=0 ;
	if(listad->qtde == 0)  return 0;
	else {
                  p = listad->fim;
                  valor = p->dados;
                  if (listad->qtde > 1)
                  {
                         aux = p->ant;
                         listad->fim = aux;
                         aux->prox = NULL;
                   }
                  else
                       listad->inicio = NULL;

                  free(p);
                  listad->qtde--;
                 
           }  return valor;
}

// mostra valores da lista. }
void mostra_lista (struct aponta_header *listad )
{
  struct aponta_nodo *aux ;
  aux = listad->inicio;
  printf("\nLista ===> \n");
  while (aux != NULL)
  {
      printf("%i - ", aux->dados);
      aux = aux->prox;
   }
  printf("\n");
}

 void libera_lista (struct aponta_header **listad )
{
  struct aponta_nodo *aux, *p ;
  aux = (*listad)->inicio;

  while (aux != NULL)
  {    p = aux-> prox;
      free(aux);
      aux = p;
   }
  }

int main()
{
	struct aponta_header *L;
	int num, x;
//Chama procedimento para criar a lista. 
	cria_lista (&L);

	//le valores do usuário e armazena na lista. 
    printf ("Inserindo valores a esquerda da lista...\n");
	for (x = 1; x<=max ; x++)
	{
		printf("Digite um valor qualquer: ");
		scanf("%i",&num); fflush(stdin);
        insere_esquerda (L, num);
    }

        //mostra valores armazenados na lista. 
        mostra_lista (L);
        getch();

	// retira o ultimo nodo da lista e escreve na tela. 
	printf("Valor  %i  - ultimo nodo - foi removido da lista !!!\n", remove_direita (L));
    mostra_lista (L);
    getch();
    libera_lista (&L);
      
}

