#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "game.h"
#include "items.h"
#include "bullets.h"

#define BOMB_SPAM_RANK 30
#define STAR_SPAM_RANK 970

#define STAR_POINTS 50

struct TItem {
	int m_pos;
	bool m_exist;
};

struct TMedkit : public TItem {
	int m_healp;
};

static TItem charger;
static TMedkit medkit;
static TItem star;
static TItem bomb;

void itemsInit() {
	charger.m_exist = false;
	medkit.m_exist = false;
	star.m_exist = false;
	bomb.m_exist = false;
}

void itemsGenerate() {

	int special_item_spam_value = rand() % 1000 + 1;

	if (player.m_ammunition <= 3 && !charger.m_exist) {
		
		if (rand() % 2) {
			charger.m_exist = true;
			int pos = player.m_pos;
			while (player.m_pos == pos ||
				(medkit.m_exist && medkit.m_pos == pos) ||
				(bomb.m_exist && bomb.m_pos == pos) ||
				(star.m_exist && star.m_pos == pos)) {

				pos = rand() % (WORLD_MAX_WIDTH - 2);
			}
			charger.m_pos = pos;
		}
	}
	if (player.m_life <= 2 && !medkit.m_exist) {

		if (rand() % 2) {
			medkit.m_exist = true;
			int pos = player.m_pos;
			while (player.m_pos == pos ||
				(charger.m_exist && charger.m_pos == pos) ||
				(bomb.m_exist && bomb.m_pos == pos) ||
				(star.m_exist && star.m_pos == pos)) {

				pos = rand() % (WORLD_MAX_WIDTH - 2);
			}
			medkit.m_pos = pos;
			medkit.m_healp = (rand() % 2 + 2);
		}
	}

	if (special_item_spam_value > STAR_SPAM_RANK && !star.m_exist) {
		star.m_exist = true;
		int pos = player.m_pos;
		while (player.m_pos == pos ||
			(medkit.m_exist && medkit.m_pos == pos) ||
			(bomb.m_exist && bomb.m_pos == pos) ||
			(charger.m_exist && charger.m_pos == pos)) {

			pos = rand() % (WORLD_MAX_WIDTH - 2);
		}
		star.m_pos = pos;
	}
	else if (special_item_spam_value < BOMB_SPAM_RANK && !bomb.m_exist && player.m_points >= 100) {
		bomb.m_exist = true;
		int pos = player.m_pos;
		while (player.m_pos == pos ||
			(medkit.m_exist && medkit.m_pos == pos) ||
			(star.m_exist && star.m_pos == pos) ||
			(charger.m_exist && charger.m_pos == pos)) {

			pos = rand() % (WORLD_MAX_WIDTH - 2);
		}
		bomb.m_pos = pos;
	}
}

void itemsCheckPlayerCollisionsAndUpdate() {
	if (star.m_exist && player.m_pos == star.m_pos) {
		star.m_exist = false;
		Beep(3000, 100);
		player.m_points += STAR_POINTS;
	}
	else if (charger.m_exist && player.m_pos == charger.m_pos) {
		charger.m_exist = false;
		Beep(3000, 100);
		player.m_ammunition = PLAYER_MAX_BULLETS;
	}
	else if (medkit.m_exist && player.m_pos == medkit.m_pos) {
		medkit.m_exist = false;
		Beep(3000, 100);
		if (player.m_life + medkit.m_healp >= PLAYER_MAX_LIFE)
			player.m_life = PLAYER_MAX_LIFE;
		else player.m_life += medkit.m_healp;
	}
	else if (bomb.m_exist) {
		if (player.m_pos == bomb.m_pos) {
			bomb.m_exist = false;
			Beep(1000, 100);
			player.m_points = 0;
		}
		else if (bulletsIsItemCollition(bomb.m_pos)) {
			bomb.m_exist = false;
			Beep(4000, 100);
		}
	}
}

bool itemsExistMedkit() {
	return medkit.m_exist; 
}

bool itemsExistCharger() {
	return charger.m_exist;
}

bool itemsExistStar() {
	return star.m_exist;
}

bool itemsExistBomb() {
	return bomb.m_exist;
}

int itemsGetMedkitPos() {
	return medkit.m_pos; 
}

int itemsGetChargerPos() {
	return charger.m_pos;
}

int itemsGetStarPos() {
	return star.m_pos;
}

int itemsGetBombPos() {
	return bomb.m_pos;
}