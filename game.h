#ifndef _GAME_H_

#define _GAME_H_

#define WORLD_MAX_WIDTH 80
#define WORLD_MIN_WIDTH 0

#define PLAYER_MAX_LIFE 4
#define PLAYER_MAX_BULLETS 10

#define ENEMY_KILL_POINS 10; 
#define STAR_POINTS 50

#define PER_FRAME_SLEEP_MS 80

#define GROUND_TEXTURE '_'
#define PLAYER 'X'
#define ENEMY 'O'
#define CHARGER '='
#define MED_KIT '\3'

#define STAR '\17'
#define BOMB 'o'

#define RIGHT_BULLET '>'
#define LEFT_BULLET '<'

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

extern TPlayer player;
extern TEnemy enemy;

extern TBullet rightBullet;
extern TBullet leftBullet;

extern TCharger charger;
extern TMedkit medkit;
extern TStar star;
extern TBomb bomb;

#endif