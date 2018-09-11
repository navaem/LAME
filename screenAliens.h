#ifndef __SCREEN_ALIENS_H__
#define __SCREEN_ALIENS_H__
#define ALIEN_HEIGHT 8 
#define ALIEN_WIDTH 11 
#define _ 0x000000 //BLACK 
#define X 0xFFFFFF //WHITE
#include "game_engine.h"

class Bullet;

extern int aliensAlive;

class screenAlien
{
  public:
    screenAlien(int x, int y, int v, int h);
    static void setFallTime(double t);
    virtual void draw() = 0;
    virtual void update();
    virtual int getY() {return yPos;};
    virtual int getX() {return xPos;};
    virtual bool hit();
    virtual bool isDead() {return (health < 1)? true:false;};
    bool checkHealth(Bullet* shot);
    static float ALIEN_FALL_TIME;
  private:
    int xPos;
    int yPos;
    int vel;
    int health;
};

class alienBob: public screenAlien
{
  public:
    //handle aliens as initializer lists
    alienBob(int x, int y);
    void draw();
  private:
    int up;
};

class alienAlice: public screenAlien
{
  public:
    //handle aliens as initializer lists
    alienAlice(int x, int y);
    void draw();
};

class alienJeff: public screenAlien
{
  public:
    //handle aliens as initializer lists
    alienJeff(int x, int y);
    void draw();
};

class alienKaren: public screenAlien
{
  public:
    //handle aliens as initializer lists
    alienKaren(int x, int y);
    void draw();
};

//sprite for alienBob
extern int alienBobDown_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];

//sprite for alien bob
extern int alienBobUp_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];

extern int alienAlice_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];

extern int alienJeff_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];

extern int alienKaren_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];

extern int delete_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];


#endif 