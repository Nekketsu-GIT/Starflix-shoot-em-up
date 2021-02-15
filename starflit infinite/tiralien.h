#ifndef ALIENSHOOT_H
#define ALIEN_SHOOT_H

#define AS_MAX 20

#define AS_INACTIF 0
#define AS_ACTIF 1

typedef struct
{
    int type;
    int sprno;
}s_tiralien;

void initialisation_tir_alien();
int as_creation(int x,int y);
void as_detruire();
void as_tdetruire(void);
void as_moveall();
int as_gettype(int asno);
int as_getsprno(int asno);

#endif // ALIENSHOOT_H

