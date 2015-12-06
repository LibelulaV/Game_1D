#ifndef _ENEMIES_H_

#define _ENEMIES_H_

void enemiesGenerate();
void enemiesUpdate();
void enemiesCheckBulletsCollition();
int enemiesGetEnemyType(int x);
bool enemiesIsPlayerCollition();
bool enemiesIsEmpty();
void enemiesEnd();

#endif

