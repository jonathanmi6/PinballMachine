#include "Arduino.h"
#include "Launcher.h"
#include "constants.h"

Pinball::Launcher::Launcher::Launcher()
{
    
}

void Pinball::Launcher::Launcher::init()
{

}

void Pinball::Launcher::Launcher::update(unsigned long currTime)
{
    //launching conditions
    //launch settings
    //count # of resets
    //determination of start/stop will be handled by scorekeeper?
}

bool Pinball::Launcher::Launcher::getResetSense()
{
    return false; //analog sense? or schmitdd trigger
}

int Pinball::Launcher::Launcher::getResetCount()
{
    return 0;
}
