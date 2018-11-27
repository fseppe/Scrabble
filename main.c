#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "player.h"
#include "hashing.h"
#include "bag.h"
#include "game.h"

/* OBRIGADO A MATEUS FIGUEIREDO E SCHIBIGO PELA GRANDE CONTRIBUICAO A DEBUGAR
ALGO EXTREMAMENTE IDIOTA, CUJO TEMPO PERDIDO PODERIA TER FEITO 2 TPS */ 
/***** m_special = 0; LEMBRANDO Q m_special É UMA MATRIZ XD *****/

int main(int argc, char *argv[]){
	int i;
	//inicializando a bag
	bag_t *bag = bag_Create();
	//inserindo as pedras na bag
	bag_Tiles(bag);
	//randomizando a bag
	bag_Random(bag);
	
	//inicializando a tabela hash
	table_t *table = table_Create();
	//inserindo as palavras na tabela
	table_Insert(table, argv[1]);

	printf("%d\n", (0 * 2));

	//inicializando o tabuleiro do jogo e matrizes auxiliares para ele
	board_t *tabuleiro = board_Create();

	//inicializando o jogo interativo
	menu_Print();
	int num_jogadores;
	scanf("%d", &num_jogadores);
	while(num_jogadores < 2 || num_jogadores > 4){
		printf(" Numero de jogadores invalido!\n ");
		scanf("%d", &num_jogadores);
	}
	player_t **players = (player_t **) malloc(num_jogadores * sizeof(player_t *));
	for(i = 0; i < num_jogadores; i++){
		players[i] = player_Create(bag);
		printf(" Digite o nome do jogador %d: ", i+1);
		scanf("%s", players[i]->name);
	}

	game_Play(table, bag, tabuleiro, players, num_jogadores);
	game_End(tabuleiro, players, num_jogadores);

	free(players);
	board_Destroy(tabuleiro);
	bag_Destroy(bag);

	return 0;
}