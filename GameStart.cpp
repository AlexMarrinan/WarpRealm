#include "GameStart.h"
#include "WorldManager.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "Hero.h"
#include "Points.h"
#include "BigSaucer.h"
#include "ResourceManager.h"
#include "Music.h"
#include "LaserDisplay.h"

GameStart::GameStart() {
    setType("GameStartr");
    setSprite("gamestart");

    // Play start music.
    p_music = RM.getMusic("start music");
    playMusic();

    // Set starting location in the middle of window.
    int world_horiz = (int)WM.getBoundary().getHorizontal();
    int world_vert = (int)WM.getBoundary().getVertical();
    df::Vector p(world_horiz / 2, world_vert / 2);
    setPosition(p);

    // Register for "keyboard" event.
    registerInterest(df::KEYBOARD_EVENT);

    //High Score Display
    df::ViewObject* p_vo = new df::ViewObject;
    p_vo->setLocation(df::TOP_CENTER);
    p_vo->setViewString("High Score");
    p_vo->setValue(Points::high_score);
    p_vo->setColor(df::YELLOW);
}

void GameStart::playMusic() {
    //p_music->play();
}

int GameStart::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P:// play
            start();
            break;
        case df::Keyboard::Q:// quit
            GM.setGameOver();
            break;
        default: // Key is not handled.
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

void GameStart::start() {
    // Create hero.
    new Hero;

    // Pause start music.
    p_music->stop();

    // Spawn some saucers to shoot.
    for (int i = 0; i < 16; i++)
        new Saucer;

    // Setup heads-up display.
    new Points;		                     // Points display.
    new LaserDisplay;                    // Laser display.
    df::ViewObject* p_vo = new df::ViewObject; // Count of nukes.
    p_vo->setLocation(df::TOP_LEFT);
    p_vo->setViewString("Nukes");
    p_vo->setValue(1);
    p_vo->setColor(df::YELLOW);

    // When game starts, become inactive.
    setActive(false);
}

int GameStart::draw() {
    return df::Object::draw();
}