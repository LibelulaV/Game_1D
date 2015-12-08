#pragma warning(disable: 4996) 

#include <list>
#include <time.h>
#include <math.h>
#include <windows.h>

#include "game.h"
#include "enemies.h"
#include "bullets.h"

#define MAX_ENEMIES 3

#define ENEMY_KILL_POINTS 10
#define BOSS_KILL_POINTS 20

enum enemyType { 
	Normal = 1, 
	Boss
};

struct TEnemy {
	int m_pos;
	int m_dir;
	bool m_collides;
	enemyType m_type; 
};

struct TBoss : public TEnemy {
	int m_life; 
};

static std::list<TEnemy *> enemies;
static std::list<TEnemy *>::const_iterator it_enemies;

void enemiesGenerate() {
	if (rand() % 2) {
		if (enemies.size() < MAX_ENEMIES) {
			if (rand() % 2) {
				TEnemy * enemy = new TEnemy();
				enemy->m_collides = false;
				enemy->m_type = Normal; 
				if (rand() % 2) {
					enemy->m_dir = 1;
					enemy->m_pos = WORLD_MIN_WIDTH;
				}
				else {
					enemy->m_dir = -1;
					enemy->m_pos = WORLD_MAX_WIDTH - 1;
				}
				enemies.push_back(enemy); 
			}
			else {
				if (player.m_points > 100) { // let's make this more interesting. 
					TBoss * enemy = new TBoss();
					enemy->m_collides = false;
					enemy->m_type = Boss;
					enemy->m_life = rand() % 2 + 2; 
					if (rand() % 2) {
						enemy->m_dir = 1;
						enemy->m_pos = WORLD_MIN_WIDTH;
					}
					else {
						enemy->m_dir = -1;
						enemy->m_pos = WORLD_MAX_WIDTH - 1;
					}
					enemies.push_back(enemy);
				}
			}
		}
	}
}

void enemiesUpdate() {
	it_enemies = enemies.begin();
	while (it_enemies != enemies.end()) {
		if ((*it_enemies)->m_collides){
			delete (*it_enemies);
			it_enemies = enemies.erase(it_enemies);
		}
		else {
			(*it_enemies)->m_pos += (*it_enemies)->m_dir; 
			it_enemies++;
		}
	}
}

void enemiesCheckBulletsCollition() {
	it_enemies = enemies.begin();
	while (it_enemies != enemies.end()) {
		if (bulletsIsCharacterCollition((*it_enemies)->m_pos)){
			if ((*it_enemies)->m_type == Boss) {
				TBoss * enemy = static_cast<TBoss *>(*it_enemies); 
				enemy->m_life -= 1; 
				if (enemy->m_life <= 0) {
					enemy->m_collides = true; 
					player.m_points += BOSS_KILL_POINTS;
				}
			}
			else {
				(*it_enemies)->m_collides = true;
				player.m_points += ENEMY_KILL_POINTS;
			}
		}
		it_enemies++;
	}
}

bool enemiesIsPlayerCollition() {
	it_enemies = enemies.begin();
	bool collition = false; 
	while (it_enemies != enemies.end()) {
		if (abs((*it_enemies)->m_pos - player.m_pos) <= 1) {
			(*it_enemies)->m_collides = true;
			if (!collition) {
				collition = true; 
				Beep(2000, 100);
			}
		}
		it_enemies++;
	}
	return collition; 
}

int enemiesGetEnemyType(int x) {
	it_enemies = enemies.begin();
	bool exist = false;
	while (it_enemies != enemies.end() && !exist) {
		if ((*it_enemies)->m_pos == x) 
			exist = true;
		else it_enemies++;
	}

	if (exist)
		return (*it_enemies)->m_type;
	else
		return 0; 
}

bool enemiesIsEmpty() {
	return enemies.empty();
}

void enemiesEnd() {
	it_enemies = enemies.begin();
	while (it_enemies != enemies.end()) {
		delete (*it_enemies);
		it_enemies = enemies.erase(it_enemies);
	}
	enemies.clear();
}
