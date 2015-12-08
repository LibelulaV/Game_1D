#pragma warning(disable: 4996) 

#include <list>
#include <windows.h>

#include "game.h"
#include "bullets.h"

struct TBullet {
	int m_pos;
	int m_direction; 
	bool m_collides; 
};

static std::list<TBullet *> bullets;
static std::list<TBullet *>::const_iterator it_bullets;

void bulletsShotLeft() {
	TBullet * bullet = new TBullet; 
	bullet->m_pos = player.m_pos - 1; 
	bullet->m_direction = - 1; 
	bullet->m_collides = false;
	bullets.push_front(bullet);
	Beep(1000, 100);
}

void bulletsShotRight() {
	TBullet * bullet = new TBullet;
	bullet->m_pos = player.m_pos + 1;
	bullet->m_direction = + 1;
	bullet->m_collides = false;
	bullets.push_front(bullet);
	Beep(1000, 100);
}

void bulletsUpdateState() { 
	it_bullets = bullets.begin(); 
	while (it_bullets != bullets.end()){
		(*it_bullets)->m_pos += (*it_bullets)->m_direction; 
		if ((*it_bullets)->m_pos < WORLD_MIN_WIDTH || (*it_bullets)->m_pos >(WORLD_MAX_WIDTH - 2) || (*it_bullets)->m_collides) {
			delete (*it_bullets);
			it_bullets = bullets.erase(it_bullets);
		}
		else it_bullets++;
	}
}

bool bulletsIsItemCollition(int x) {
	it_bullets = bullets.begin(); 
	bool collition = false; 
	while (!collition && it_bullets != bullets.end()) {
		if (x == (*it_bullets)->m_pos) {
			collition = true; 
			(*it_bullets)->m_collides = true; 
		}
			
		else it_bullets++; 
	}
	return collition; 
}

bool bulletsIsCharacterCollition(int x) {
	it_bullets = bullets.begin();
	bool collition = false;
	while (!collition && it_bullets != bullets.end()) {
		if (abs((*it_bullets)->m_pos - x) <= 1 && !(*it_bullets)->m_collides) {
			collition = true;
			Beep(8000, 100);
			(*it_bullets)->m_collides = true;
		}
		else it_bullets++;
	}
	return collition;
}

TBullet * bulletsGetBullet(int x) {
	it_bullets = bullets.begin();
	TBullet * bullet = NULL;
	bool exist = false; 
	while (!exist && it_bullets != bullets.end()) {
		if (x == (*it_bullets)->m_pos) {
			exist = true;
			bullet = (*it_bullets); 
		}
		else it_bullets++;
	}
	return bullet; 
}

int bulletsGetBulletDirection(int x) { // if 0 --> there is not a bullet.
	TBullet * b = bulletsGetBullet(x); 
	if (b != NULL)
		return b->m_direction; 
	else return 0; 
}

bool bulletsIsEmpty() {
	return bullets.empty(); 
}

void bulletsEnd() {
	it_bullets = bullets.begin();
	while(it_bullets != bullets.end()) {
		delete (*it_bullets); 
		it_bullets = bullets.erase(it_bullets); 
	}
	bullets.clear();
}

