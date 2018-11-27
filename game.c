#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "board.h"
#include "player.h"

/* funcoes para interface do jogo */
void menu_Print(){
	system("cls");
	printf("\n\n\tSCRABBLE v0.6\t\t\t\n");
	printf("\n\n\n\n");
	printf(" Escolha o numero de jogadores: \n");
	printf(" OBS: 2, 3 ou 4 jogadores!\n");
	printf(" Digite aqui: ");
}

void game_Print(board_t *board, player_t *player, bag_t *bag){
	info_player_Print(board, player, bag);
	printf(" Digite:");
	printf(" 1. Jogar\n");
	printf("         2. Passar a vez\n");
	printf("         3. Trocar a mao\n");
	printf("         4. Desistir\n");
	printf("         5. Dicas\n");
	printf("\n");
	printf(" Digite sua jogada: ");
}

void info_player_Print(board_t *board, player_t *player, bag_t *bag){
	system("cls");
	printf("\n");
	board_char_Print(board->m_visual);
	printf("\t\t\t\tTURNO DE %s\n", player->name);
	printf("\t    MAO: ");
	player_hand_Print(player);
	printf("\t  PONTUACAO: %d", player->score);
	printf("\tPEDRAS NA BAG: %d\n", bag->size);
	printf("\n");
}

void game_Play(table_t *table, bag_t *bag, board_t *board, player_t **player, int num_jog){
	int jogada;
	int i = 0;
	int num_playing = num_jog;
	int pass = 0;
	for(i = 0; i < num_jog+1; i++){
		i = (i % num_jog);
		if(num_playing < 2){
			return;
		}
		if(player[i]->playing == 0){
			continue;
		}
		if(pass == (num_jog*2)){
			return;
		}

		game_Print(board, player[i], bag);

		scanf("%d", &jogada);
		//system("pause");
		if(jogada == 1){
			board_t *temp_board = board_Create();
			board_Copy(temp_board, board);
			
			if(action_1(table, bag, temp_board, player[i], 0)){
				pass = 0;
				board_Points(temp_board, player[i]);
				board_Copy(board, temp_board);
				board_Destroy(temp_board);
				player_hand_Complete(bag, player[i]);
				if(bag_is_Empty(bag)){
					return;
				}
			}
			else{
				printf("Palavra invalida!\n");
				board_Destroy(temp_board);
				i--;
			}
		}
		else if(jogada == 2){
			pass++;
			continue;
		}
		else if(jogada == 3){
			action_3(bag, board, player[i], 0);
			pass = 0;
		}
		else if(jogada == 4){
			player[i]->playing = 0;
			num_playing--;
		}
		else if(jogada == 5){
			action_5();
			i--;
		}
		else if(jogada == 6){
			action_6(board);
			i--;
		}
	}
}

void game_End(board_t *board, player_t **players, int num_jog){
	system("cls");
	board_char_Print(board->m_visual);
	players_Score(players, num_jog);
	printf("\t\t\t\t FIM DE JOGO!!\n\n");
	printf("\t\t\t\t    PLACAR: \n\n");
	players_Sort(players, num_jog);
	int i;
	for(i = 0; i < num_jog; i++){
		printf("\t\t\t     %d. %s com %d pontos\n", i+1, players[i]->name, players[i]->score);
	}
	printf("\n");
}

int action_1(table_t *table, bag_t *bag, board_t *board, player_t *player, int action){
	if(action == 0){
		info_player_Print(board, player, bag);
	}
	if(player->num_tiles > 0){
		if(action == 1){
			printf(" Letra invalida!\n");
		}
		else if(action == 2){
			printf(" Linha ou coluna invalida!\n");
		}
		printf(" Digite a letra, linha e coluna que deseja jogar\n");
		printf(" Caso deseje retornar, coloque sua letra como '0'. Caso deseje encerrar, coloque sua letra como '1'\n");
	}
	else{
		printf(" Sua mao esta vazia!\n");
		printf(" Digite 1 para encerrar sua jogada\n");
	}
	char letra;
	int linha, coluna;
	printf(" Digite... ");
	scanf(" %c", &letra);
	if(letra == '0'){
		player_hand_Back(board, player);
		return 0;		
	}
	if(letra == '1'){
		printf(" Digite a linha e a coluna que sua palavra comeca, caso tenha formado.\n");
		printf(" Digite... ");
		scanf("%d %d", &linha, &coluna);
		linha--; coluna--;
		//verify_Word retorna 1 caso o player tenha inserido corretamente
		//alem de ja aumentar seu score
		if(verify_Word(table, board, player, linha, coluna)){
			return 1;
		}
		else{
			player_hand_Back(board, player);
			return 0;
		}
	}
	scanf("%d %d", &linha, &coluna);
	linha--; coluna--;
	if(letra == '*'){
		printf(" CARTA CORINGA!\n");
		printf(" Digite qual letra voce deseja usar: ");
		scanf(" %c", &letra);
		int i;
		for(i = 0; i < HAND_SIZE; i++){
			if(player->hand[i] == '*'){
				player->hand[i] = letra;
				break;
			}
		}
	}
	if(verify_Tile(player->hand, letra)){
		if(verify_Position(linha, coluna) && board->m_new[linha][coluna] == 0){
			board_Insert(board, player, letra, linha, coluna);
			return action_1(table, bag, board, player, 0);
		}
		else{
			return action_1(table, bag, board, player, 2);
		}
	}
	else{
		return action_1(table, bag, board, player, 1);
	}
}


void action_3(bag_t *bag, board_t *board, player_t *player, int action){
	//info_player_Print(board, player, bag);
	printf(" Para trocar toda a mao, digite 1\n");
	printf(" Caso deseje trocar apenas uma letra, digite a letra desejada\n");
	if(action){
		printf(" Voce nao possui a letra informada em maos\n");
		printf(" Digite novamente... ");
	}
	else{
		printf(" Digite... ");
	}
	char letra;
	scanf(" %c", &letra);
	if(letra == '1'){
		player_hand_Change(bag, player, 1, '0');
		bag_Random(bag);
		return;
	}
	else{
		if(verify_Tile(player->hand, letra)){
			player_hand_Change(bag, player, 0, letra);
			bag_Random(bag);
			return;
		}
		else{
			action_3(bag, board, player, 1);
		}
	}
}

void action_5(){
	printf("\n");
	printf(" Posicoes no tabuleiro marcadas com numeros, representam posicoes especiais!\n");
	printf(" Caso sua palavra formada passe por alguma delas, recebera uma pontacao bonus!!\n");
	printf("\t1. O dobro de pontos para a letra naquela posicao;\n");
	printf("\t2. O triplo de pontos para a letra naquela posicao;\n");
	printf("\t3. O dobro de pontos na palavra formada;\n");
	printf("\t4. O triplo de pontos na palavra formada.\n");
	printf("\n");
	char lixo;
	printf(" Digite qualquer coisa para retornar... ");
	scanf(" %c", &lixo);
}

void action_6(board_t *board){
	char letra;
	while(1){
		scanf(" %c", &letra);
		if(letra == '1'){
			return;
		}
		int linha, coluna;
		scanf("%d %d", &linha, &coluna);
		linha--; coluna--;
		board->m_visual[linha][coluna] = letra;
		board->m_new[linha][coluna] = 2;
	}
}