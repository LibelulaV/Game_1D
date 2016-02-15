#pragma warning(disable: 4820)
#pragma warning(disable: 4514)
#pragma warning(disable: 4668)
//#pragma warning(disable: 4710)

#include "game.h"
#include "console.h"
#include "render.h"
#include "items.h"
#include "weather.h"
#include "ranking.h"
#include "bullets.h"
#include "enemies.h"

#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

// player
TPlayer player;

static bool game_over; 
static bool exit_game; 

int main() {
	int key = 0;
	do {
		// world 
		weatherInit(WORLD_MAX_WIDTH); 

		PlaySound(TEXT("song_of_storms.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

		player.m_pos = WORLD_MAX_WIDTH / 2 ;
		player.m_life = PLAYER_MAX_LIFE; 
		player.m_ammunition = PLAYER_MAX_BULLETS;
		player.m_points = 0; 

		game_over = false;
		exit_game = false; 

		itemsInit();

		srand(static_cast<unsigned int>(time(NULL)));

		// play 
		do { 
			// world 
			paintWorldState(); 

			enemiesGenerate(); 
			itemsGenerate();

			itemsCheckPlayerCollisionsAndUpdate();
		
			if (enemiesIsPlayerCollition()) {
				player.m_life--;
					if (player.m_life <= 0) 
						game_over = true;
			}
		
			enemiesCheckBulletsCollition();

			// player actions
			if (_kbhit()) {
				key = _getch();
				switch (key) {
					case 'q': 
						if (player.m_pos > WORLD_MIN_WIDTH)
							player.m_pos--;
						break; 
					case 'w': 
						if (player.m_pos < (WORLD_MAX_WIDTH - 2))
							player.m_pos++;
						break; 
					case 'o': 
						if (player.m_pos > WORLD_MIN_WIDTH && player.m_ammunition) {
							bulletsShotLeft();
							player.m_ammunition--;
						}
						break; 
					case 'p': 
						if (player.m_pos < (WORLD_MAX_WIDTH - 2) && player.m_ammunition) {
							bulletsShotRight();
							player.m_ammunition--; 
						}
						break;
				}
			}
	
			if(!enemiesIsEmpty())
				enemiesUpdate();

			if (!bulletsIsEmpty())
				bulletsUpdateState();

			weatherUpdate();
			
			Sleep(PER_FRAME_SLEEP_MS);
			consoleGoTo(0, 0); 

		} while (key!= 27 && !game_over); // 27: ESC

		consoleClear();
		
		PlaySound(NULL, NULL, NULL);

		enemiesEnd(); 
		bulletsEnd(); 
		weatherEnd(); 

		// end of game information
		if (game_over) {
			PlaySound(TEXT("game_over_mario.wav"), NULL, SND_FILENAME | SND_ASYNC | NULL);
			paintGameOver(); 
			Sleep(GAME_OVER_SLEEP_MS); 
			if(rankingIsRecord(player.m_points))
				rankingRecordScore(player.m_points); 
			if (!rankingIsEmpty()) {
				consoleClear();
				rankingPrintScores();
			}
			printf("\n\n Press ENTER to start the game. Press any other key to quit.");
			key = _getch(); 
			if (key != 13) // 13: ENTER
				exit_game = true; 
		}
		consoleClear();

	} while (key != 27 && !exit_game); // 27: ESC

	rankingEnd(); 
	
	return 0; 
}