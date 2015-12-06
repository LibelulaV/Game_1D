#ifndef _ITEMS_H_

#define _ITEMS_H_

void itemsInit();
void itemsGenerate(); 
void itemsCheckPlayerCollisionsAndUpdate();

bool itemsExistMedkit();
bool itemsExistCharger();
bool itemsExistStar();
bool itemsExistBomb();

int itemsGetMedkitPos();
int itemsGetChargerPos();
int itemsGetStarPos();
int itemsGetBombPos();

#endif