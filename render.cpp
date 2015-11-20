#include "weather.h"
#include "render.h"
#include "game.h"

#include <stdio.h>

void paintWorldState() {
	// generating world
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
			world[i] = weatherGetGroundChar(i, GROUND_TEXTURE);
		world[WORLD_MAX_WIDTH - 1] = '\0';
	}
	// printing world
	printf("\n Ammunition:\t");
	for (int i = 0; i < player.m_ammunition; i++) {
		printf("%c", RIGHT_BULLET);
	}
	printf("\n Lifes:\t\t");
	for (int i = 0; i < player.m_life; i++) {
		printf("%c", MED_KIT);
	}
	printf("\n Score:\t\t%d\n", player.m_points);
	paintBackGround(); 
	printf("%s", world);
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
	printf("\n\n\n"); 

	// game over msg
	for (int i = 0; i < WORLD_MAX_WIDTH; i = i + 2) {
		if (i == blank_space) {
			printf(" GAME OVER");
			i = i + 10;
		}
		else printf(" =");
	}

	// score
	printf("\n\n\n\n\n\n\n\n\n\n Final Score:\t%d\t\t\t\t\t Press any key to quit", player.m_points);
}

void paintBackGround() {
	if (WORLD_MAX_WIDTH >= 80) { 
		printf("                                      _                                      \n");
		printf("                            .-.      / \\        _                           \n"); 
		printf("                ^^         /   \\    /^./\\__   _/ \\                        \n"); 
		printf("              _        .--'\\/\\_ \\__/.      \\ /    \\  ^^  ___            \n");
		printf("             / \\_    _/ ^      \\/  __  :'   /\\/\\  /\\  __/   \\          \n");
		printf("            /    \\  /    .'   _/  /  \\   ^ /    \\/  \\/ .`'\\_/\\         \n");
		printf("           /\\/\\  /\\/ :' __  ^/  ^/    `--./.'  ^  `-.\\ _    _:\\ _       \n");
		printf("          /    \\/  \\  _/  \\-' __/.' ^ _   \\_   .'\\   _/ \\ .  __/ \\    \n"); 
		printf("        /\\  .-   `. \\/     \\ / -.   _/ \\ -. `_/   \\ /    `._/  ^  \\    \n");
		printf("       /  `-.__ ^   / .-'.--'    . /    `--./ .-'  `-.  `-. `.  -  `.        \n");
		printf("     @/        `.  / /      `-.   /  .-'   / .   .'   \\    \\  \\  .-  \\0  \n");
		printf("     @@(880@)@00 @)&@&(88&@.-_=_-=_-=_-=_-=_.8@0 &@&&8(80@08)(8@08 80@)0     \n");
		printf("      @88:::&(&8&&8::&8&8:&`.~-_~~-~~_~-~_~-~~=.'@(&0::::0@8&8)::&#@8::::    \n");
		printf("      `::::::80@@0:::::@0&8:`.=~~-.~~-.~~=..~'8::::::::&@8:::::&8::::::'     \n");
		printf("       `::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::'      \n\n\n");
	} 
	else printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); 
}