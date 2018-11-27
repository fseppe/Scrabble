#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashing.h"

table_t *table_Create(){
	table_t *table = (table_t *) malloc(sizeof(table_t));
	table->entries = (entry_t **) malloc(TABLE_HASH_SIZE * sizeof(entry_t *));
	table->size = TABLE_HASH_SIZE;
	int i;
	for(i = 0; i < TABLE_HASH_SIZE; i++){
		table->entries[i] = NULL;
	}
	return table;
}

entry_t *entry_Initialize(char *palavra){
	entry_t *entry = (entry_t *) malloc(sizeof(entry_t));
	entry->next = NULL;
	strcpy(entry->palavra, palavra);
	entry->key = hash(palavra);
	return entry;
}

void table_Insert(table_t *table, char *arquivo){
	FILE *fp = fopen(arquivo, "r");
	entry_t *aux;
	char palavra[40];
	while(fscanf(fp, "%s", palavra) != EOF){
		entry_t *entry = entry_Initialize(palavra);
		if(table->entries[entry->key] == NULL){
			table->entries[entry->key] = entry;
		}
		else{
			aux = table->entries[entry->key];
			while(aux->next != NULL){
				aux = aux->next;
			}
			aux->next = entry;
		}
	}
	fclose(fp);
}

int hash(char *palavra){
	unsigned long hash = 5381;
	int c;
	while(c = *palavra++){
		hash = ((hash << 5) + hash) + c;
	}
	return (hash%TABLE_HASH_SIZE);
}

int busca_Palavra(table_t *table, char *palavra){
	int key = hash(palavra);
	entry_t *aux = table->entries[key];
	while(aux != NULL){
		if(strcmp(aux->palavra, palavra) == 0){
			return 1;
		}
		aux = aux->next;
	}
	return 0;
}
