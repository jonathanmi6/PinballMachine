# PinballMachine
PlatformIO C++ code for ECE 115 pinball machine project.

## General Guidelines
* All digital inputs are to be INPUT_PULLUP

## Gameplay Mechanisms

### Pong Slider
* Flippers
* Flipper buttons
* Slider
* Slider buttons
#### Todo:
* ~~Test code logic~~
* ~~Test flippers~~
* Test slider with motor driver

### Launcher
* Launcher Solenoid
* Launcher button
* Launch strength pot

#### Todo:
* Implement code


### Score Keeper / Game Warden
* Score keeper
* Scoreboard
* Reset Sensors

#### Todo:
* Test scoreboard display code
* Implement game flow code
    * Power up: flash some lights, etc in setup()
    * Wait for launcher to launch
    * Loop code until reset sensor triggered
        * End round
        * Increment round count
    * Check round cound < max round count
    * Wait for launcher to launch again
    * Once round count > max round count
        * Reset score
        * Reset round count
* Discrete reset button on machine?



## Scoring Mechanisms:

### Scoring Elmenet
* Parent object for all scoring mechanisms for commonality with scoring methods

### Drop Target
* Drop sensor
* Reset Servo
#### Todo:
* Fully tested :heavy_check_mark:

### Pop Bumper
* Contact sensor
* Pop Solenoid

#### Todo:
* Code logic tested, test with solenoid
* Possibly reuse for slingshot?

### Channels
* Channel Sensors
#### Todo:
* Code

### Horizontal Spinner
* DC motor
#### Todo:
* Design and build
* Program

### Vertical Spinner






