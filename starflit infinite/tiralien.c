#include "tiralien.h"
#include "maBibli.h"
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"

s_tiralien as[AS_MAX];

int i;


void initialisation_tir_alien()
{

    for(i=0;i<AS_MAX;i++)
    {
        as[i].type=AS_INACTIF;
        as[i].sprno=-1;
    }

}

int as_creation(int x,int y)
{

    for(i=0;i<AS_MAX;i++)
    {
        if(as[i].type==AS_INACTIF)
        {
            as[i].sprno=spr_reserveFreeSprite();
            if(as[i].sprno!=-1)
            {

                as[i].type=AS_ACTIF;
                spr_changeSpriteImage(as[i].sprno,IB_SHOOT_ALIEN_F0);
                spr_moveSprite(as[i].sprno,x,y);

                spr_setSpriteHitbox(as[i].sprno,0,0,17,58);

                return i;
            }
        }
    }

    return -1;
}

void as_moveall()
{

    for(i=0;i<AS_MAX;i++)
    {
        if(as[i].type!=AS_INACTIF)
           {

               spr_moveSpriteRelative(as[i].sprno,3,15);

               if(spr_getSpriteY(as[i].sprno)>480)
                  {
                      as_detruire(i);
                  }

           }
    }
}

void as_detruire(int asno)
{
    if(as[asno].type!=AS_INACTIF)
    {
        as[asno].type=AS_INACTIF;
        if(as[asno].sprno!=-1)
        {
            spr_releaseSprite(as[asno].sprno);
        }
    }
}

void as_tdetruire(void)
{
    for(i=0;i<AS_MAX;i++)
    {
        as_detruire(i);
    }
}

int as_gettype(int asno)
{
    return as[asno].type;
}

int as_getsprno(int asno)
{
    return as[asno].sprno;
}

