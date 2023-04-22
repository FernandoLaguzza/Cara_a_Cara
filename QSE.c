#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* Definição da estrutura de um nó da lista encadeada */
typedef struct st_lista {
    char *nome;
    struct st_lista *prox;
} lista;

/* Função para criar um novo nó com o dado especificado */
lista *novo_no(char *nome) 
{
    lista *nodo = (lista*)malloc(sizeof(lista));
    nodo->nome = (char*) malloc(strlen(nome) + 1);
    strcpy(nodo->nome, nome);
    nodo->prox = NULL;
    return nodo;
}

/* Função para inserir um novo nó no final da lista */
void inserir(lista **cabeca, char *nome) 
{
    lista *pl = novo_no(nome);
    if(*cabeca == NULL) 
        *cabeca = pl;
	else
	{
        lista *plant = *cabeca;
        while (plant->prox != NULL) 
            plant = plant->prox;

        plant->prox = pl;
    }
}

/* Função para imprimir uma lista */
void imprimir(lista *cabeca)
{
	lista *pl = cabeca;

	while(pl != NULL)
	{
		printf("%s\n", pl->nome);
		pl = pl->prox;
	}
}
// Função para sortear uma string aleatória na lista encadeada
lista *sorteio_nome(lista *cabeca)
{
    int count = 0, sorteio = 0, i = 0;
    lista *pl = cabeca;

    while(pl != NULL)
	{
        count++;
        pl = pl->prox;
    }

    sorteio = rand() % count;
    pl = cabeca;
    for(i = 0; i < sorteio; i++)
	{
        pl = pl->prox;
	}
    
	return pl;

}

lista *remove_nome(lista *cabeca, char *nome)
{
	lista *pl = cabeca;
    if(cabeca == NULL)
        return NULL;

    if(strcmp(cabeca->nome, nome) == 0)
	{
        pl = pl->prox;
        free(cabeca);
        return pl;
    }
    pl->prox = remove_nome(cabeca->prox, nome);
    return pl;
}

/* Função que limpa a memória alocada pela lista */
void clean(lista *cabeca)
{
	lista *pl = cabeca;

	while(pl != NULL)
	{
		lista *proximo = pl->prox;
        free(pl->nome);
        free(pl);
        pl = proximo;

	}
}



/* Função principal */
int main(void)
{
    FILE* file = fopen("nomes.txt", "r");
    lista *cabeca = NULL, *sorteado;
    char linha[100];
	int i = 0, j = 0;

	if(file == NULL)
	{
		printf("Erro ao abrir o arquivo\n");
		return 1;
	}

    while (fgets(linha, sizeof(linha), file) != NULL) 
	{
        // Remove o caractere '\n' do final da linha (se existir)
        if(linha[strlen(linha) - 1] == '\n')
            linha[strlen(linha) - 1] = '\0';
        
		inserir(&cabeca, linha);
    }
    fclose(file);

	printf("\n");
    
	srand(time(NULL));


	printf("\n");
	printf("Personagem jogador 2:");
	printf("\n");
    for(i = 0; i < 2; i++)
	{
        sorteado = sorteio_nome(cabeca);
        printf("%s ", sorteado->nome);
        cabeca = remove_nome(cabeca, sorteado->nome);
    }
	printf("\n");
	for(i = 0; i < 100; i++)
	{
		printf(".\n");
	}
	printf("\n");
	printf("Personagem jogador 1:");
	printf("\n");
	for(j = 0; j < 2; j++)
	{
		sorteado = sorteio_nome(cabeca);
		printf("%s ", sorteado->nome);
		cabeca = remove_nome(cabeca, sorteado->nome);
	}
	printf("\n");
	for(i = 0; i < 100; i++)
	{
		printf(".\n");
	}

    printf("\n");

	printf("Lista de Personagens: \n");
	imprimir(cabeca);

	clean(cabeca);

    return 0;
}
