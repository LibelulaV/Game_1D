#ifndef _GAME_H_

#define _GAME_H_

#define WORLD_MAX_WIDTH 80
#define WORLD_MIN_WIDTH 0

#define PLAYER_MAX_LIFE 4
#define PLAYER_MAX_BULLETS 10

#define ENEMY_KILL_POINS 10; 
#define STAR_POINTS 50

#define PER_FRAME_SLEEP_MS 80
#define GAME_OVER_SLEEP_MS 4000

struct TPlayer {
	int m_pos;
	int m_life;
	int m_ammunition;
	int m_points;
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

extern TCharger charger;
extern TMedkit medkit;
extern TStar star;
extern TBomb bomb;

#endif