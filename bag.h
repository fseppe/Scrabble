#ifndef BAG_H
#define BAG_H

/* declarando as structs para os nos e a bag */
typedef struct node{
	char tile;
	int value;
	struct node *next;
}node_t;

typedef struct{
	node_t *head;
	node_t *tail;
	int size;
}bag_t;

bag_t *bag_Create();
void bag_Tiles(bag_t *);
void bag_Random(bag_t *);
void bag_Insert(bag_t *b, char, int);
char bag_Remove(bag_t *b);
int bag_Value(bag_t *b);

void bag_Print(bag_t *);
int bag_is_Empty(bag_t *);

void bag_Destroy(bag_t *);
void aux_Destroy(node_t *);

#endif