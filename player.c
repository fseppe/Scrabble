#include <stdio.h>
#include <stdlib.h>
#include "player.h"

/* funcoes para o jogador */
player_t *player_Create(bag_t *bag){
	player_t *player = (player_t *) malloc(sizeof(player_t));
	player->score = 0;
	player->num_tiles = 7;
	player->playing = 1;
	int i;
	for(i = 0; i < HAND_SIZE; i++){
		player->hand[i] = BLANK_HAND;
	}
	player_hand_Complete(bag, player);
	return player;
}

void player_hand_Complete(bag_t *bag, player_t *player){
	int i;
	for(i = 0; i < HAND_SIZE; i++){
		if(player->hand[i] == BLANK_HAND){
			player->hand_value[i] = bag_Value(bag);
			player->hand[i] = bag_Remove(bag);
			player->num_tiles++;
		}
	}
}

void player_hand_Change(bag_t *bag, player_t *player, int action, char letra){
	int i;
	if(action == 1){
		for(i = 0; i < HAND_SIZE; i++){
			bag_Insert(bag, player->hand[i], player->hand_value[i]);
			player->hand_value[i] = bag_Value(bag);
			player->hand[i] = bag_Remove(bag);
		}
	}
	else{
		for(i = 0; i < HAND_SIZE; i++){
			if(player->hand[i] == letra){
				bag_Insert(bag, player->hand[i], player->hand_value[i]);
				player->hand_value[i] = bag_Value(bag);
				player->hand[i] = bag_Remove(bag);
				break;
			}
		}
	}
}

void player_hand_Back(board_t *board, player_t *player){
	int i, j, k;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			if(board->m_new[i][j] == 1){
				for(k = 0; k < HAND_SIZE; k++){
					if(player->hand[k] == BLANK_HAND){
						player->hand[k] = board->m_visual[i][j];
						player->hand_value[k] = board->m_value[i][j];
						player->num_tiles++;
						break;
					}
				}
			}
		}
	}
}

void player_hand_Print(player_t *player){
	int i;
	char aux;
	for(i = 0; i < HAND_SIZE; i++){
		aux = player->hand[i];
		if(aux != BLANK_HAND){
			printf("%c ", aux);
		}
	}
}

void players_Sort(player_t **players, int num_jog){
	int i, j;
	player_t *current;
	for(i = 1; i < num_jog; i++){
		current = players[i];
		j = i-1;
		while(j >= 0 && players[j]->score < current->score){
			players[j+1] = players[j];
			j--;
		}
		players[j+1] = current;
	}
}

void players_Score(player_t **players, int num_jog){
	int i, j;
	for(i = 0; i < num_jog; i++){
		for(j = 0; j < HAND_SIZE; j++){
			players[i]->score -= players[i]->hand_value[j];
		}
	}
}

int verify_Tile(char *hand, char letra){
	int i;
	for(i = 0; i < HAND_SIZE; i++){
		if(hand[i] == letra){
			return 1;
		}
	}
	return 0;
}