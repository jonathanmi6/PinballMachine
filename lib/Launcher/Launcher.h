#pragma once

namespace Pinball::Launcher
{
namespace Constants
{
    const unsigned long LAUNCH_TIME = 100;
    const int LAUNCH_PERCENT = 255;
    const int HOLD_PERCENT = 100;
    const int OFF_PERCENT = 0;

    //analog launcher? - how? linear pot?

}

class Launcher
{
    private:


    public:
        Launcher();
        void init();
        void update(unsigned long currTime);

        bool getResetSense(); 
        int getResetCount();
};
}