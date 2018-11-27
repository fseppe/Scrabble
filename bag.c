#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bag.h"
#include "game.h"

 /*****************************/
/* funcoes de criacao da bag */
bag_t *bag_Create(){
	bag_t *b = (bag_t *) malloc(sizeof(bag_t));
	if(b == NULL){
		printf("ERRO: Nao foi possivel iniciar a bag!\n");
		exit(1);
	}
	b->head = NULL;
	b->tail = NULL;
	b->size = 0;
	return b;
}

//Insere todas as pedras na bag
void bag_Tiles(bag_t *aux_bag){
	int i;
	for(i = 0; i < 3; i++)
		bag_Insert(aux_bag, '*', 0);
	for(i = 0; i < 14; i++)
		bag_Insert(aux_bag, 'a', 1);
	for(i = 0; i < 11; i++)
		bag_Insert(aux_bag, 'e', 1);
	for(i = 0; i < 10; i++)
		bag_Insert(aux_bag, 'i', 1);
	for(i = 0; i < 10; i++)
		bag_Insert(aux_bag, 'o', 1);
	for(i = 0; i < 8; i++)
		bag_Insert(aux_bag, 's', 1);
	for(i = 0; i < 7; i++)
		bag_Insert(aux_bag, 'u', 1);
	for(i = 0; i < 6; i++)
		bag_Insert(aux_bag, 'm', 1);
	for(i = 0; i < 6; i++)
		bag_Insert(aux_bag, 'r', 1);
	for(i = 0; i < 5; i++)
		bag_Insert(aux_bag, 't', 1);
	for(i = 0; i < 5; i++)
		bag_Insert(aux_bag, 'd', 2);
	for(i = 0; i < 5; i++)
		bag_Insert(aux_bag, 'l', 2);
	for(i = 0; i < 4; i++)
		bag_Insert(aux_bag, 'c', 2);
	for(i = 0; i < 4; i++)
		bag_Insert(aux_bag, 'p', 2);
	for(i = 0; i < 4; i++)
		bag_Insert(aux_bag, 'n', 3);
	for(i = 0; i < 3; i++)
		bag_Insert(aux_bag, 'b', 3);
	for(i = 0; i < 2; i++)
		bag_Insert(aux_bag, 'f', 4);
	for(i = 0; i < 2; i++)
		bag_Insert(aux_bag, 'g', 4);
	for(i = 0; i < 2; i++)
		bag_Insert(aux_bag, 'h', 4);
	for(i = 0; i < 2; i++)
		bag_Insert(aux_bag, 'v', 4);
	for(i = 0; i < 2; i++)
		bag_Insert(aux_bag, 'j', 5);
	bag_Insert(aux_bag, 'q', 6);
	bag_Insert(aux_bag, 'x', 8);
	bag_Insert(aux_bag, 'z', 8);
}

void bag_Random(bag_t *bag){
	int i, random, num_elements;
	num_elements = bag->size;
	char aux[num_elements];
	int aux_value[num_elements];
	srand((unsigned) time(NULL));
	for(i = 0; i < num_elements; i++){
		aux_value[i] = bag_Value(bag);
		aux[i] = bag_Remove(bag);
	}
	for(i = 0; i < num_elements; i++){
		random = rand()%num_elements;
		while(aux[random] == '0'){
			random++;
			random = (random%num_elements);
		}
		bag_Insert(bag, aux[random], aux_value[random]);
		aux[random] = '0';
	}
}

//bag_Insert inserimos sempre no fim
void bag_Insert(bag_t *b, char tile, int value){
	node_t *new = (node_t *) malloc(sizeof(node_t));
	new->tile = tile;
	new->next = NULL;
	new->value = value;
	if(b->head == NULL){
		b->head = new;
	}
	else{
		b->tail->next = new;
	}
	b->tail = new;
	b->size++;
}

//bag_Remove remove sempre do inicio
char bag_Remove(bag_t *b){
	if(bag_is_Empty(b)){
		return BLANK_HAND;
	}
	node_t *aux;
	char toReturn;
	toReturn = b->head->tile;
	aux = b->head;
	aux = aux->next;
	free(b->head);
	b->head = aux;
	b->size--;
	return toReturn;
}

//funcao para pegar o valor da primeira pedra da bag
int bag_Value(bag_t *b){
	if(bag_is_Empty(b)){
		printf("Lista vazia!\n");
		exit(1);
	}
	return b->head->value;
}

void bag_Print(bag_t *b){
	if(bag_is_Empty(b)){
		printf("Lista vazia!\n");
		return;
	}
	node_t *aux = b->head;
	while(aux != NULL){
		printf("%c ", aux->tile);
		aux = aux->next;
	}
}

int bag_is_Empty(bag_t *bag){
	if(bag->head == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

void bag_Destroy(bag_t *b){
	aux_Destroy(b->head);
	b->head = NULL;
	b->tail = NULL;
	b->size = 0;
}

void aux_Destroy(node_t *aux){
	if(aux == NULL){
		return;
	}
	aux_Destroy(aux->next);
	free(aux);
}
