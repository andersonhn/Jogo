//==============
//=   Player   =
//==============

void iniciarJogador(struct Player *heroi);
void desenharPlayer(struct Player *heroi);
void moverEsquerda(struct Player *heroi);
void moverDireita(struct Player *heroi);
void pular(struct Player *heroi);
void gravidadePlayer(struct Player *heroi,int gravidade);
void desenharBloqueio(struct Player *heroi);

void iniciarJogador(struct Player *heroi)
{
    heroi->InfoPlayer.x = Width/2;
    heroi->InfoPlayer.y = Height/2;
    heroi->InfoPlayer.ID = PLAYER;
    heroi->InfoPlayer.live = true;
    heroi->InfoPlayer.jump = false;
    heroi->InfoPlayer.onGround = true;
    heroi->InfoPlayer.speed = 3;
    heroi->InfoPlayer.vSpeed = 5;
    heroi->InfoPlayer.maxJump = 100;
    heroi->InfoPlayer.curPlace = Height/2;

}
void moverEsquerda(struct Player *heroi)
{
    if(heroi->InfoPlayer.live)
    {
        heroi->InfoPlayer.x -= heroi->InfoPlayer.speed;
    }
}
void moverDireita(struct Player *heroi)
{
    if(heroi->InfoPlayer.live)
    {
        heroi->InfoPlayer.x += heroi->InfoPlayer.speed;
    }
}
void desenharPlayer(struct Player *heroi)
{
    if(heroi->InfoPlayer.live)
    {
        al_draw_filled_circle(heroi->InfoPlayer.x,heroi->InfoPlayer.y,9,al_map_rgb(255,0,0));
    }
}
void desenharBloqueio(struct Player *heroi)
{
    if(heroi->InfoPlayer.live)
    {
        al_draw_filled_circle(heroi->InfoPlayer.x+5,heroi->InfoPlayer.y+5,5,al_map_rgb(0,255,0));
    }
}
void pular(struct Player *heroi)
{
    if(heroi->InfoPlayer.live)
    {
        heroi->InfoPlayer.y -= heroi->InfoPlayer.vSpeed = 5;;

        if(heroi->InfoPlayer.y <= heroi->InfoPlayer.curPlace - heroi->InfoPlayer.maxJump)
        {
            heroi->InfoPlayer.onGround = false;
        }

    }
}
void gravidadePlayer(struct Player *heroi,int gravidade)
{
    heroi->InfoPlayer.y += gravidade;

    if(heroi->InfoPlayer.y >= heroi->InfoPlayer.curPlace)
    {
        heroi->InfoPlayer.onGround = true;
        heroi->InfoPlayer.jump = false;
    }
}
