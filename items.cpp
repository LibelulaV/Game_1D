#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "items.h"

#define BOMB_SPAM_RANK 970
#define STAR_SPAM_RANK 2

void itemsRandomGeneration() {
	if (player.m_ammunition <= 3 && !charger.m_exist) {
		srand(static_cast<unsigned int>(time(NULL)));
		if (rand() % 2) {
			charger.m_exist = true;
			int pos = player.m_pos;
			while (player.m_pos == pos ||
				(medkit.m_exist && medkit.m_pos == pos) ||
				(bomb.m_exist && bomb.m_pos == pos) ||
				(star.m_exist && star.m_pos == pos)) {
				srand(static_cast<unsigned int>(time(NULL)));
				pos = rand() % (WORLD_MAX_WIDTH - 2);
			}
			charger.m_pos = pos;
		}
	}
	if (player.m_life <= 2 && !medkit.m_exist) {
		srand(static_cast<unsigned int>(time(NULL)));
		if (rand() % 2) {
			medkit.m_exist = true;
			int pos = player.m_pos;
			while (player.m_pos == pos ||
				(charger.m_exist && charger.m_pos == pos) ||
				(bomb.m_exist && bomb.m_pos == pos) ||
				(star.m_exist && star.m_pos == pos)) {
				srand(static_cast<unsigned int>(time(NULL)));
				pos = rand() % (WORLD_MAX_WIDTH - 2);
			}
			medkit.m_pos = pos;
			medkit.m_healp = (rand() % 2) * 1 + 1;
		}
	}

	int special_item_spam_value = rand() % 1000 + 1;

	if (special_item_spam_value > BOMB_SPAM_RANK && !star.m_exist) {
		star.m_exist = true;
		int pos = player.m_pos;
		while (player.m_pos == pos ||
			(medkit.m_exist && medkit.m_pos == pos) ||
			(bomb.m_exist && bomb.m_pos == pos) ||
			(charger.m_exist && charger.m_pos == pos)) {
			srand(static_cast<unsigned int>(time(NULL)));
			pos = rand() % (WORLD_MAX_WIDTH - 2);
		}
		star.m_pos = pos;
	}
	else if (special_item_spam_value < STAR_SPAM_RANK && !bomb.m_exist && player.m_points > 100) {
		bomb.m_exist = true;
		int pos = player.m_pos;
		while (player.m_pos == pos ||
			(medkit.m_exist && medkit.m_pos == pos) ||
			(star.m_exist && star.m_pos == pos) ||
			(charger.m_exist && charger.m_pos == pos)) {
			srand(static_cast<unsigned int>(time(NULL)));
			pos = rand() % (WORLD_MAX_WIDTH - 2);
		}
		bomb.m_pos = pos;
	}
}

void itemsCollisionsCheck() {
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
}

