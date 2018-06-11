#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
enum IDS{PLAYER,ENEMY};

struct BasicInfo{
    int ID;
    int x;
    int y;
    int speed;
    int vSpeed;
    int maxJump;
    int curPlace;
    bool live;
    bool jump;
    bool onGround;
};

struct Player{
    struct BasicInfo InfoPlayer;
};

struct Enemy{

};



//==============
//= Global Var =
//==============

const int Width = 640;
const int Height = 480;
#endif // STRUCTS_H_INCLUDED
