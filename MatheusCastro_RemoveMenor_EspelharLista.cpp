#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>

//Matheus Castro 
//Funções a serem corrigidas: remove_menor e espelhar_lista

struct nodo
{
    int dados;
    struct nodo *prox;
};
struct header
{
    struct nodo *iniciol;
    int qtde;
    struct nodo *fiml;
};
struct nodo_duplo
{
    struct nodo_duplo *ant;
    int dados;
    struct nodo_duplo *prox;
};
struct header_duplo
{
    struct nodo_duplo *inicio;
    int qtde;
    struct nodo_duplo *fim;
};

void cria_header(struct header **lista, int *status);
void insere_direita(struct header *lista, int valor, int *status);
void mostra_lista(struct header *lista);
void libera_lista(struct header *lista);
void remove_menor(struct header *lista);

void cria_header_duplo(struct header_duplo **listad);
void insere_direitaduplo(struct header_duplo *listad, int valor);
void mostra_listaduplo(struct header_duplo *listad);
void libera_listaduplo(struct header_duplo *listad);
void espelhar_lista(struct header_duplo *lista);

void espelhar_lista(struct header_duplo *lista)
{
    struct nodo_duplo *p;
    int tamanholista = lista->qtde, i;
    int vetor[tamanholista];
    if (lista->qtde == 0)
    {
        printf("A lista está vazia");
    }
    if (lista->qtde == 1)
    {
        printf("A lista possui apenas um elemento então não pode ser espelhada");
    }
    if (lista->qtde > 1)
    {
        p = lista->fim;
        for (i = 0; i <= tamanholista - 1; i++)
        {
            vetor[i] = p->dados;
            p = p->ant;
        }
        p = lista->inicio;
        for (i = 0; i <= tamanholista - 1; i++)
        {
            p->dados = vetor[i];
            p = p->prox;
        }
    }
}

void remove_menor(struct header *lista)
{
    struct nodo *p, *menor, *anteriorAoMenor;
    if (lista->qtde >= 1)
    {
        if (lista->qtde == 1)
        {
            free(lista->iniciol);
            lista->iniciol = NULL;
            lista->fiml = NULL;
            lista->qtde = 0;
            printf("A lista agora está vazia pois o unico elemento foi removido");
        }
        else
        {
            p = lista->iniciol;
            menor = lista->iniciol;
            anteriorAoMenor = lista->iniciol;
            while (p->prox != NULL || p == lista->fiml)
            {
                if (p->dados < menor->dados)
                {
                    menor = p;
                }
                if (p->prox != NULL)
                {
                    p = p->prox;
                }
                else
                {
                    break;
                }
            }
            if (menor == lista->iniciol)
            {
                lista->iniciol = lista->iniciol->prox;
            }

            else
            {
                while (anteriorAoMenor->prox != menor)
                {
                    anteriorAoMenor = anteriorAoMenor->prox;
                }
            }
            if (menor == lista->fiml)
            {
                lista->fiml = anteriorAoMenor;
                lista->fiml->prox = NULL;
            }
            else
            {
                anteriorAoMenor->prox = menor->prox;
            }
            free(menor);
            lista->qtde--;
        }
    }
    else
    {
        printf("A lista está vazia");
    }
}

void cria_header(struct header **lista, int *status)
{
    *lista = (struct header *)malloc(sizeof(struct header));
    if (*lista == NULL)
        *status = 0;
    else
    {
        (*lista)->iniciol = NULL;
        (*lista)->qtde = 0;
        (*lista)->fiml = NULL;
        *status = 1;
    }
}

void insere_direita(struct header *lista, int valor, int *status)
{
    struct nodo *p;
    p = (struct nodo *)malloc(sizeof(struct nodo));
    if (p == NULL)
        *status = 0;
    else
    {
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

void libera_lista(struct header *lista)
{
    struct nodo *p;
    p = lista->iniciol;
    while (p)
    {
        lista->iniciol = lista->iniciol->prox;
        free(p);
        p = lista->iniciol;
    }
}

void mostra_lista(struct header *lista)
{
    struct nodo *aux;
    aux = lista->iniciol;
    while (aux)
    {
        printf("Elemento: %i\n", aux->dados);
        aux = aux->prox;
    }
    getch();
}

void cria_header_duplo(struct header_duplo **listad)
{
    struct header_duplo *listadupla = NULL;
    listadupla = (struct header_duplo *)malloc(sizeof(struct header_duplo));
    if (listadupla != NULL)
    {
        listadupla->inicio = NULL;
        listadupla->qtde = 0;
        listadupla->fim = NULL;
    }
    *listad = listadupla;
}
void insere_direitaduplo(struct header_duplo *listad, int valor)
{
    struct nodo_duplo *p, *aux;
    p = (struct nodo_duplo *)malloc(sizeof(struct nodo_duplo));
    if (p != NULL)
    {
        p->dados = valor;
        p->ant = listad->fim;
        if (p->ant != NULL)
        {
            aux = listad->fim;
            aux->prox = p;
        }
        p->prox = NULL;
        listad->fim = p;
        listad->qtde++;
        if (listad->inicio == NULL) //Se lista estava vazia...
            listad->inicio = p;
    }
}
void mostra_listaduplo(struct header_duplo *listad)
{
    struct nodo_duplo *aux;
    aux = listad->inicio;
    printf("\nLista ===> \n");
    while (aux != NULL)
    {
        printf("%i - ", aux->dados);
        aux = aux->prox;
    }
    printf("\n");
}

void libera_listaduplo(struct header_duplo *listad)
{
    struct nodo_duplo *aux, *p;
    aux = (listad)->inicio;

    while (aux != NULL)
    {
        p = aux->prox;
        free(aux);
        aux = p;
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    // //inicio da execução mostrando o funcionamento da função remove_menor();
    struct header *l;
    int valor, ok;
    printf("\nPrimeiro vamos criar a lista simplesmente encadeada para remover o menor elemento dela \n");
    cria_header(&l, &ok);
    if (ok == 0)
    {
        printf("Descritor não criado!\n");
        getch();
        return 1;
    }
    printf("Digite um valor ou zero: ");
    scanf("%i", &valor);
    fflush(stdin);
    while (valor != 0)
    {
        insere_direita(l, valor, &ok);
        if (ok == 0)
            return 1;
        printf("Digite outro valor ou zero: ");
        scanf("%i", &valor);
        fflush(stdin);
    }
    mostra_lista(l);
    remove_menor(l);
    mostra_lista(l);
    libera_lista(l);
    free(l);
    //fim da execução mostrando o funcionamento da função remove_menor();
    /*-------------------*/
    //inicio da execução mostrando o funcionamento da função espelhar_lista();
    struct header_duplo *l1 = NULL;
    //int valor;
    cria_header_duplo(&l1);
    printf("\nAgora vamos criar a lista duplamente encadeada com header para depois espelhar a mesma\n");
    printf("Digite um valor ou zero: ");
    scanf("%i", &valor);
    fflush(stdin);
    while (valor != 0)
    {
        insere_direitaduplo(l1, valor);

        printf("Digite outro valor ou zero: ");
        scanf("%i", &valor);
        fflush(stdin);
    }
    mostra_listaduplo(l1);
    espelhar_lista(l1);
    mostra_listaduplo(l1);
    libera_listaduplo(l1);
    free(l1);
    //fim da execução mostrando o funcionamento da função espelhar_lista();
    return 0;
}