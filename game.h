#ifndef _GAME_H_

#define _GAME_H_

#define WORLD_MAX_WIDTH 80
#define WORLD_MIN_WIDTH 0

#define PLAYER_MAX_LIFE 5
#define PLAYER_MAX_BULLETS 10

#define PER_FRAME_SLEEP_MS 50
#define GAME_OVER_SLEEP_MS 8000

struct TPlayer {
	int m_pos;
	int m_life;
	int m_ammunition;
	int m_points;
};

extern TPlayer player;

#endif