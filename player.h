#ifndef PLAYER_H
#define PLAYER_H

#define HAND_SIZE 7
#define BLANK_HAND '_'

/* Struct para representar cada jogador */
typedef struct{
	char name[14];
	char hand[7];
	int hand_value[7];
	int score;
	int num_tiles;
	int playing;
}player_t;

#include "bag.h"
#include "board.h"

/* funcoes sobre os jogadores */
player_t *player_Create(bag_t *);

void player_hand_Complete(bag_t *, player_t *);
void player_hand_Change(bag_t *, player_t *, int, char);
void player_hand_Back(board_t *, player_t *);

void player_hand_Print(player_t *);
void players_Sort(player_t **, int);
void players_Score(player_t **, int);

int verify_Tile(char *, char);


#endif