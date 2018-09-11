#include "game_engine.h"

int ASSERT_LEFT = 0; 
int ASSERT_RIGHT = 0;
int ASSERT_SHOOT = 0;

SpaceShip::SpaceShip(int x, int y)
{
  this->xPos = x;
  this->yPos = y;
}

void SpaceShip::draw()
{
  uLCD.BLIT(xPos,yPos,ALIEN_WIDTH,ALIEN_HEIGHT,SpaceShip_sprite);
}

Bullet* SpaceShip::update()
{
  if (ASSERT_LEFT){
    ASSERT_LEFT = 0;
    this->left();
    this->draw();
  }
  if (ASSERT_RIGHT){
    ASSERT_RIGHT = 0;
    this->right();
    this->draw();
  }
  if (ASSERT_SHOOT) {
    ASSERT_SHOOT = 0;
    this->draw();
    Bullet* shot = this->fire();
    return shot;
  }
  
  return NULL;
}

void SpaceShip::left()
{
  uLCD.BLIT(xPos,yPos,ALIEN_WIDTH,ALIEN_HEIGHT,delete_sprite);
  xPos = xPos-5;
  if (xPos < 0)
    xPos = 0;
}

void SpaceShip::right()
{
  uLCD.BLIT(xPos,yPos,ALIEN_WIDTH,ALIEN_HEIGHT,delete_sprite);
  xPos = xPos + 5;
  if (xPos > 116){
    xPos = 116;  
  }
}

Bullet* SpaceShip::fire()
{
  if(Bullet::live){
    return NULL;
  }
  mySpeaker.PlayNote(6800,.12,.5);
  Bullet* shot = new Bullet(xPos+5, yPos+6, 12);
  return shot;
}
    
int Bullet::live = 0;

Bullet::Bullet(int x, int y, int vel)
{
  this->xPos = x;
  this->yPos = y;
  this->vel = vel;
  live = 1;
}

void Bullet::draw()
{
  uLCD.filled_rectangle(xPos,yPos,xPos,yPos+5,0x3399FF);
}

void Bullet::update(screenAlien** list)
{
  uLCD.filled_rectangle(xPos,yPos,xPos,yPos+5,0x000000);
  for (int i = 0; i<6; i++){
    screenAlien* alien = list[i];     
    if (!alien->isDead()) {
      if (alien->checkHealth(this)){
        delete this;
        return;
      }
      //check if all are dead
    }
  }
  yPos-=vel;
  if (yPos < 0){
    delete this;
    return;
  }
}

int Bullet::getX(){
  return this->xPos;
}
int Bullet::getY(){
  return this->yPos;
}

Bullet::~Bullet(){
  live = 0;
}

//global functions
/*
 * This function calls the alien initializer
 * then the function draws the spaceship and aliens after they are initialized
*/
void launch_game(screenAlien** list){
  create_aliens(list);
}

//this function populates the screenAlien list
void create_aliens(screenAlien** list){
  for (int i = 0; i<6; i++) {
    int type = rand() % 4;
    bool suitableY = false;
    int yPos;
    int tiers[6];
    while (!suitableY) {
      yPos = (rand() % 10) * 9; //multiples of 9
      tiers[i] = yPos;
      suitableY = true;
      int j = i - 1;
      while (j >= 0 && suitableY){
        if (tiers[j] == yPos)
          suitableY = false;
        j--;
      }
    }
    switch (type){
      case 0:
        list[i] = new alienBob(rand() % 116, yPos);  
        break;
      case 1:
        list[i] = new alienAlice(rand() % 116, yPos); 
        break;
      case 2:
        list[i] = new alienJeff(rand() % 116, yPos);  
        break;
      default:
        list[i] = new alienKaren(rand() % 116, yPos);   
      }
  }
}

/*
see if any aliens are dead
see if all aliens are dead
update the spaceship and Bullet
draw spaceship and Bullet
update the aliens
draw the aliens
reset timer if needed
*/
void run_game(screenAlien** list){
  int gameOver = -1;
  
  //initialize SpaceShip
  SpaceShip USS_enterprise = SpaceShip(59,120);
  USS_enterprise.draw();
  Bullet* userShot = NULL;
  timer.start();
  while (gameOver == -1){
    if (!aliensAlive)
        return;      
    
    //update aliens
    for (int i = 0; i<6; i++){
      if (!list[i]->isDead()){
        list[i]->update();
        list[i]->draw();
        if (list[i]->getY() > 116)
          gameOver = 0;
      }
      //update spaceship  
      if (Bullet::live == 0){
        userShot = USS_enterprise.update();
      }else{
        USS_enterprise.update();
        userShot->update(list);
        if (Bullet::live ==1)
          userShot->draw();
      }
    }
    handleDownfall();

  }
  uLCD.cls();
  while (1)
    uLCD.printf("\n     GAME OVER");
}



void handleDownfall(){
  if(timer.read() > 10.0)
    timer.reset();
}

int SpaceShip_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
_,_,_,_,_,_,_,_,_,_,_, 
_,_,_,_,_,_,_,_,_,_,_, 
_,_,_,_,_,X,_,_,_,_,_, 
_,_,_,_,X,X,X,_,_,_,_, 
_,_,_,_,X,X,X,_,_,_,_, 
_,_,X,X,X,_,X,X,X,_,_, 
_,_,X,_,_,X,_,_,X,_,_, 
_,_,X,_,_,_,_,_,X,_,_, 
};


