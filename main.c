#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Structs.h"
#include "Player.c"

void switchState(int curState,int nextState);

bool keys[] = {false,false,false,false,false};
enum KEYS {LEFT,RIGHT,SPACE,ENTER,Z};

int main(void)
{
    //======================
    //=     Variables      =
    //======================
    const int FPS = 60;
    const int gravity = 10;
    bool done = false;
    bool redraw = false;
    bool gameOver = false;
    //======================
    //=Variaveis de Objetos=
    //======================
    struct Player heroi;

    //======================
    //=   Allegro Iniciar  =
    //======================
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event = NULL;
    ALLEGRO_TIMER *timer = NULL;

    //======================
    //=     Verificar      =
    //======================
    if(!al_init())
        exit(-1);

    display = al_create_display(Width,Height);

    if(!display)
        exit(-2);

    //====================
    //=  Iniciar Funçoes =
    //====================
    al_init_primitives_addon();
    al_install_keyboard();

    event = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    srand(time(NULL));
    iniciarJogador(&heroi);

    al_register_event_source(event, al_get_keyboard_event_source());
    al_register_event_source(event, al_get_timer_event_source(timer));
    al_register_event_source(event, al_get_display_event_source(display));

    al_start_timer(timer);

    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event, &ev);
        //=====================
        //=    Game Updade    =
        //=====================
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            if(keys[Z])
                desenharBloqueio(&heroi);
            if(!keys[Z] && heroi.InfoPlayer.onGround){
                if(keys[LEFT])
                    moverEsquerda(&heroi);
                if(keys[RIGHT])
                    moverDireita(&heroi);
            }
            if(heroi.InfoPlayer.jump)
                pular(&heroi);
            if(!heroi.InfoPlayer.onGround && heroi.InfoPlayer.jump)
                gravidadePlayer(&heroi,gravity);


        }
        //
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_UP:
                heroi.InfoPlayer.jump = true;
                break;
            case ALLEGRO_KEY_Z:
                keys[Z] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                break;
            case ALLEGRO_KEY_ENTER:
                keys[ENTER] = true;
                break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            case ALLEGRO_KEY_ENTER:
                keys[ENTER] = false;
                break;
            case ALLEGRO_KEY_Z:
                keys[Z] = false;
                break;
            }
        }
        //====================
        //=    Renderizar    =
        //====================
        if(redraw && al_is_event_queue_empty(event))
        {
            redraw = false;
            if(!gameOver)
            {
                desenharPlayer(&heroi);
            }

            al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

//================================
//=  Destruir objetos do Allegro =
//================================
    al_destroy_timer(timer);
    al_destroy_event_queue(event);
    al_destroy_display(display);

    return 0;
}

