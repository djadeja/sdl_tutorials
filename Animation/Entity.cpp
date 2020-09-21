#include "Entity.h"
#include "Camera.h"
#include "FPS.h"
#include "Area.h"

vector<Entity*> Entity::entityList;
vector<EntityCol> EntityCol::EntityColList;

EntityCol::EntityCol() {
    EntityA = NULL;
    EntityB = NULL;
}

Entity::Entity() {
    textureEntity = NULL;
    x = y = 0.0f;
    width = height = 0;
    MoveLeft  = false;
    MoveRight = false;
 
    Type =     ENTITY_TYPE_GENERIC;
 
    Dead = false;
    Flags = ENTITY_FLAG_GRAVITY;
 
    SpeedX = 0;
    SpeedY = 0;
 
    AccelX = 0;
    AccelY = 0;
 
    MaxSpeedX = 5;
    MaxSpeedY = 5;
 
    CurrentFrameCol = 0;
    CurrentFrameRow = 0;
 
    Col_X = 0;
    Col_Y = 0;
 
    Col_Width  = 0;
    Col_Height = 0;
}

Entity::~Entity() {

}

bool Entity::onLoad(SDL_Renderer* sdlRenderer, const string& file, int width, int height, int maxFrames) {
    textureEntity = new Texture(sdlRenderer, file);
    this->width = width;
    this->height = height;
    animControl.maxFrames = maxFrames;
    return true;
}

void Entity::onLoop() {
    //We're not Moving
    if(MoveLeft == false && MoveRight == false) {
        StopMove();
    }
 
    if(MoveLeft) {
        AccelX = -0.5;
    }else
 
    if(MoveRight) {
        AccelX = 0.5;
    }
 
    if(Flags & ENTITY_FLAG_GRAVITY) {
        AccelY = 0.75f;
    }
 
    SpeedX += AccelX * FPS::FPSControl.GetSpeedFactor();
    SpeedY += AccelY * FPS::FPSControl.GetSpeedFactor();
 
    if(SpeedX > MaxSpeedX)  SpeedX =  MaxSpeedX;
    if(SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
    if(SpeedY > MaxSpeedY)  SpeedY =  MaxSpeedY;
    if(SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;
 
    onAnimate();
    OnMove(SpeedX, SpeedY);
}

void Entity::onRender(SDL_Renderer* rendererDisplay) {
    if (textureEntity == NULL || rendererDisplay == NULL)
        return;
    //textureEntity->copyTo(rendererDisplay, x, y, animState * width, animControl.getCurrentFrame() * height, width, height);
    textureEntity->copyTo(rendererDisplay, x - Camera::cameraControl.getX(), y - Camera::cameraControl.getY(), 
            CurrentFrameCol * width, (CurrentFrameRow + animControl.getCurrentFrame()) * height, width, height);
}

void Entity::onCleanup() {
    if (textureEntity)
        delete textureEntity;
    textureEntity = NULL;
}

void Entity::onAnimate() {
    if(MoveLeft) {
        CurrentFrameCol = 0;
    }else
 
    if(MoveRight) {
        CurrentFrameCol = 1;
    }
 
    animControl.onAnimate();
}

void Entity::onCollision(Entity* Entity) {

}

void Entity::OnMove(float MoveX, float MoveY) {
    if (MoveX == 0 && MoveY == 0)
        return;
 
    double NewX = 0;
    double NewY = 0;
 
    MoveX *= FPS::FPSControl.GetSpeedFactor();
    MoveY *= FPS::FPSControl.GetSpeedFactor();
 
    if(MoveX != 0) {
        if(MoveX >= 0)
            NewX =  FPS::FPSControl.GetSpeedFactor();
        else
            NewX = -FPS::FPSControl.GetSpeedFactor();
    }
 
    if(MoveY != 0) {
        if(MoveY >= 0)
            NewY =  FPS::FPSControl.GetSpeedFactor();
        else
            NewY = -FPS::FPSControl.GetSpeedFactor();
    }
 
    while(true) {
        if(Flags & ENTITY_FLAG_GHOST) {
            PosValid((int)(x + NewX), (int)(x + NewY)); //We don't care about collisions, but we need to send events to other entities
 
            x += NewX;
            x += NewY;
        }else{
            if(PosValid((int)(x + NewX), (int)(y))) {
                x += NewX;
            }else{
                SpeedX = 0;
            }
 
            if(PosValid((int)(x), (int)(y + NewY))) {
                y += NewY;
            }else{
                SpeedY = 0;
            }
        }
 
        MoveX += -NewX;
        MoveY += -NewY;
 
        if(NewX > 0 && MoveX <= 0) NewX = 0;
        if(NewX < 0 && MoveX >= 0) NewX = 0;
 
        if(NewY > 0 && MoveY <= 0) NewY = 0;
        if(NewY < 0 && MoveY >= 0) NewY = 0;
 
        if(MoveX == 0) NewX = 0;
        if(MoveY == 0) NewY = 0;
 
        if(MoveX == 0 && MoveY     == 0)     break;
        if(NewX  == 0 && NewY     == 0)     break;
    }
}

void Entity::StopMove() {
    if(SpeedX > 0) {
        AccelX = -1;
    }
 
    if(SpeedX < 0) {
        AccelX =  1;
    }
 
    if(SpeedX < 2.0f && SpeedX > -2.0f) {
        AccelX = 0;
        SpeedX = 0;
    }
}

bool Entity::Collides(int oX, int oY, int oW, int oH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;
 
    int tX = (int)x + Col_X;
    int tY = (int)y + Col_Y;
 
    left1 = tX;
    left2 = oX;
 
    right1 = left1 + width - 1 - Col_Width;
    right2 = oX + oW - 1;
 
    top1 = tY;
    top2 = oY;
 
    bottom1 = top1 + height - 1 - Col_Height;
    bottom2 = oY + oH - 1;
 
 
    if (bottom1 < top2)
        return false;
    if (top1 > bottom2)
        return false; 
    if (right1 < left2)
        return false;
    if (left1 > right2)
        return false;
 
    return true;
}

bool Entity::PosValid(int NewX, int NewY) {
    bool Return = true;
 
    int StartX     = (NewX + Col_X) / TILE_WIDTH;
    int StartY     = (NewY + Col_Y) / TILE_HEIGHT;
 
    int EndX    = ((NewX + Col_X) + width - Col_Width - 1)      / TILE_WIDTH;
    int EndY    = ((NewY + Col_Y) + height - Col_Height - 1)    / TILE_HEIGHT;
 
    for(int iY = StartY;iY <= EndY;iY++) {
        for(int iX = StartX;iX <= EndX;iX++) {
            Tile* Tile = Area::areacontrol.getTile(iX * TILE_WIDTH, iY * TILE_HEIGHT);
 
            if(PosValidTile(Tile) == false) {
                Return = false;
            }
        }
    }
 
    if(Flags & ENTITY_FLAG_MAPONLY) {
    }else{
        for(int i = 0;i < entityList.size();i++) {
            if(PosValidEntity(entityList[i], NewX, NewY) == false) {
                Return = false;
            }
        }
    }
 
    return Return;
}

bool Entity::PosValidTile(Tile* Tile) {
    if(Tile == NULL) {
        return true;
    }
 
    if(Tile->type == TileType::BLOCK) {
        return false;
    }
 
    return true;
}

bool Entity::PosValidEntity(Entity* Entity, int NewX, int NewY) {
    if(this != Entity && Entity != NULL && Entity->Dead == false &&
        Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
        Entity->Collides(NewX + Col_X, NewY + Col_Y, width - Col_Width - 1, height - Col_Height - 1) == true) {
 
        EntityCol EntityCol;
 
        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;
 
        EntityCol::EntityColList.push_back(EntityCol);
 
        return false;
    }
 
    return true;
}

