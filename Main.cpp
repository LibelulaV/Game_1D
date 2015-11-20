
#pragma warning(disable: 4820)
#pragma warning(disable: 4514)
#pragma warning(disable: 4668)
//#pragma warning(disable: 4710)

#include "game.h"
#include "render.h"
#include "items.h"
#include "weather.h"

#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

// characters
TPlayer player;
TEnemy enemy;

// bullets
TBullet rightBullet;
TBullet leftBullet;

// items
TCharger charger;
TMedkit medkit;
TStar star;
TBomb bomb;

static bool game_over; 

int main() {

	weatherInit(WORLD_MAX_WIDTH); 

	// world state
	player.m_pos = WORLD_MAX_WIDTH / 2 ;
	player.m_life = PLAYER_MAX_LIFE; 
	player.m_ammunition = PLAYER_MAX_BULLETS;
	player.m_points = 0; 
	
	enemy.m_exist = false; 

	rightBullet.m_exist = false; 
	leftBullet.m_exist = false; 

	charger.m_exist = false; 
	medkit.m_exist = false; 
	star.m_exist = false; 
	bomb.m_exist = false; 

	game_over = false;

	// game code
	int key = 0;

	do { 
		// world 
		paintWorldState(); 
		weatherUpdate(); 

		// items effects 
		itemsCollisionsCheck();

		// bullets effects 
		if (leftBullet.m_exist) { 
			leftBullet.m_pos -= 1;
			if (leftBullet.m_pos < WORLD_MIN_WIDTH) {
				leftBullet.m_exist = false;
			}
		}
		else if (rightBullet.m_exist) { 
			rightBullet.m_pos += 1;
			if (rightBullet.m_pos > (WORLD_MAX_WIDTH - 2)) {
				rightBullet.m_exist = false; 
			}
		}

		// enemy
		if (enemy.m_exist) {
			enemy.m_pos += enemy.m_dir; 
			if (abs(player.m_pos - enemy.m_pos) <= 1) {
				enemy.m_exist = false; 
				player.m_life--; 
				if (player.m_life <= 0) {
					game_over = true; 
				}	
			}
			else if (enemy.m_dir == -1 && rightBullet.m_exist) {
				if (abs(rightBullet.m_pos - enemy.m_pos) <= 1) {
					enemy.m_exist = false; 
					rightBullet.m_exist = false; 
					player.m_points += ENEMY_KILL_POINS;
				}
			}
			else if (enemy.m_dir == 1 && leftBullet.m_exist) {
				if (abs(leftBullet.m_pos - enemy.m_pos) <= 1) {
					enemy.m_exist = false;
					leftBullet.m_exist = false;
					player.m_points += ENEMY_KILL_POINS;
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
				case 'a': { 
					if (player.m_pos > WORLD_MIN_WIDTH)
						player.m_pos--;
					break; 
				}
				case 'd': { 
					if (player.m_pos < (WORLD_MAX_WIDTH - 2))
						player.m_pos++;
					break; 
				}
				case 'j': {
					if (player.m_pos > WORLD_MIN_WIDTH && !leftBullet.m_exist && player.m_ammunition && !rightBullet.m_exist) {
						leftBullet.m_exist = true;
						leftBullet.m_pos = player.m_pos - 1;
						player.m_ammunition--;
					}
					break; 
				}
				case 'l': {
					if (player.m_pos < (WORLD_MAX_WIDTH - 2) && !rightBullet.m_exist && player.m_ammunition && !leftBullet.m_exist) {
						rightBullet.m_exist = true;
						rightBullet.m_pos = player.m_pos + 1;
						player.m_ammunition--; 
					}
					break;
				}
			}
		}

		// items generation
		itemsRandomGeneration(); 

		Sleep(PER_FRAME_SLEEP_MS);
		system("cls");

	} while (key!=32 && !game_over); // 32: blanck space

	weatherEnd(); 

	// end of game information
	if (game_over) {
		paintGameOver(); 
		_getch(); 
	}
	return 0; 
}