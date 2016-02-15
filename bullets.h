#ifndef _BULLETS_H_

#define _BULLETS_H_

void bulletsShotLeft();
void bulletsShotRight();
void bulletsUpdateState(); 
bool bulletsIsItemCollition(int x);
bool bulletsIsCharacterCollition(int x, enemyType type);
int bulletsGetBulletDirection(int x); 
bool bulletsIsEmpty();
void bulletsEnd(); 

#endif
