#ifndef JOUEUR_H
#define JOUEUR_H

#define PL_COOLDOWN 30

typedef struct
{
    int sprno;
    int vie;
    int cooldown;
}s_joueur;

void initialisation_du_joueur();

void action_du_joueur();

int pl_getcooldown(void);
void pl_setcooldown(int cd);

int pl_getvie(void);
void pl_setvie(int nbl);

int pl_getsprno(void);

void pl_detruire(void);

#endif // JOUEUR_H

