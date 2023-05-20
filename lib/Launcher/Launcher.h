#pragma once

namespace Pinball::Launch
{
namespace Constants
{
    const unsigned long LAUNCH_TIME = 100;
    const int LAUNCH_PERCENT_MAX = 255;
    const int LAUNCH_PERCENT_MIN = 100;
    const int OFF_PERCENT = 0;

    //analog launcher? - how? pot?

}

class Launcher
{
    private:
        bool launchFlag;
        unsigned long trigTime;
        int resetCount;
        bool launched;

        int getPotValue();
        
    public:
        Launcher();
        void init();
        void update(unsigned long currTime);

        void resetLaunched();
        bool getLaunched();
        bool getLaunchButton();
        int getLaunchStrength(); //perhaps display launch strength on scoreboard?
};
}