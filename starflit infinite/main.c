#include <stdio.h>
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "joueur.h"
#include "maBibli.h"
#include "tirjoueur.h"
#include "alien.h"
#include "collision.h"
#include "animation.h"
#include "workflow.h"

int v1,v2,n;
n=1;
v1=1;
v2=2;
score_init();
void titre_ecran()
{
    int cpt;
    cpt=0;

    while(w_get()==W_TITLESCREEN)
    {
        prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        blitImageTra(IMAGE_DECOR1,0,0);
        blitImageTra(IMAGE_DECOR1,512,0);

        we_printString(64,428,"STARFLIT INFINITE");

        if(cpt<11)
        {
            we_printString(200,250,"PRESS START TO PLAY");
        }

        termineEcritureVideoTra();
        termineEcritureVideoGlobale();

        checkController();

        if(getKeyStart()==1)
        {

            w_set(W_INGAME);
        }

        cpt++;

        if(cpt==20)
        {
            cpt=0;
        }
    }
}

void next_level()
{
    int cpt;
    cpt=0;

    while(w_get()==W_NEXTLEVEL)
    {
        prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        blitImageTra(IMAGE_DECOR,0,0);
        blitImageTra(IMAGE_DECOR,512,0);


        if(cpt<11)
        {
            we_printString(100,196,"PRESS START TO PLAY NEXT LEVEL");
        }

        termineEcritureVideoTra();
        termineEcritureVideoGlobale();

        checkController();

        if(getKeyStart()==1)
        {
            w_set(W_INGAME);
        }

        cpt++;

        if(cpt==20)
        {
            cpt=0;
        }
    }
}

void game_over()
{
    int cpt;
    cpt=0;

    while(w_get()==W_GAMEOVER)
    {
        prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        blitImageTra(IMAGE_DECOR,0,0);
        blitImageTra(IMAGE_DECOR,512,0);

        we_printString(256,256,"SCORE");
        we_printInt(275,275,score_get());


        if(cpt<11)
        {
            we_printString(100,196,"GAME OVER. PRESS START TO PLAY");
        }

        termineEcritureVideoTra();
        termineEcritureVideoGlobale();

        checkController();

        if(getKeyStart()==1)
        {

            score_init();

            pl_setvie(3);

            creation_ennemies(AL_VIOLET,275,30,v1,-5);

            creation_ennemies(AL_FLIP,275,150,v2,7);

            w_set(W_INGAME);
        }

        cpt++;

        if(cpt==20)
        {
            cpt=0;
        }
    }

}

int main(int argc, char *argv[])
{

    int x,y,c;

    w_set(W_INIT);

    while(1)
    {
        if(w_get()==W_INIT)
        {

            initGfxEngine();
            spr_initSpriteEngine();
            initSfxEngine();

            rnd_srand2(time());


            loadImageTra("cd/vaisseau sprites du joueur.png",IMAGE_SPRITE,512,512);

            loadImageTra("cd/f2.png",IMAGE_DECOR,512,512);
            loadImageTra("cd/garde.png",IMAGE_DECOR1,512,512);

            loadImageTra("cd/font16x16.png",IMAGE_FONT,256,256);



            c=0;

            for(y=0;y<256;y+=16)
            {
                for(x=0;x<256;x+=16)
                {
                    getImageAlpha(c,IMAGE_FONT,x,y,16,16);
                    c++;
                }
            }

            getImageBankTra(IB_ALIEN_F0,IMAGE_SPRITE,6,430,76,82);
            getImageBankTra(IB_ALIEN_F1,IMAGE_SPRITE,79,305,76,82);
            getImageBankTra(IB_ALIEN_F2,IMAGE_SPRITE,207,239,97,96);
            getImageBankTra(IB_ALIEN_F3,IMAGE_SPRITE,207,136,97,96);
            getImageBankTra(IB_PLAYER_F0,IMAGE_SPRITE,8,169,87,77);
            getImageBankTra(IB_SHOOT_ALIEN_F0,IMAGE_SPRITE,3,360,58,17);
            getImageBankTra(IB_SHOOT_PLAYER_F0,IMAGE_SPRITE,473,4,56,11);
            getImageBankTra(IB_EXPLODE_F0,IMAGE_SPRITE,426,226,55,47);
            getImageBankTra(IB_EXPLODE_F1,IMAGE_SPRITE,426,300,55,47);
            getImageBankTra(IB_EXPLODE_F2,IMAGE_SPRITE,426,373,55,47);
            getImageBankTra(IB_EXPLODE_F3,IMAGE_SPRITE,426,436,55,47);
            getImageBankTra(IB_EXPLODE_F4,IMAGE_SPRITE,426,155,55,47);
            getImageBankTra(IB_EXPLODE_F5,IMAGE_SPRITE,343,332,43,51);

            loadSound("cd/tir.WAV",0);
            loadSound("cd/boom.WAV",1);
            loadSound("cd/game over.WAV",2);
            loadSound("cd/todjngafi.WAV",3);

            w_set(W_TITLESCREEN);

        }

        else if(w_get()==W_TITLESCREEN)
        {
            playMusic("cd/symbolism.ogg",0);

            titre_ecran();


            initialisation_du_joueur();

            initialisation_tir_du_joueur();

            initialisation_tir_alien();

            initialisation_des_ennemies();

            ao_initialisation();

            creation_ennemies(AL_VIOLET,275,30,v1,-5);

            creation_ennemies(AL_FLIP,275,150,v2,7);




        }

        else if(w_get()==W_INGAME)
        {


            while(w_get()==W_INGAME)
            {

                action_du_joueur();
                ps_moveall();
                al_moveall();
                as_moveall();
                ao_updateAll();
                verification_collision_ps_alien();
                verification_collision_as_joueur();


                prepareEcritureVideoGlobale();
                prepareEcritureVideoTra();

                blitImageTra(IMAGE_DECOR,0,0);
                blitImageTra(IMAGE_DECOR,512,0);

                we_printString(256,2,"SCORE");
                we_printInt(270,20,score_get());
                we_printString(0,450,"VIE:");
                we_printInt(60,450,pl_getvie());




                spr_updateAllSprites();
                spr_showAllSprites();

                termineEcritureVideoTra();
                termineEcritureVideoGlobale();



                if(al_compteur()==0)
                {
                    score_set(score_get()+10);
                    w_set(W_NEXTLEVEL);
                }

                if(pl_getvie()==0)
                {
                    playSound(2,0);
                    w_set(W_GAMEOVER);
                }
            }

        }
        else if(w_get()==W_NEXTLEVEL)
        {

            ao_tdetruire();
            as_tdetruire();
            ps_tdetruire();

            next_level();

            pl_setvie(3);

            creation_ennemies(AL_VIOLET,275,30,v1+n,-5);

            creation_ennemies(AL_FLIP,275,150,v2+n-1,7);

            creation_ennemies(AL_FLIP,0,50,v2+n,1);

            n++;

        }

        else if(w_get()==W_GAMEOVER)
        {

            al_tdetruire();
            ao_tdetruire();
            as_tdetruire();
            ps_tdetruire();


            game_over();

        }

    }


   return 0;
}

