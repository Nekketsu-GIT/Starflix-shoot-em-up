#ifndef PLAYERSHOOT_H
#define PLAYER_SHOOT_H

#define PS_MAX 4

#define PS_INACTIF 0
#define PS_ACTIF 1

typedef struct
{
    int type;
    int sprno;
}s_tirjoueur;

void initialisation_tir_du_joueur();
int ps_creation(int x,int y);
void ps_detruire(int psno);
void ps_tdetruire(void);
void ps_moveall();
int ps_gettype(int psno);
int ps_getsprno(int psno);

#endif // PLAYERSHOOT_H
