#pragma warning(disable: 4820)
#pragma warning(disable: 4514)
#pragma warning(disable: 4668)
//#pragma warning(disable: 4710)

#include "game.h"
#include "render.h"
#include "items.h"
#include "weather.h"
#include "ranking.h"
#include "bullets.h"

#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// characters
TPlayer player;
TEnemy enemy;

// items
TCharger charger;
TMedkit medkit;
TStar star;
TBomb bomb;

static bool game_over; 
static bool exit_game; 

int main() {
	int key = 0;
	do {
		weatherInit(WORLD_MAX_WIDTH); 

		// world state
		player.m_pos = WORLD_MAX_WIDTH / 2 ;
		player.m_life = PLAYER_MAX_LIFE; 
		player.m_ammunition = PLAYER_MAX_BULLETS;
		player.m_points = 0; 
	
		enemy.m_exist = false; 

		charger.m_exist = false; 
		medkit.m_exist = false; 
		star.m_exist = false; 
		bomb.m_exist = false; 

		game_over = false;
		exit_game = false; 

		// play 
		do { 
			// world 
			paintWorldState(); 
			weatherUpdate(); 

			// items effects 
			itemsCollisionsCheck();

			// enemy
			if (enemy.m_exist) {
				enemy.m_pos += enemy.m_dir; 
				if (bulletsIsCharacterCollition(enemy.m_pos)) {
					enemy.m_exist = false; 
					player.m_points += ENEMY_KILL_POINS;
				}
				else if (abs(player.m_pos - enemy.m_pos) <= 1) {
					enemy.m_exist = false;
					player.m_life--;
					if (player.m_life <= 0) {
						game_over = true;
					}
				}
			}
			else { // TODO: enemy random spam (?) 
				enemy.m_exist = true; 
				srand(static_cast<unsigned int>(time(NULL)));
				if (rand() % 2) {
					enemy.m_dir = 1; 
					enemy.m_pos = WORLD_MIN_WIDTH; 
				}
				else {
					enemy.m_dir = -1;
					enemy.m_pos = WORLD_MAX_WIDTH - 1; 
				}
			}

			// player actions
			if (_kbhit()) {
				key = _getch();
				switch (key) {
					case 'a': 
						if (player.m_pos > WORLD_MIN_WIDTH)
							player.m_pos--;
						break; 
					case 'd': 
						if (player.m_pos < (WORLD_MAX_WIDTH - 2))
							player.m_pos++;
						break; 
					case 'j': 
						if (player.m_pos > WORLD_MIN_WIDTH && player.m_ammunition) {
							bulletsShotLeft(); 
							player.m_ammunition--;
						}
						break; 
					case 'l': 
						if (player.m_pos < (WORLD_MAX_WIDTH - 2) && player.m_ammunition) {
							bulletsShotRight();
							player.m_ammunition--; 
						}
						break;
				}
			}

			// bullets
			if (!bulletsIsEmpty())
				bulletsUpdateState();

			// items generation
			itemsRandomGeneration(); 

			Sleep(PER_FRAME_SLEEP_MS);
			system("cls");

		} while (key!= 27 && !game_over); // 32: blanck space

		bulletsEnd(); 
		weatherEnd(); 

		// end of game information
		if (game_over) {
			paintGameOver(); 
			Sleep(GAME_OVER_SLEEP_MS); 
			if(rankingIsRecord(player.m_points))
				rankingRecordScore(player.m_points); 
			if (!rankingIsEmpty()) {
				system("cls");
				rankingPrintScores();
			}
			printf("\n\n Press ENTER to start the game. Press any other key to quit.");
			key = _getch(); 
			if (key != 13) // 13: ENTER
				exit_game = true; 
		}
	} while (key != 27 && !exit_game); // 27: ESC

	rankingEnd(); 
	
	return 0; 
}