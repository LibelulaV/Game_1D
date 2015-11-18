#pragma warning(disable: 4820)
#pragma warning(disable: 4710)
#pragma warning(disable: 4668)

#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define WORLD_MAX_WIDTH 80
#define WORLD_MIN_WIDTH 0

#define GROUND_TEXTURE '_'
#define PLAYER 'X'
#define ENEMY 'O'

#define RIGHT_BULLET '>'
#define LEFT_BULLET '<'

#define PER_FRAME_SLEEP_MS 80

struct TBullet {
	int m_pos;
	bool m_exist;
};

struct TEnemy {
	int m_pos;
	bool m_exist;
	int m_dir;
};

int main() {
	// World state
	int pos = WORLD_MAX_WIDTH / 2;

	TBullet rightBullet;
	rightBullet.m_exist = false;

	TBullet leftBullet;
	leftBullet.m_exist = false;

	TEnemy enemy;
	enemy.m_exist = false;

	// Game code
	printf("\n\n\n\n\n\n\n\n\n\n");

	bool gameOver = false;
	int key = 0;
	do {
		char world[WORLD_MAX_WIDTH];
		for (int i = 0; i < WORLD_MAX_WIDTH; i++) {
			if (i == pos)
				world[i] = PLAYER;
			else if (leftBullet.m_exist && i == leftBullet.m_pos)
				world[i] = LEFT_BULLET;
			else if (rightBullet.m_exist && i == rightBullet.m_pos)
				world[i] = RIGHT_BULLET;
			else if (enemy.m_exist && i == enemy.m_pos)
				world[i] = ENEMY;
			else
				world[i] = GROUND_TEXTURE;
			world[WORLD_MAX_WIDTH - 1] = '\0';
		}

		printf("%s", world);
		printf("\r");

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

		if (enemy.m_exist) {
			enemy.m_pos += enemy.m_dir;
			if (abs(pos - enemy.m_pos) <= 1) {
				gameOver = true;
				enemy.m_exist = false;
			}
			else if (enemy.m_dir == -1 && rightBullet.m_exist) {
				if (abs(rightBullet.m_pos - enemy.m_pos) <= 1) {
					enemy.m_exist = false;
					rightBullet.m_exist = false;
				}
			}
			else if (enemy.m_dir == 1 && leftBullet.m_exist) {
				if (abs(leftBullet.m_pos - enemy.m_pos) <= 1) {
					enemy.m_exist = false;
					leftBullet.m_exist = false;
				}
			}
		}
		else {
			enemy.m_exist = true;
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
				if (pos > WORLD_MIN_WIDTH)
					pos--;
				break;
			}
			case 'd': {
				if (pos < (WORLD_MAX_WIDTH - 2))
					pos++;
				break;
			}
			case 'q': {
				if (pos > WORLD_MIN_WIDTH && !leftBullet.m_exist) {
					leftBullet.m_exist = true;
					leftBullet.m_pos = pos - 1;
				}
				break;
			}
			case 'e': {
				if (pos < (WORLD_MAX_WIDTH - 2) && !rightBullet.m_exist) {
					rightBullet.m_exist = true;
					rightBullet.m_pos = pos + 1;
				}
				break;
			}
			}
		}

		Sleep(PER_FRAME_SLEEP_MS);

	} while (key != 32 && !gameOver); // 32: blanck space

	if (gameOver) {
		for (int i = 0; i < WORLD_MAX_WIDTH; i++) {
			if (i == (WORLD_MAX_WIDTH / 2) - 5) {
				printf("GAME OVER");
				i = i + 10;
			}
			else printf("%c", 22);
		}
		Sleep(PER_FRAME_SLEEP_MS * 100);
	}
	return 0;
}