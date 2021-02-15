#ifndef ALIEN_H
#define ALEN_H

#define AL_INACTIF 0
#define AL_VIOLET 1
#define AL_FLIP 2

#define AL_MAX 10

typedef struct
{
    int type;
    int sprno;
    int vie;
    int direction;
    int warmup;

}s_alien;

void initialisation_des_ennemies();

int creation_ennemies(int type,int x,int y,int vie,int direction);

void al_moveall(void);

int al_gettype(int alno);

int al_getsprno(int alno);

int al_getvie(int alno);

void al_setvie(int alno,int vie);

void al_detruire();

void al_tdetruire();

int al_compteur();

#endif // ALIEN_H
