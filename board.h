#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 15
#define BLANK_BOARD '?'

//struct para representacao do tabuleiro
typedef struct{
	char **m_visual;
	int **m_value;
	int **m_new;
	int **m_special;
}board_t;

#include "hashing.h"
#include "player.h"

board_t *board_Create();
int **matrix_int_Create();
char **matrix_char_Create();

//new sera igual a toCopy
void board_Copy(board_t *nova, board_t *toCopy);
void board_Insert(board_t *, player_t *, char, int linha, int coluna);
void board_Points(board_t *, player_t *);
int verify_Position(int, int);

int verify_Word(table_t *, board_t *, player_t *, int linha, int coluna);
int verify_Horizontal(table_t *, board_t *, player_t *, int linha, int coluna);
int verify_Vertical(table_t *, board_t *, player_t *, int linha, int coluna);

void board_special_Positions(board_t *);
void board_char_Print(char **);

void board_int_Print(int **);
void board_Destroy(board_t *);

#endif