#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

/* funcoes para criacao do tabuleiro */

board_t *board_Create(){
	board_t *board = (board_t *) malloc(sizeof(board_t));
	board->m_visual = matrix_char_Create();
	board->m_value = matrix_int_Create();
	board->m_new = matrix_int_Create();
	board->m_special =  matrix_int_Create();
	board_special_Positions(board);
	return board;
}

char **matrix_char_Create(){
	char **matriz = (char **) malloc(BOARD_SIZE * sizeof(char *));
	int i, j;
	for(i = 0; i < BOARD_SIZE; i++){
		matriz[i] = (char *) malloc(BOARD_SIZE * sizeof(char));
	}
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			matriz[i][j] = BLANK_BOARD;
		}
	}
	return matriz;
}

int **matrix_int_Create(){
	int i;
	int **matriz = (int **) malloc(BOARD_SIZE * sizeof(int *));
	for(i = 0; i < BOARD_SIZE; i++){
		//calloc usado para inicializar com 0
		matriz[i] = (int *) calloc(BOARD_SIZE, sizeof(int));
	}
	return matriz;
}

// funcao para inserir as posicoes especiais no taubleiro
void board_special_Positions(board_t *board){
	//4 eh triple word  //2 eh trilpe letter
	//3 eh double word  //1 eh double letter
	int i, j;
	//inserindo triple word
	for(i = 0; i < 15; i+=7){
		for(j = 0; j < 15; j+=7){
			board->m_special[i][j] = 4;
		}
	}
	board->m_special[7][7] = 0;
	//inserido double word
	for(i = 1; i < 5; i++){
		board->m_special[i][i] = 3;
	}
	for(i = 10; i < 14; i++){
		board->m_special[i][i] = 3;
	}
	for(i = 1, j = 13; i < 5; i++, j--){
		board->m_special[i][j] = board->m_special[j][i] = 3;
	}
	//inserindo triple letter
	for(i = 5; i < 10; i+=4){
		for(j = 1; j < 14; j+= 4){
			board->m_special[i][j] = 2;
			board->m_special[j][i] = 2;
		}
	}
	//inserindo double letter
	board->m_special[0][3] = 1; board->m_special[0][11] = 1; board->m_special[2][6] = 1;
	board->m_special[2][8] = 1; board->m_special[3][7] = 1; board->m_special[3][14] = 1; 
	board->m_special[6][6] = 1; board->m_special[8][8] = 1; board->m_special[6][8] = 1;
	board->m_special[6][12] = 1; board->m_special[7][11] = 1; board->m_special[8][12] = 1;
	board->m_special[11][14] = 1;
	for(i = 0; i < 15; i++){
		for(j = i; j < 15; j++){
			if(board->m_special[i][j] == 1){
				board->m_special[j][i] = 1;
			}
		}
	}
	for(i = 0; i < 15; i++){
		for(j = 0; j < 15; j++){
			if(board->m_special[i][j] == 1){
				board->m_visual[i][j] = '1';
			}
			else if(board->m_special[i][j] == 2){
				board->m_visual[i][j] = '2';
			}
			else if(board->m_special[i][j] == 3){
				board->m_visual[i][j] = '3';
			}
			else if(board->m_special[i][j] == 4){
				board->m_visual[i][j] = '4';
			}
		}
	}
}

/* funcoes de alteracoes no tabuleiro */
void board_Copy(board_t *b1, board_t *b2){
	int i, j;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			b1->m_visual[i][j] = b2->m_visual[i][j];
			b1->m_value[i][j] = b2->m_value[i][j];
			b1->m_new[i][j] = b2->m_new[i][j];
			b1->m_special[i][j] = b2->m_special[i][j];
		}
	}
}

void board_Insert(board_t *board, player_t *player, char letra, int linha, int coluna){
	int i;
	int value;
	for(i = 0; i < HAND_SIZE; i++){
		if(player->hand[i] == letra){
			player->hand[i] = BLANK_HAND;
			value = player->hand_value[i];
			player->hand_value[i] = 0;
			player->num_tiles--;
			break;
		}
	}
	board->m_visual[linha][coluna] = letra;
	board->m_value[linha][coluna] += value;
	board->m_new[linha][coluna] = 1;
}

/* funcao para somar a pontuacao do jogador */
void board_Points(board_t *board, player_t *player){
	int i, j;
	int temp_Score = 0;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			if(board->m_new[i][j] == 3){
				if(board->m_special[i][j] == 1){
					board->m_value[i][j] *= 2;
					board->m_special[i][j] = 0;
				}
				else if(board->m_special[i][j] == 2){
					board->m_value[i][j] *= 3;
					board->m_special[i][j] = 0;
				}
				temp_Score += board->m_value[i][j];
			}
		}
	}
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			if(board->m_new[i][j] == 3){
				if(board->m_special[i][j] == 3){
					temp_Score *= 2;
				}
				else if(board->m_special[i][j] == 4){
					temp_Score *= 3;
				}
			}
		}
	}
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			if(board->m_new[i][j] == 3){
				board->m_new[i][j] = 2;
			}
		}
	}
	player->score += temp_Score;
}


/* funcoes de verificacoes do tabuleiro */
int verify_Word(table_t *table, board_t *board, player_t *player, int linha, int coluna){
	//primeiro verifica se a posicao indicada pelo usuario eh valida
	//em seguida verifica se a palavra foi formada corretamente na horizontal
	//logo apos verifica na vertical
	if(verify_Position(linha, coluna) == 0){
		return 0;
	}
	if(verify_Horizontal(table, board, player, linha, coluna) == 1){
		return 1;
	}
	if(verify_Vertical(table, board, player, linha, coluna) == 1){
		return 1;
	}
	return 0;
}

int verify_Horizontal(table_t *table, board_t *board, player_t *player, int linha, int coluna){
	int i, j;
	int cont;
	int is_New;
	char sub_string[16];
	//verificando se ha a palavra na horizontal
	i = 0; j = coluna; cont = 0; is_New = 0;
	while(j < BOARD_SIZE){
		if(board->m_new[linha][j] == 0){
			break;
		}
		//esse if serve para verificar se a linha que o jogador indicou que inicia sua palavra 
		//realmente possue alguma nova letra
		if(board->m_new[linha][j] == 1){
			is_New = 1;
			
		}
		sub_string[i] = board->m_visual[linha][j];
		i++; j++; cont++;
	}
	sub_string[i] = '\0';
	//a funcao busca_Palavra retorna 1 caso exista a palavra
	if(busca_Palavra(table, sub_string)){
		//caso a palavra nao seja realmente nova, retornamos 0
		if(is_New == 0){
			return 0;
		} 
		int aux = 0;
		//caso haja a palvra, verificamos se foram inseridas letras a mais
		//para manter a integridade, caso tenha inserido letras a mais, ele perde a vez
		for(i = 0; i < BOARD_SIZE; i++){
			for(j = 0; j < BOARD_SIZE; j++){
				if(board->m_new[i][j] == 1){
					aux++;
				}
			}
		}
		if(aux > cont){
			return 0;
		}
		j = coluna;
		while(j < BOARD_SIZE){
			if(board->m_new[linha][j] == 0){
				break;
			}
			board->m_new[linha][j] = 3;
			j++;
		}
		return 1;
	}
	return 0;
}

int verify_Vertical(table_t *table, board_t *board, player_t *player, int linha, int coluna){
	int i, j;
	int cont;
	int is_New;
	char sub_string[16];
	i = linha; j = 0; is_New = 0; cont = 0;
	while(i < BOARD_SIZE){
		if(board->m_new[i][coluna] == 0){
			break;
		}//esse if serve para verificar se a linha que o jogador indicou que inicia sua palavra 
		//realmente possue alguma nova letra
		if(board->m_new[i][coluna] == 1){
			is_New = 1;
		}
		sub_string[j] = board->m_visual[i][coluna];
		i++; j++; cont++;
	}
	sub_string[j] = '\0';
	if(busca_Palavra(table, sub_string)){
		//caso a palavra nao seja realmente nova, retornamos 0
		if(is_New == 0){
			return 0;
		}
		//caso haja a palvra, verificamos se foram inseridas letras a mais
		//para manter a integridade, caso tenha inserido letras a mais, ele perde a vez
		int aux = 0;
		for(i = 0; i < BOARD_SIZE; i++){
			for(j = 0; j < BOARD_SIZE; j++){
				if(board->m_new[i][j] == 1){
					aux++;
				}
			}
		}
		if(aux > cont){	
			return 0;
		}
		i = linha; 
		while(i < BOARD_SIZE){
			if(board->m_new[i][coluna] == 0){
				break;
			}
			board->m_new[i][coluna] = 3;
			i++;
		}
		return 1;
	}
	return 0;
}

int verify_Position(int linha, int coluna){
	if(linha < 0 && linha >= 15){
		return 0;
	}
	if(coluna < 0 && coluna >= 15){
		return 0;
	}
	return 1;
}

/* funcoes para exibir o tabuleiro */
void board_char_Print(char **board){
	int i, j;
	for(i = 0; i < BOARD_SIZE; i++){
		if(i == 0){
			for(j = 0; j < BOARD_SIZE; j++){
				if(j == 0){
					printf("\t     ");
				}
				printf("%2d  ", j+1);
			}
			printf("\n");
			for(j = 0; j < BOARD_SIZE; j++){
				if(j == 0){
					printf("\t    |");
				}
				printf("---|");
			}
			printf("\n");
		}
		for(j = 0; j < BOARD_SIZE; j++){
			if(j == 0){
				printf("\t%2d  |", i+1);
			}
			//caso seja BLANK_BOARD (nao foi colocado nada na posicao, ela ficara em branco)
			if(board[i][j] == BLANK_BOARD){
				printf("   |");
			}
			else{
				printf(" %c |", board[i][j]);
			}
		}
		printf("\n");
		for(j = 0; j < BOARD_SIZE; j++){
			if(j == 0){
				printf("\t    |");
			}
			printf("---|");
		}
		printf("\n");
	}
	printf("\n");
}

//funcao para verificacao das matrizes auxiliares do tabuleiro
void board_int_Print(int **board){
	int i, j;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//funcao para desalocar o tabulerio
void board_Destroy(board_t *board){
	int i;
	for(i = 0; i < BOARD_SIZE; i++){
		free(board->m_visual[i]);
		free(board->m_value[i]);
		free(board->m_new[i]);
		free(board->m_special[i]);
	}
	free(board->m_visual);
	free(board->m_value);
	free(board->m_new);
	free(board->m_special);
	free(board);
}
