#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <SDL2/SDL.h>

class Animation {
    private:
        int currentFrame;
        int frameInc;
        int frameRate;  // Milliseconds
        long oldTime;

    public:
        int maxFrames;
        bool oscillate;

    public:
        Animation();
        void onAnimate();
        void setFrameRate(int rate);
        void setCurrentFrame(int frame);
        int getCurrentFrame();
};

#endif