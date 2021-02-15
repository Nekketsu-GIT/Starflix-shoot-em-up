#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "joueur.h"
#include "maBibli.h"
#include "tirjoueur.h"

s_joueur joueur;


void initialisation_du_joueur()
{
    joueur.sprno=spr_reserveFreeSprite();
    joueur.cooldown=0;
    joueur.vie=3;

    spr_changeSpriteImage(joueur.sprno,IB_PLAYER_F0);
    spr_moveSprite(joueur.sprno,250,400);

    spr_setSpriteHitbox(joueur.sprno,1,22,63,72);
}

void action_du_joueur()
{
    int verification;

    if(joueur.cooldown>0)
    {
        joueur.cooldown--;
    }

    checkController();


    if(getKeyLeft()==1&&1<spr_getSpriteX(joueur.sprno))
    {
        spr_moveSpriteRelative(joueur.sprno,-5,0);
    }
    if(getKeyRight()==1&&spr_getSpriteX(joueur.sprno)<550)
    {
        spr_moveSpriteRelative(joueur.sprno,5,0);
    }
    if(getKeyUp()==1&&0<spr_getSpriteY(joueur.sprno))
    {
        spr_moveSpriteRelative(joueur.sprno,0,-3);
    }
    if(getKeyDown()==1&&spr_getSpriteY(joueur.sprno)<400)
    {
        spr_moveSpriteRelative(joueur.sprno,0,3);
    }

    if((getKeyA()==1)&&(joueur.cooldown==0))
    {
        playSound(0,0);
        verification=ps_creation((int)spr_getSpriteX(joueur.sprno)+90,(int)spr_getSpriteY(joueur.sprno));
        joueur.cooldown=PL_COOLDOWN;

        if(verification!=-1)
        {
            joueur.cooldown=PL_COOLDOWN;
        }

        ps_creation((int)spr_getSpriteX(joueur.sprno),(int)spr_getSpriteY(joueur.sprno));
    }
}

int pl_getcooldown(void)
{
    return joueur.cooldown;
}

void pl_setcooldown(int cd)
{
    joueur.cooldown=cd;
}


int pl_getvie(void)
{
    return joueur.vie;
}

void pl_setvie(int nbl)
{
    joueur.vie=nbl;
}


int pl_getsprno(void)
{
    return joueur.sprno;
}

void pl_detruire(void)
{
    spr_releaseSprite(joueur.sprno);

}
