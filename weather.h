#ifndef _WEATHER_H_

#define _WEATHER_H_

void weatherInit(int world_width); 
void weatherEnd(); 
void weatherUpdate();
char weatherGetGroundChar(int x, char def_value);

#endif

