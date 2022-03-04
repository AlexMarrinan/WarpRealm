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
    RM.loadSprite("sprites/walls/fizzler-v.txt", WALL_FIZZLER_V_STR);

    RM.loadSprite("sprites/walls/door_v_locked.txt", WALL_DLV_STR);
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

    RM.loadSprite("sprites/arrow-u-spr.txt", "arrow-u");
    RM.loadSprite("sprites/arrow-d-spr.txt", "arrow-d");
    RM.loadSprite("sprites/arrow-l-spr.txt", "arrow-l");
    RM.loadSprite("sprites/arrow-r-spr.txt", "arrow-r");

    RM.loadSprite("sprites/button-on-spr.txt", "button-on");
    RM.loadSprite("sprites/button-off-spr.txt", "button-off");
    RM.loadSprite("sprites/cube-spr.txt", "cube");
    RM.loadSprite("sprites/monster-spr.txt", "monster");
    RM.loadSprite("sprites/breakable-spr.txt", "breakable");
    RM.loadSprite("sprites/exitdoor-spr.txt", "exitdoor");
    RM.loadSprite("sprites/animated-exitdoor-spr.txt", "animated-exitdoor");
    RM.loadSprite("sprites/orbicon-spr.txt", "orbicon");
    RM.loadSprite("sprites/orbicon-collected-spr.txt", "orbicon-collected");
    RM.loadSprite("sprites/pu-portals-spr.txt", "pu-portals");
    RM.loadSprite("sprites/pu-sword-spr.txt", "pu-sword");

    RM.loadSprite("sprites/sword-u.txt", "sword-u");
    RM.loadSprite("sprites/sword-d.txt", "sword-d");
    RM.loadSprite("sprites/sword-l.txt", "sword-l");
    RM.loadSprite("sprites/sword-r.txt", "sword-r");

    RM.loadSprite("sprites/empty-spr.txt", "empty");
    
    //OLD
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");

    RM.loadSound("sounds/breakable.wav", "breakable");
    RM.loadSound("sounds/equip-sword.wav", "equip-sword");
    RM.loadSound("sounds/equip-orb.wav", "equip-orb");
    RM.loadSound("sounds/sword-slash.wav", "sword-slash");
    RM.loadSound("sounds/arrow-shoot.wav", "arrow-shoot");
    RM.loadSound("sounds/win.wav", "win");
    RM.loadSound("sounds/keys.wav", "keys");

    RM.loadSound("sounds/blue-portal-open.wav", "blue-portal-open");
    RM.loadSound("sounds/blue-portal-shoot.wav", "blue-portal-shoot");

    RM.loadMusic("sounds/game-music.wav", "game-music");
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
  //populateWorld();
  new GameStart;

  //new df::Pause(df::Keyboard::F10);

  GM.run();

  // Shut everything down.
  GM.shutDown();
}