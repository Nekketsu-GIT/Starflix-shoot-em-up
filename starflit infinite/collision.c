#include "collision.h"
#include "alien.h"
#include "tirjoueur.h"
#include "../gfxEngine_shared/bfg_spriteEngine.h"
#include "animation.h"
#include "tiralien.h"
#include "joueur.h"
#include "score.h"

int psno,alno,asno;

void verification_collision_ps_alien(void)
{


    for(psno=0; psno<PS_MAX; psno++)
    {
        if(ps_gettype(psno)!=PS_INACTIF)
        {
            for(alno=0; alno<AL_MAX; alno++)
            {
                if(al_gettype(alno)!=AL_INACTIF)
                {

                    if(spr_isSpriteCollide(ps_getsprno(psno),al_getsprno(alno))==1)
                    {
                      if (al_getvie(alno)>1)
                        {
                            al_setvie(alno,al_getvie(alno)-1);
                            ao_creation(AO_PETITE_EXPLOSION,spr_getSpriteX(ps_getsprno(psno)),spr_getSpriteY(ps_getsprno(psno)));
                            ps_detruire(psno);
                        }
                        else
                        {
                            ao_creation(AO_GROSSE_EXPLOSION,spr_getSpriteX(al_getsprno(alno)),spr_getSpriteY(al_getsprno(alno)));
                            ps_detruire(psno);
                            al_detruire();
                            playSound(1,0);
                            score_set(score_get()+10);


                        }

                       break;
                    }

                }

            }
        }

    }

}

void verification_collision_as_joueur(void)
{

    for(asno=0; asno<AS_MAX; asno++)
    {
        if(as_gettype(asno)!=AS_INACTIF)
        {

            if(spr_isSpriteCollide(as_getsprno(asno),pl_getsprno())==1)
            {
              if (pl_getvie()>0)
                {
                    pl_setvie(pl_getvie()-1);
                    ao_creation(AO_PETITE_EXPLOSION,spr_getSpriteX(pl_getsprno()),spr_getSpriteY(pl_getsprno()));
                    as_detruire(asno);
                }
                else
                {
                    ao_creation(AO_GROSSE_EXPLOSION,spr_getSpriteX(pl_getsprno()),spr_getSpriteY(pl_getsprno()));
                    as_detruire(asno);
                    pl_detruire();
                    al_tdetruire();



                }
               break;
            }
        }
    }

}

