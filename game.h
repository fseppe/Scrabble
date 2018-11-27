#ifndef GAME_H
#define GAME_H


#define BLANK_BOARD '?'
#define BLANK_HAND '_'

#include "hashing.h"
#include "bag.h"
#include "board.h"

void menu_Print();
void game_Print(board_t *, player_t *, bag_t *);
void info_player_Print(board_t *, player_t *, bag_t *);

void game_Play(table_t *, bag_t *, board_t *, player_t **, int);
void game_End(board_t *, player_t **, int);

int action_1(table_t *, bag_t *, board_t *, player_t *, int);
void action_3(bag_t *, board_t *, player_t *, int);
void action_5();
void action_6(board_t *);

#endif