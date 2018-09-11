#include "screenAliens.h"
#include "game_engine.h"

float screenAlien::ALIEN_FALL_TIME = 4.0;

int aliensAlive = 6;

screenAlien::screenAlien(int x, int y, int v, int h){
  xPos = x;
  yPos = y;
  vel = v;
  health = h;
}

void screenAlien::update(){
  uLCD.BLIT(xPos,yPos,ALIEN_WIDTH,ALIEN_HEIGHT,delete_sprite);
  xPos-=vel;
  if (xPos < 0){
    vel = -vel;
    xPos = 0;
  }
  if (xPos > 116){
    vel = -vel;
    xPos = 116;
  }
  if (timer.read() > screenAlien::ALIEN_FALL_TIME)
    yPos+=9;
}

void screenAlien::setFallTime(double t){
  t = 10*(1-t);
  t = (t < 4)? 4:t;
  t = (t >8)? 8:t;
  uLCD.printf("\n%f",t);
  screenAlien::ALIEN_FALL_TIME = t;
}


bool screenAlien::checkHealth(Bullet* shot) {
  int diff = this->getY() - shot->getY();
  if (diff >= -7 && diff <= 5){
    diff = this->getX() - shot->getX();
    if(diff >= -11 && diff <= 0){
      //alien has been hit
      delete shot;
      if (this->hit()){
        uLCD.BLIT(this->getX(),this->getY(),ALIEN_WIDTH,ALIEN_HEIGHT,delete_sprite);
        aliensAlive--;
        return true;
      }
    }
  }
  return false;
}

bool screenAlien::hit() {
  this->health--;
  if (this->health < 1)
    return true;
  return false;
}


alienBob::alienBob(int x, int y):screenAlien(x,y,1,1) {
  this->up = 0;

}

void alienBob::draw() {
  if (!this->isDead()){  
    if (up){
      uLCD.BLIT(this->getX(),this->getY(),ALIEN_WIDTH,ALIEN_HEIGHT,alienBobUp_sprite);
    } else {
    uLCD.BLIT(this->getX(),this->getY(),ALIEN_WIDTH,ALIEN_HEIGHT,alienBobDown_sprite);
    }
    up = (up==1) ? 0:1;
  }  
}

alienAlice::alienAlice(int x, int y):screenAlien(x,y,2,1){
}

void alienAlice::draw() {
  if (!this->isDead())
    uLCD.BLIT(this->getX(),this->getY(),ALIEN_WIDTH,ALIEN_HEIGHT,alienAlice_sprite);  
}


alienJeff::alienJeff(int x, int y) :screenAlien(x,y,1,3){
}

void alienJeff::draw() {
  if (!this->isDead()) 
    uLCD.BLIT(this->getX(),this->getY(),ALIEN_WIDTH,ALIEN_HEIGHT,alienJeff_sprite);  
}


alienKaren::alienKaren(int x, int y) : screenAlien(x,y,5,1){
}

void alienKaren::draw() {
  if (!this->isDead()) 
    uLCD.BLIT(this->getX(),this->getY(),ALIEN_WIDTH,ALIEN_HEIGHT,alienKaren_sprite);  
}

//sprite for alienBob
int alienBobDown_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
_,_,X,_,_,_,_,_,X,_,_, 
_,_,_,X,_,_,_,X,_,_,_, 
_,_,X,X,X,X,X,X,X,_,_, 
_,X,X,_,X,X,X,_,X,X,_, 
X,X,X,X,X,X,X,X,X,X,X, 
X,_,X,X,X,X,X,X,X,_,X, 
X,_,X,_,_,_,_,_,X,_,X, 
_,_,_,X,X,_,X,X,_,_,_,
};

//sprite for alien bob
int alienBobUp_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
_,_,X,_,_,_,_,_,X,_,_, 
X,_,_,X,_,_,_,X,_,_,X, 
X,_,X,X,X,X,X,X,X,_,X, 
X,X,X,_,X,X,X,_,X,X,X, 
X,X,X,X,X,X,X,X,X,X,X, 
_,_,X,X,X,X,X,X,X,_,_, 
_,_,X,_,_,_,_,_,X,_,_, 
_,X,_,_,_,_,_,_,_,X,_,
};

int alienAlice_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
_,_,_,_,X,X,X,_,_,_,_, 
_,X,X,X,X,X,X,X,X,X,_, 
X,X,X,X,X,X,X,X,X,X,X, 
X,X,X,_,_,X,_,_,X,X,X, 
X,X,X,X,X,X,X,X,X,X,X, 
_,_,_,X,X,_,X,X,_,_,_, 
_,_,X,X,_,_,_,X,X,_,_, 
X,X,_,_,_,X,_,_,_,X,X,
};

int alienJeff_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
_,_,_,_,X,X,X,_,_,_,_, 
_,_,_,_,X,X,X,_,_,_,_, 
_,X,X,X,X,X,X,X,X,X,_, 
X,X,X,_,_,X,_,_,X,X,X, 
_,X,X,X,_,X,_,X,X,X,_, 
_,X,_,X,_,_,_,X,_,X,_, 
_,X,_,X,_,_,_,X,_,X,_, 
X,X,_,_,_,X,_,_,_,X,X,
};

int alienKaren_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
_,_,_,_,_,X,_,_,_,_,_, 
_,_,_,_,_,X,_,_,_,_,_, 
_,X,X,X,_,X,_,X,X,X,_, 
X,X,X,_,_,X,_,_,X,X,X, 
_,X,X,X,X,X,X,X,X,X,_, 
_,X,_,X,_,_,_,X,_,X,_, 
_,X,_,X,_,_,_,X,_,X,_, 
_,_,X,_,_,_,_,_,X,_,_,
};

int delete_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
_,_,_,_,_,_,_,_,_,_,_, 
_,_,_,_,_,_,_,_,_,_,_, 
_,_,_,_,_,_,_,_,_,_,_, 
_,_,_,_,_,_,_,_,_,_,_, 
_,_,_,_,_,_,_,_,_,_,_, 
_,_,_,_,_,_,_,_,_,_,_, 
_,_,_,_,_,_,_,_,_,_,_, 
_,_,_,_,_,_,_,_,_,_,_, 
};
