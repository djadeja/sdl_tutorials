#include "Camera.h"

Camera  Camera::cameraControl;

Camera::Camera() : targetX(NULL), targetY(NULL), x(0), y(0), targetMode(TargetMode::NORMAL) {
}

int Camera::getX() {
    if (targetX != NULL) {
        if (targetMode == TargetMode::CENTER) {
            return *targetX - (WIN_WIDTH / 2);
        }

        return *targetX;
    }

    return x;
}

int Camera::getY() {
     if(targetY != NULL) {
        if(targetMode == TargetMode::CENTER) {
            return *targetY - (WIN_HEIGHT / 2);
        }
 
        return *targetY;
    }
 
    return y;
}

void Camera::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Camera::setTarget(float *x, float *y) {
    targetX = x;
    targetY = y;
}