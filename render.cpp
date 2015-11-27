#include "weather.h"
#include "render.h"
#include "game.h"
#include "bullets.h"

#include <stdio.h>
#include <windows.h>

#define GROUND_TEXTURE '_'
#define PLAYER 'X'
#define ENEMY 'O'
#define CHARGER '='
#define MED_KIT '\3'

#define STAR '\17'
#define BOMB 'o'

#define RIGHT_BULLET '>'
#define LEFT_BULLET '<'

enum  EColor {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GREY,
	DARK_GREY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE,
};

void setTextColor(EColor color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color)); 
}

void paintPlayerStats() {
	setTextColor(WHITE);
	printf("\n Ammunition:\t");
	for (int i = 0; i < player.m_ammunition; i++) {
		setTextColor(LIGHT_GREY);
		printf("%c", RIGHT_BULLET);
		setTextColor(WHITE);
	}
	printf("\n Lifes:\t\t");
	for (int i = 0; i < player.m_life; i++) {
		setTextColor(RED);
		printf("%c", MED_KIT);
		setTextColor(WHITE);
	}
	printf("\n Score:\t\t");
	setTextColor(LIGHT_GREEN);
	printf("%d\n", player.m_points);
	
}

void paintWorldState() {

	// painting scenario
	paintPlayerStats();
	paintBackGround(); 

	// generating world
	for (int i = 0; i < WORLD_MAX_WIDTH; i++) {
		int direction = bulletsGetBulletDirection(i);
		if (i == player.m_pos) {
			setTextColor(WHITE);
			printf("%c", PLAYER); 
		}
		else if (direction) { // if direction != 0, there is a bullet.  
			if (direction == 1) {
				setTextColor(LIGHT_GREY);
				printf("%c", RIGHT_BULLET);
			}
			else {
				setTextColor(LIGHT_GREY);
				printf("%c", LEFT_BULLET);
			}
		}
		else if (enemy.m_exist && i == enemy.m_pos) {
			setTextColor(BROWN);
			printf("%c", ENEMY);
		}	
		else if (charger.m_exist && i == charger.m_pos) {
			setTextColor(DARK_GREY);
			printf("%c", CHARGER);
		}
		else if (medkit.m_exist && i == medkit.m_pos) {
			setTextColor(RED);
			printf("%c", MED_KIT);
		}
		else if (star.m_exist && i == star.m_pos) {
			setTextColor(YELLOW);
			printf("%c", STAR);
		}
		else if (bomb.m_exist && i == bomb.m_pos) {
			setTextColor(MAGENTA);
			printf("%c", BOMB);
		}
		else {
			char g = weatherGetGroundChar(i, GROUND_TEXTURE);
			if (g == GROUND_TEXTURE) 
				setTextColor(LIGHT_GREEN);
			else setTextColor(LIGHT_CYAN);
			printf("%c", g);
		}
	}
}

void paintBlanks(int n) {
	for (int i = 0; i < n; i++) {
		printf(" ");
	}
}

void paintGameOver() {
	int blank_space = (WORLD_MAX_WIDTH / 2) - 6;

	// skull
	printf("\n\n\n\n\n\n\n");
	setTextColor(LIGHT_GREY);
	paintBlanks(blank_space); 
	printf("   _____  \n"); 
	paintBlanks(blank_space);
	printf("  /     \\  \n");
	paintBlanks(blank_space);
	printf(" | () () |\n");
	paintBlanks(blank_space);
	printf("  \\  ^  / \n");
	paintBlanks(blank_space);
	printf("   |||||  \n");
	paintBlanks(blank_space);
	printf("   |||||  \n");
	setTextColor(WHITE);
	printf("\n\n\n"); 

	// game over msg
	for (int i = 0; i < WORLD_MAX_WIDTH; i = i + 2) {
		if (i == blank_space) {
			setTextColor(RED);
			printf(" GAME OVER");
			i = i + 10;
		}
		else {
			setTextColor(CYAN);
			printf(" =");
		}
	}
	setTextColor(WHITE);

	// score
	printf("\n\n\n\n\n\n\n\n\n\n Final Score:\t"); 
	setTextColor(LIGHT_GREEN);
	printf("%d", player.m_points);	
	setTextColor(WHITE);
}

void paintScore(int n, char name[20], int points) {
	if (n == 1)
		printf("\n\t= = = = = RANKING = = = = =\n\n"); 
	printf("\tPlayer %d: %s - %d\n", n, name, points);
}

void paintBackGround() {
	if (WORLD_MAX_WIDTH >= 80) { 
		setTextColor(DARK_GREY);
		printf("                                      _                                      \n");
		printf("                            .-.      / \\        _                           \n"); 
		setTextColor(WHITE); 
		printf("                ^^");
		setTextColor(DARK_GREY);
		printf("         /   \\    /^./\\__   _/ \\                        \n");
		printf("              _        .--'\\/\\_ \\__/.      \\ /    \\ ");
		setTextColor(WHITE); 
		printf(" ^^"); 
		setTextColor(DARK_GREY); 
		printf("  ___            \n");
		printf("             / \\_    _/ ^      \\/  __  :'   /\\/\\  /\\  __/   \\          \n");
		printf("            /    \\  /    .'   _/  /  \\   ^ /    \\/  \\/ .`'\\_/\\         \n");
		printf("           /\\/\\  /\\/ :' __  ^/  ^/    `--./.'  ^  `-.\\ _    _:\\ _       \n");
		printf("          /    \\/  \\  _/  \\-' __/.' ^ _   \\_   .'\\   _/ \\ .  __/ \\    \n"); 
		printf("        /\\  .-   `. \\/     \\ / -.   _/ \\ -. `_/   \\ /    `._/  ^  \\    \n");
		printf("       /  `-.__ ^   / .-'.--'    . /    `--./ .-'  `-.  `-. `.  -  `.        \n");
		setTextColor(CYAN); printf("     @");
		setTextColor(DARK_GREY);
		printf("/        `.  / /      `-.   /  .-'   / .   .'   \\    \\  \\  .-  \\");
		setTextColor(CYAN);
		printf("0  \n");
		printf("     @@(880@)@00 @)&@&(88&@.-_=_-=_-=_-=_-=_.8@0 &@&&8(80@08)(8@08 80@)0     \n");
		printf("      @88:::&(&8&&8::&8&8:&`.~-_~~-~~_~-~_~-~~=.'@(&0::::0@8&8)::&#@8::::    \n");
		printf("      `::::::80@@0:::::@0&8:`.=~~-.~~-.~~=..~'8::::::::&@8:::::&8::::::'     \n");
		printf("       `::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::'      \n\n\n");
		setTextColor(WHITE);
	} 
	else printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); 
}