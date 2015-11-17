#pragma warning(disable: 4820)
#pragma warning(disable: 4710)
#pragma warning(disable: 4668)

#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define WORLD_MAX_WIDTH 80
#define WORLD_MIN_WIDTH 0
#define GROUND_TEXTURE "_"
#define PLAYER "X"
#define RIGHT_BULLET ">"
#define LEFT_BULLET "<"
#define SLEEP 80

struct TBullet {
	int m_pos;
	bool m_exist;
};

void newGame(char world[], unsigned int pos) {
	printf("\n\n\n\n\n\n\n\n\n\n");
	for (unsigned int i = 0; i < WORLD_MAX_WIDTH; i++) {
		world[i] = *GROUND_TEXTURE;
	}
	world[WORLD_MAX_WIDTH -1] = '\0';
	world[pos] = *PLAYER;
}

void moveRight(char world[], unsigned int pos) {
	world[pos] = *GROUND_TEXTURE;
	world[pos + 1] = *PLAYER;
}

void moveLeft(char world[], unsigned int pos) {
	world[pos] = *GROUND_TEXTURE;
	world[pos - 1] = *PLAYER;
}

void paintRightBullet(char world[], int posBullet) {
	world[posBullet] = *RIGHT_BULLET; 
}

void paintLeftBullet(char world[], int posBullet) {
	world[posBullet] = *LEFT_BULLET;
}

void removeBullet(char world[], int posBullet) {
	world[posBullet] = *GROUND_TEXTURE;
}

TBullet shotRight(char world[], unsigned int pos) {
	TBullet bullet; 
	bullet.m_exist = true; 
	bullet.m_pos = static_cast<int>(pos + 1); 
	paintRightBullet(world, bullet.m_pos); 
	return bullet; 
}

TBullet shotLeft(char world[], unsigned int pos) {
	TBullet bullet;
	bullet.m_exist = true;
	bullet.m_pos = static_cast<int>(pos - 1);
	paintLeftBullet(world, bullet.m_pos);
	return bullet;
}

int main(int, char[]) {
	int key = 0;
	char world[WORLD_MAX_WIDTH];
	unsigned int pos = WORLD_MAX_WIDTH / 2 ;

	newGame(world, pos);  // inicializacion mundo y personaje
 
	TBullet rightBullet; 
	rightBullet.m_exist = false; 

	TBullet leftBullet; 
	leftBullet.m_exist = false; 

	do { 
		printf("%s", world);
		printf("\r");

		if (leftBullet.m_exist) { // control avance bala izquierda
			removeBullet(world, leftBullet.m_pos);
			leftBullet.m_pos -= 1;
			if (leftBullet.m_pos < WORLD_MIN_WIDTH) {
				leftBullet.m_exist = false;
			}
			else paintLeftBullet(world, leftBullet.m_pos);
		}

		if (rightBullet.m_exist) { // control avance bala derecha
			removeBullet(world, rightBullet.m_pos);
			rightBullet.m_pos += 1;
			if (rightBullet.m_pos > (WORLD_MAX_WIDTH - 2)) {
				rightBullet.m_exist = false; 
			}
			else paintRightBullet(world, rightBullet.m_pos);
		}

		if (_kbhit()) {
			key = _getch();
			switch (key) {
				case 'a': { // mover izquierda
					if (pos > WORLD_MIN_WIDTH) {
						moveLeft(world, pos);
						pos--;
					}
					break; 
				}
				case 'd': { // mover derecha
					if (pos < (WORLD_MAX_WIDTH - 2)) {
						moveRight(world, pos);
						pos++;
					}
					break; 
				}
				case 'q': { // disparo izquierda
					if (pos > WORLD_MIN_WIDTH && !leftBullet.m_exist) {
						leftBullet = shotLeft(world, pos); 
					}
					break; 
				}
				case 'e': { // disparo derecha
					if (pos < (WORLD_MAX_WIDTH - 2) && !rightBullet.m_exist) {
						rightBullet = shotRight(world, pos);
					}
					break;
				}
			}
		}

		Sleep(SLEEP);

	} while (key!=32); // blanck space

	return 0; 
}