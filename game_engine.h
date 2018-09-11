//this header file will define the spaceship/Bullet
#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__
#include <stdlib.h>
#include "mbed.h"
#include "SDFileSystem.h"
#include "screenAliens.h"
#include "PinDetect.h"
#include "MMA8452.h"

#include "Speaker.h"

#ifndef ULCD_4DGL_H
#define ULCD_4DGL_H
#include "uLCD_4DGL.h"
#endif

class screenAlien;

//hardware delcarations init in main
extern Timer timer;
extern SDFileSystem sd;
extern uLCD_4DGL uLCD;
extern PinDetect pbLeft;
extern PinDetect pbCenter;
extern PinDetect pbRight;
extern Speaker mySpeaker;
extern MMA8452 acc;
extern int SpaceShip_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];

//global vars
extern int ASSERT_LEFT; 
extern int ASSERT_RIGHT;
extern int ASSERT_SHOOT;

    
class Bullet {
    public: 
      Bullet(int x, int y, int vel);
      void draw();
      void update(screenAlien** list);
      int getX();
      int getY();
     ~Bullet();
      static int live;
    private:
      int xPos;
      int yPos;
      int vel;
    };
    
class SpaceShip {
  public: 
    SpaceShip(int x, int y);
    void draw();
    Bullet* update();
    void left();
    void right();
    Bullet* fire();
  private:
    int xPos;
    int yPos;
};
    
    
//global functions
/*
 * This function calls the alien initializer
 * then the function draws the spaceship and aliens after they are initialized
*/
void launch_game(screenAlien** alienList);

//this function populates the screenAlien list
void create_aliens(screenAlien** alienList);

/*
see if any aliens are dead
see if all aliens are dead
update the spaceship and Bullet
draw spaceship and Bullet
update the aliens
draw the aliens
reset timer if needed
*/
void run_game(screenAlien** list);


//method for seeing if timer should be reset
void handleDownfall();

#endif 