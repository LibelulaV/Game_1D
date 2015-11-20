#include "weather.h"

#include <stdlib.h>

static int * weatherState; 
static char states[] = {'|', '.', '^','´*','´', '-'};
static int weather_size;
static int cicle;
static int cicle_state;

void weatherInit(int world_width) {
	weatherState = static_cast<int *>(malloc(static_cast<unsigned int>(world_width*4)));
	int state = 0; 
	cicle = 0; 
	cicle_state = 0; 
	for (int i = 0; i < world_width; i++) {
		weatherState[i] = state; 
	}
	weather_size = world_width; 
}

void weatherEnd() {
	free(weatherState); 
}

void weatherUpdate() {
	for (int i = 0; i < weather_size; i++) {
		if (weatherState[i] < sizeof(states) - 1) 
			weatherState[i] += 1; 
		else {
			weatherState[i] = 0;
		}	
	}
	cicle_state++; 
	if (cicle_state >= sizeof(states)) {
		cicle_state = 0; 
		if (cicle)
			cicle = 0; 
		else cicle = 1; 
	}
}

char weatherGetGroundChar(int x, char def_value) {
	int state = weatherState[x]; 
	if ((sizeof(states) > state && ((x % 7) == 0 && cicle == 0)) || (sizeof(states) > state && ((x % 10) == 0 && cicle ==1)))
		return states[state]; 
	else
		return def_value; 
}


