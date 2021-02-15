#include "alien.h"
#include "maBibli.h"
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "tiralien.h"

s_alien alien[AL_MAX];
int alien_violet_animation[]={IB_ALIEN_F0,IB_ALIEN_F1,-1};
int alien_flip_animation[]={IB_ALIEN_F2,IB_ALIEN_F3,-1};
int alno,i,cpt;

void initialisation_des_ennemies()
{
    int i;

    for(i=0;i<AL_MAX;i++)
    {
        alien[i].type=AL_INACTIF;
        alien[i].sprno=-1;
        alien[i].vie=0;
        alien[i].direction=0;
        alien[i].warmup=10;
    }
}

int creation_ennemies(int type,int x,int y,int vie,int direction)
{
    int i;
    for(i=0;i<AL_MAX;i++)
    {
        if(alien[i].type==AL_INACTIF)
        {
            alien[i].sprno=spr_reserveFreeSprite();
            if(alien[i].sprno!=-1)
            {
                if(type==AL_VIOLET)
                {
                    alien[i].type=type;
                    alien[i].direction=direction;
                    alien[i].vie=vie;
                    alien[i].warmup=rnd_random2(30,150);
                    spr_setSpriteAnimation2(alien[i].sprno,0,12,alien_violet_animation,ANIM_LOOP);
                    spr_animateSprite(alien[i].sprno,0);
                    spr_moveSprite(alien[i].sprno,(float)x,(float)y);

                    spr_setSpriteHitbox(alien[i].sprno,22,1,48,40);

                }
                if(type==AL_FLIP)
                {
                    alien[i].type=type;
                    alien[i].direction=direction;
                    alien[i].vie=vie;
                    alien[i].warmup=rnd_random2(30,150);
                    spr_setSpriteAnimation2(alien[i].sprno,0,12,alien_flip_animation,ANIM_LOOP);
                    spr_animateSprite(alien[i].sprno,0);
                    spr_moveSprite(alien[i].sprno,(float)x,(float)y);

                    spr_setSpriteHitbox(alien[i].sprno,29,27,37,35);

                }

                return i;

            }

        }
    }

    return -1;
}

void al_intern_move_violet(int no)
{
    spr_moveSpriteRelative(alien[no].sprno,alien[no].direction,0);

    if(spr_getSpriteX(alien[no].sprno)<0)
    {
        spr_moveSprite(alien[no].sprno,0,spr_getSpriteY(alien[no].sprno));
        alien[no].direction=alien[no].direction*-1;
    }
    else
    if(spr_getSpriteX(alien[no].sprno)>550)
    {
        spr_moveSprite(alien[no].sprno,550,spr_getSpriteY(alien[no].sprno));
        alien[no].direction=alien[no].direction*-1;
    }

    if(alien[no].warmup>0)
    {
        alien[no].warmup--;
    }
    else
    {
        as_creation(spr_getSpriteX(alien[no].sprno)+90,spr_getSpriteY(alien[no].sprno)+40);
        as_creation(spr_getSpriteX(alien[no].sprno),spr_getSpriteY(alien[no].sprno)+40);
        playSound(0,0);
        alien[no].warmup=rnd_random2(30,150);
    }



}

void al_intern_move_flip(int no)
{

    spr_moveSpriteRelative(alien[no].sprno,alien[no].direction,0);

    if(spr_getSpriteX(alien[no].sprno)<100)
    {
        spr_moveSprite(alien[no].sprno,100,spr_getSpriteY(alien[no].sprno));
        alien[no].direction=alien[no].direction*-1;
    }
    else
    if(spr_getSpriteX(alien[no].sprno)>450)
    {
        spr_moveSprite(alien[no].sprno,450,spr_getSpriteY(alien[no].sprno));
        alien[no].direction=alien[no].direction*-1;
    }

    if(alien[no].warmup>0)
    {
        alien[no].warmup--;
    }
    else
    {
        as_creation(spr_getSpriteX(alien[no].sprno)+90,spr_getSpriteY(alien[no].sprno)+40);
        as_creation(spr_getSpriteX(alien[no].sprno),spr_getSpriteY(alien[no].sprno)+40);
        alien[no].warmup=rnd_random2(50,150);
    }

}

void al_moveall(void)
{
    int i;
    for(i=0;i<AL_MAX;i++)
    {
        if(alien[i].type==AL_VIOLET)
        {
            al_intern_move_violet(i);
        }
        if(alien[i].type==AL_FLIP)
        {
            al_intern_move_flip(i);
        }
    }

}

int al_gettype(int alno)
{
    return alien[alno].type;
}

int al_getsprno(int alno)
{
    return alien[alno].sprno;
}

int al_getvie(int alno)
{
   return alien[alno].vie;
}

void al_setvie(int alno,int vie)
{
    alien[alno].vie=vie;
}

void al_detruire()
{
    spr_releaseSprite(alien[alno].sprno);
    alien[alno].type=AL_INACTIF;
}

void al_tdetruire()
{
    for(alno=0;alno<AL_MAX;alno++)
    {
        al_detruire();
    }
}

int al_compteur()
{

    cpt=0;

    for(i=0;i<AL_MAX;i++)
    {
        if(alien[i].type!=AL_INACTIF)
        {
            cpt++;
        }


    }

    return cpt;
}
