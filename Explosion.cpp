#include "Explosion.h"
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

Explosion::Explosion(){
    registerInterest(df::STEP_EVENT);

    // Link to "explosion" sprite.
    if (setSprite("explosion") == 0)
        // Set live time as long as sprite length.
        time_to_live = getAnimation().getSprite()->getFrameCount();
    else
        time_to_live = 0;

    setSolidness(df::SPECTRAL);
}
int Explosion::eventHandler(const df::Event* p_e) {
	//call step every in game step
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}
void Explosion::step() {
    time_to_live--;
    if (time_to_live <= 0)
        WM.markForDelete(this);
}
