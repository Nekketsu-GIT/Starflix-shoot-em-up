#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "maBibli.h"
#include "animation.h"

s_ao ao[MAX_AO];

int ao_explosion[] = {IB_EXPLODE_F0,IB_EXPLODE_F1,IB_EXPLODE_F2,IB_EXPLODE_F3,IB_EXPLODE_F4,IB_EXPLODE_F5,-1};

void ao_initialisation(void)
{
    int i;

    for (i=0;i<MAX_AO;i++)
    {
        ao[i].type = AO_INACTIF;
        ao[i].sprno = -1;
    }
}

void ao_creation(int type,int x,int y)
{
    int i;

    /* On parcourt tous le tableau des AO */
    for (i=0;i<MAX_AO;i++)
    {
        /* On en trouve un le libre */
        if (ao[i].type == AO_INACTIF)
        {
            /* On affecte le type à l'ao */
            ao[i].type = type;

            /* Selon le type d'ao on initialise ce qui va bien */
            if (type==AO_PETITE_EXPLOSION)
            {
                ao[i].sprno = spr_reserveFreeSprite();
                spr_moveSprite(ao[i].sprno,(float)x,(float)y);
                /* On set l'animation 0 du sprite */
                spr_setSpriteAnimation2(ao[i].sprno,0,5,ao_explosion,ANIM_NOLOOP);
                /* C'est une petite explosion, au lieu de faire des autres images,
                   on réduit juste le zoom*/
                spr_changeSpriteZoom(ao[i].sprno,0.5f,0.5f);
                /* Joue l'animation 0 */
                spr_animateSprite(ao[i].sprno,0);
            }
            else if (type==AO_GROSSE_EXPLOSION)
            {
                ao[i].sprno = spr_reserveFreeSprite();
                spr_moveSprite(ao[i].sprno,(float)x,(float)y);
                /* On set l'animation 0 du sprite */
                spr_setSpriteAnimation2(ao[i].sprno,0,5,ao_explosion,ANIM_NOLOOP);
                /* C'est une grosse explosion, au lieu de faire des autres images,
                   on augmente juste le zoom*/
                spr_changeSpriteZoom(ao[i].sprno,2.0f,2.0f);
                /* Joue l'animation 0 */
                spr_animateSprite(ao[i].sprno,0);
            }

            /* On quitte la boucle for parce qu'on à trouvé */
            break;
        }
    }
}

void ao_detruire(int aono)
{
        ao[aono].type = AO_INACTIF;
        spr_releaseSprite(ao[aono].sprno);
        ao[aono].sprno = -1;
}

void ao_tdetruire()
{
    int aono;
    for(aono=0;aono<MAX_AO;aono++)
    {
        ao_detruire(aono);
    }
}

void ao_updateAll()
{
        int i;

    /* On parcourt tous le tableau des AO */
    for (i=0;i<MAX_AO;i++)
    {
        /* On en trouve un ACTIF */
        if (ao[i].type != AO_INACTIF)
        {
            if (spr_getFinAnimation(ao[i].sprno))
            {
                ao_detruire(i);
            }
        }
    }
}



