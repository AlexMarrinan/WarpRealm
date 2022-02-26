//
// game.cpp
//
// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "BigSaucer.h"
#include "Hero.h"
#include "Bullet.h"
#include "Points.h"
#include "Star.h"
#include "GameStart.h"
#include "Pause.h"
#include "game.h"
#include "Wall.h"
#include "Room.h"
#include "Key.h"
#include "HealthDisplay.h"
#include "DisplayManager.h"

void loadResources(void) {
    RM.loadSprite("sprites/walls/h_1.txt", WALL_H1_STR);
    RM.loadSprite("sprites/walls/v_1.txt", WALL_V1_STR);
    RM.loadSprite("sprites/walls/n_1.txt", WALL_N1_STR);
    RM.loadSprite("sprites/walls/water.txt", WALL_WATER_STR);
    RM.loadSprite("sprites/walls/fizzler.txt", WALL_FIZZLER_STR);
    RM.loadSprite("sprites/walls/door_h_locked.txt", WALL_DLH_STR);
    RM.loadSprite("sprites/walls/door_v.txt", WALL_DV_STR);
    RM.loadSprite("sprites/walls/door_h.txt", WALL_DH_STR);

    RM.loadSprite("sprites/walls/h_1_p.txt", WALL_H1_STR_P);
    RM.loadSprite("sprites/walls/v_1_p.txt", WALL_V1_STR_P);
    RM.loadSprite("sprites/walls/n_1_p.txt", WALL_N1_STR_P);

    RM.loadSprite("sprites/blue-portal-spr.txt", "blue-portal");
    RM.loadSprite("sprites/red-portal-spr.txt", "red-portal");
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/red-bullet-spr.txt", "red-bullet");
    RM.loadSprite("sprites/chest-spr.txt", "chest");

    RM.loadSprite("sprites/hero-up-spr.txt", "hero-up");
    RM.loadSprite("sprites/hero-down-spr.txt", "hero-down");
    RM.loadSprite("sprites/hero-left-spr.txt", "hero-left");
    RM.loadSprite("sprites/hero-right-spr.txt", "hero-right");
    RM.loadSprite("sprites/hero-dead-spr.txt", "hero-dead");

    RM.loadSprite("sprites/key-spr.txt", "key");
    RM.loadSprite("sprites/turret-spr.txt", "turret");
    RM.loadSprite("sprites/arrow-h-spr.txt", "arrow-h");
    RM.loadSprite("sprites/arrow-v-spr.txt", "arrow-v");
    RM.loadSprite("sprites/button-on-spr.txt", "button-on");
    RM.loadSprite("sprites/button-off-spr.txt", "button-off");
    RM.loadSprite("sprites/cube-spr.txt", "cube");
    RM.loadSprite("sprites/monster-spr.txt", "monster");

    RM.loadSprite("sprites/pu-portals-spr.txt", "pu-portals");
    RM.loadSprite("sprites/pu-sword-spr.txt", "pu-sword");


    RM.loadSprite("sprites/empty-spr.txt", "empty");
    
    //OLD
   // RM.loadSprite("sprites/saucer-spr.txt", "saucer");

    RM.loadSprite("sprites/laser-spr.txt", "laser");
    RM.loadSprite("sprites/explosion-spr.txt", "explosion");
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");

    RM.loadSprite("sprites/big-saucer-4-spr.txt", "bigsaucer4");
    RM.loadSprite("sprites/big-saucer-3-spr.txt", "bigsaucer3");
    RM.loadSprite("sprites/big-saucer-2-spr.txt", "bigsaucer2");
    RM.loadSprite("sprites/big-saucer-1-spr.txt", "bigsaucer1");

    RM.loadSound("sounds/fire.wav", "fire");
    RM.loadSound("sounds/explode.wav", "explode");
    RM.loadSound("sounds/nuke.wav", "nuke");
    RM.loadSound("sounds/game-over.wav", "game over");

    RM.loadMusic("sounds/start-music.wav", "start music");
}

// Populate world with some objects.
void populateWorld() {

    // Spawn some Stars.
   // for (int i = 0; i < 16; i++)
    //    new Star;

    Hero* hero = new Hero;

    /*
    new Wall(H_1, Vector(20, 12));
    new Wall(H_1, Vector(22, 12));
    new Wall(V_1, Vector(23, 11));
    new Wall(V_1, Vector(23, 9));
    */

    Room* r0 = new Room("rooms/00.txt");
    r0->loadRoom();
    hero->currentRoom = r0;
    Room* r1 = new Room("rooms/01.txt");
    r0->setNextRoom(r1, RoomDirection::UP);
    r1->setNextRoom(r0, RoomDirection::DOWN);
    Room* r2 = new Room("rooms/02.txt");
    r0->setNextRoom(r2, RoomDirection::DOWN);
    r2->setNextRoom(r0, RoomDirection::UP);
    Room* r3 = new Room("rooms/03.txt");
    r3->setNextRoom(r1, RoomDirection::RIGHT);
    r1->setNextRoom(r3, RoomDirection::LEFT);
    Room* r4 = new Room("rooms/04.txt");
    r1->setNextRoom(r4, RoomDirection::UP);
    r4->setNextRoom(r1, RoomDirection::DOWN);
    Room* r5 = new Room("rooms/05.txt");
    r2->setNextRoom(r5, RoomDirection::LEFT);
    r5->setNextRoom(r2, RoomDirection::RIGHT);
    Room* r6 = new Room("rooms/06.txt");
    r4->setNextRoom(r6, RoomDirection::UP);
    r6->setNextRoom(r4, RoomDirection::DOWN);
    Room* r7 = new Room("rooms/07.txt");
    r6->setNextRoom(r7, RoomDirection::RIGHT);
    r7->setNextRoom(r6, RoomDirection::LEFT);
    Room* r8 = new Room("rooms/08.txt");
    r7->setNextRoom(r8, RoomDirection::DOWN);
    r8->setNextRoom(r7, RoomDirection::UP);
    Room* r9 = new Room("rooms/09.txt");
    r8->setNextRoom(r9, RoomDirection::DOWN);
    r9->setNextRoom(r8, RoomDirection::UP);
    r0->setNextRoom(r9, RoomDirection::RIGHT);
    r9->setNextRoom(r0, RoomDirection::LEFT);

    new Points;
    new HealthDisplay;

    //new Key(Vector(35, 7));
}
//spawns regular saucers 95% and big saucers 5%
void spawnSaucer(int prob) {
    if (rand() % 100 < prob) {
        new BigSaucer;
    }
    else {
        new Saucer;
    }
}
int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }
  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  //initialize high score (TODO: read from file)
  //Points::high_score = 0;

  // Show splash screen.
  //df::splash();

  // Load game resources.
  loadResources();

  // Populate game world with some objects.
  populateWorld();

  //new df::Pause(df::Keyboard::F10);

  GM.run();

  // Shut everything down.
  GM.shutDown();
}