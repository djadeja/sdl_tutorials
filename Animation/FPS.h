#ifndef _CFPS_H_
#define _CFPS_H_
 
#include <SDL2/SDL.h>
 
class FPS {
    public:
        static FPS FPSControl;
 
    private:
        int     OldTime;
        int     LastTime;
        float   SpeedFactor;
        int     NumFrames;
        int     Frames;
 
    public:
        FPS(); 
        void    OnLoop();
        int     GetFPS();
        float   GetSpeedFactor();
};
 
#endif