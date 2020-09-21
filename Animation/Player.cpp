#include "Player.h"
 
Player::Player() {
}
 
bool Player::onLoad(SDL_Renderer* sdlRenderer, const string& file, int width, int height, int maxFrames) {
    if(Entity::onLoad(sdlRenderer, file, width, height, maxFrames) == false) {
        return false;
    }
 
    return true;
}
 
void Player::onLoop() {
    Entity::onLoop();
}
 
void Player::onRender(SDL_Renderer* rendererDisplay) {
    Entity::onRender(rendererDisplay);
}
 
void Player::onCleanup() {
    Entity::onCleanup();
}
 
void Player::onAnimate() {
    if(SpeedX != 0) {
        animControl.maxFrames = 8;
    }else{
        animControl.maxFrames = 0;
    }
 
    Entity::onAnimate();
}
 
void Player::onCollision(Entity* Entity) {
}