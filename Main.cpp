#pragma warning(disable: 4820)
#pragma warning(disable: 4710)
#pragma warning(disable: 4668)

#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define WORLD_MAX_WIDTH 80
#define WORLD_MIN_WIDTH 0

#define PLAYER_MAX_LIFE 4
#define PLAYER_MAX_BULLETS 10

#define GROUND_TEXTURE '_'
#define PLAYER 'X'
#define ENEMY 'O'
#define CHARGER '='
#define MED_KIT '+'

#define STAR '*'
#define BOMB 'o'

#define ENEMY_KILL_POINS 10; 
#define STAR_POINTS 50

#define RIGHT_BULLET '>'
#define LEFT_BULLET '<'

#define PER_FRAME_SLEEP_MS 90
#define GAME_OVER_SLEEP_MS 5000

struct TPlayer {
	int m_pos;
	int m_life;
	int m_ammunition;
	int m_points;
};

struct TBullet {
	int m_pos;
	bool m_exist;
};

struct TEnemy {
	int m_pos;
	bool m_exist;
	int m_dir;
};

struct TStar {
	int m_pos;
	bool m_exist;
};

struct TBomb {
	int m_pos;
	bool m_exist;
};

struct TCharger {
	int m_pos;
	bool m_exist;
};

struct TMedkit {
	int m_pos;
	bool m_exist;
	int m_healp;
};

void printPlayerInfo(TPlayer const player) {
	printf("\n Ammunition:\t");
	for (int i = 0; i < player.m_ammunition; i++) {
		printf(">");
	}
	printf("\n Lifes:\t\t");
	for (int i = 0; i < player.m_life; i++) {
		printf("|");
	}
	printf("\n Score:\t\t%d", player.m_points);
}

int main() {

	// World state
	TPlayer player;
	player.m_pos = WORLD_MAX_WIDTH / 2;
	player.m_life = PLAYER_MAX_LIFE;
	player.m_ammunition = PLAYER_MAX_BULLETS;
	player.m_points = 0;

	TBullet rightBullet;
	rightBullet.m_exist = false;

	TBullet leftBullet;
	leftBullet.m_exist = false;

	TEnemy enemy;
	enemy.m_exist = false;

	TCharger charger;
	charger.m_exist = false;

	TMedkit medkit;
	medkit.m_exist = false;

	TStar star;
	star.m_exist = false;

	TBomb bomb;
	bomb.m_exist = false;

	bool game_over = false;

	// Game code
	int key = 0;

	do {
		int special_item_spam_value = rand() % 100 + 1;

		char world[WORLD_MAX_WIDTH];
		for (int i = 0; i < WORLD_MAX_WIDTH; i++) {
			if (i == player.m_pos)
				world[i] = PLAYER;
			else if (leftBullet.m_exist && i == leftBullet.m_pos)
				world[i] = LEFT_BULLET;
			else if (rightBullet.m_exist && i == rightBullet.m_pos)
				world[i] = RIGHT_BULLET;
			else if (enemy.m_exist && i == enemy.m_pos)
				world[i] = ENEMY;
			else if (charger.m_exist && i == charger.m_pos)
				world[i] = CHARGER;
			else if (medkit.m_exist && i == medkit.m_pos)
				world[i] = MED_KIT;
			else if (star.m_exist && i == star.m_pos)
				world[i] = STAR;
			else if (bomb.m_exist && i == bomb.m_pos)
				world[i] = BOMB;
			else
				world[i] = GROUND_TEXTURE;
			world[WORLD_MAX_WIDTH - 1] = '\0';
		}
		printPlayerInfo(player);

		printf("\n\n\n\n\n\n\n");
		printf("%s", world);

		if (leftBullet.m_exist) {
			leftBullet.m_pos -= 1;
			if (leftBullet.m_pos < WORLD_MIN_WIDTH) {
				leftBullet.m_exist = false;
			}
		}

		if (rightBullet.m_exist) {
			rightBullet.m_pos += 1;
			if (rightBullet.m_pos >(WORLD_MAX_WIDTH - 2)) {
				rightBullet.m_exist = false;
			}
		}

		if (star.m_exist && player.m_pos == star.m_pos) {
			star.m_exist = false;
			player.m_points += STAR_POINTS;
		}

		if (bomb.m_exist) {
			if (player.m_pos == bomb.m_pos) {
				bomb.m_exist = false;
				player.m_points = 0;
			}
			else if (rightBullet.m_exist && rightBullet.m_pos == bomb.m_pos) {
				bomb.m_exist = false;
				rightBullet.m_exist = false;
			}
			else if (leftBullet.m_exist && leftBullet.m_pos == bomb.m_pos) {
				bomb.m_exist = false;
				leftBullet.m_exist = false;
			}
		}


		if (charger.m_exist && player.m_pos == charger.m_pos) {
			charger.m_exist = false;
			player.m_ammunition = PLAYER_MAX_BULLETS;
		}

		if (medkit.m_exist && player.m_pos == medkit.m_pos) {
			medkit.m_exist = false;
			if (player.m_life + medkit.m_healp <= PLAYER_MAX_LIFE)
				player.m_life = PLAYER_MAX_LIFE;
			else player.m_life += medkit.m_healp;
		}
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
		else {
			enemy.m_exist = true;
			srand(time(0));
			if (rand() % 2) {
				enemy.m_dir = 1;
				enemy.m_pos = WORLD_MIN_WIDTH;
			}
			else {
				enemy.m_dir = -1;
				enemy.m_pos = WORLD_MAX_WIDTH - 1;
			}
		}

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
			case 'q': {
				if (player.m_pos > WORLD_MIN_WIDTH && !leftBullet.m_exist && player.m_ammunition) {
					leftBullet.m_exist = true;
					leftBullet.m_pos = player.m_pos - 1;
					player.m_ammunition--;
				}
				break;
			}
			case 'e': {
				if (player.m_pos < (WORLD_MAX_WIDTH - 2) && !rightBullet.m_exist && player.m_ammunition) {
					rightBullet.m_exist = true;
					rightBullet.m_pos = player.m_pos + 1;
					player.m_ammunition--;
				}
				break;
			}
			}
		}
		if (player.m_ammunition <= 3 && !charger.m_exist) {
			charger.m_exist = true;
			int pos = player.m_pos;
			while (player.m_pos == pos ||
				(medkit.m_exist && medkit.m_pos == pos) ||
				(bomb.m_exist && bomb.m_pos == pos) ||
				(star.m_exist && star.m_pos == pos)) {
				srand(time(0));
				pos = rand() % (WORLD_MAX_WIDTH - 2);
			}
			charger.m_pos = pos;
		}
		if (player.m_life <= 2 && !medkit.m_exist) {
			medkit.m_exist = true;
			int pos = player.m_pos;
			while (player.m_pos == pos ||
				(charger.m_exist && charger.m_pos == pos) ||
				(bomb.m_exist && bomb.m_pos == pos) ||
				(star.m_exist && star.m_pos == pos)) {
				srand(time(0));
				pos = rand() % (WORLD_MAX_WIDTH - 2);
			}
			medkit.m_pos = pos;
			medkit.m_healp = (rand() % 2) * 1 + 1;
		}

		if (special_item_spam_value > 97 && !star.m_exist) {
			star.m_exist = true;
			int pos = player.m_pos;
			while (player.m_pos == pos ||
				(medkit.m_exist && medkit.m_pos == pos) ||
				(bomb.m_exist && bomb.m_pos == pos) ||
				(charger.m_exist && charger.m_pos == pos)) {
				srand(time(0));
				pos = rand() % (WORLD_MAX_WIDTH - 2);
			}
			star.m_pos = pos;
		}
		else if (special_item_spam_value < 2 && !bomb.m_exist) {
			bomb.m_exist = true;
			int pos = player.m_pos;
			while (player.m_pos == pos ||
				(medkit.m_exist && medkit.m_pos == pos) ||
				(star.m_exist && star.m_pos == pos) ||
				(charger.m_exist && charger.m_pos == pos)) {
				srand(time(0));
				pos = rand() % (WORLD_MAX_WIDTH - 2);
			}
			bomb.m_pos = pos;
		}
		Sleep(PER_FRAME_SLEEP_MS);
		system("cls");
	} while (key != 32 && !game_over); // 32: blanck space

	if (game_over) {
		printf("\n\n\n\n\n\n\n\n\n\n");
		for (int i = 0; i < WORLD_MAX_WIDTH; i = i + 2) {
			if (i == (WORLD_MAX_WIDTH / 2) - 6) {
				printf(" GAME OVER");
				i = i + 10;
			}
			else printf(" =");
		}
		printf("\n\n\n Final Score:\t\t%d\t\t\t Press any key to quit", player.m_points);
		_getch();
	}
	return 0;
}