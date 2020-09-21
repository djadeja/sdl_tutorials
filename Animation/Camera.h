#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "SDL2/SDL.h"
#include "Define.h"

enum class TargetMode {
    NORMAL = 0,
    CENTER
};

class Camera {
    public:
        static Camera cameraControl;

    private:
        int x, y;
        float *targetX, *targetY;

    public:
        TargetMode targetMode;

    public:
        Camera();
        int getX();
        int getY();
        void setPos(int x, int y);
        void setTarget(float *x, float *y);
};

#endif