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

#define RIGHT_BULLET '>'
#define LEFT_BULLET '<'

#define PER_FRAME_SLEEP_MS 80

struct TBullet {
	int m_pos;
	bool m_exist;
};

int main() {
	// World state
	int player_pos = WORLD_MAX_WIDTH / 2;

	TBullet rightBullet;
	rightBullet.m_exist = false;

	TBullet leftBullet;
	leftBullet.m_exist = false;

	// Game code
	printf("\n\n\n\n\n\n\n\n\n\n");

	int key = 0;
	do {
		char world[WORLD_MAX_WIDTH];
		for (int i = 0; i < WORLD_MAX_WIDTH; i++) {
			if (i == player_pos)
				world[i] = PLAYER;
			else if (leftBullet.m_exist && i == leftBullet.m_pos)
				world[i] = LEFT_BULLET;
			else if (rightBullet.m_exist && i == rightBullet.m_pos)
				world[i] = RIGHT_BULLET;
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

		if (_kbhit()) {
			key = _getch();
			switch (key) {
			case 'a': {
				if (player_pos > WORLD_MIN_WIDTH)
					player_pos--;
				break;
			}
			case 'd': {
				if (player_pos < (WORLD_MAX_WIDTH - 2))
					player_pos++;
				break;
			}
			case 'q': {
				if (player_pos > WORLD_MIN_WIDTH && !leftBullet.m_exist) {
					leftBullet.m_exist = true;
					leftBullet.m_pos = player_pos - 1;
				}
				break;
			}
			case 'e': {
				if (player_pos < (WORLD_MAX_WIDTH - 2) && !rightBullet.m_exist) {
					rightBullet.m_exist = true;
					rightBullet.m_pos = player_pos + 1;
				}
				break;
			}
			}
		}

		Sleep(PER_FRAME_SLEEP_MS);

	} while (key != 32); // 32: blanck space

	return 0;
}