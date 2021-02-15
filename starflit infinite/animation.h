#ifndef AO_H
#define AO_H

#define MAX_AO          10

#define AO_INACTIF      0
#define AO_PETITE_EXPLOSION    1
#define AO_GROSSE_EXPLOSION    2

typedef struct
{
    int type;
    int sprno;
} s_ao;

void ao_initialisation(void);
void ao_creation(int type,int x,int y);
void ao_detruire(int aono);
void ao_tdetruire();
void ao_updateAll();

#endif // AO_H

