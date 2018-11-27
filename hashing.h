#ifndef HASHING_H
#define HASHING_H

#define TABLE_HASH_SIZE 100000

/* Structs para criacao da tabela hash */
typedef struct entry{
	int key;
	char palavra[50];
	struct entry *next;
}entry_t;

typedef struct{
	int size;
	entry_t **entries;
}table_t;

/* funcoes do mapeamento hash */
table_t *table_Create();
entry_t *initialize_Entry(char *);
void table_Insert(table_t *, char *);

int hash(char *);
int busca_Palavra(table_t *, char *);


#endif