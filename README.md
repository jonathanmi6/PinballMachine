# PinballMachine
PlatformIO C++ code for ECE 115 pinball machine project. Uses Arduino Mega as controller.

## General Guidelines
* All digital inputs are to be INPUT_PULLUP

## Gameplay Mechanisms

### Pong Slider
* Flippers
* Flipper buttons
* Slider
* Slider buttons
#### Todo:
- [X] Design and build
- [X] Test code logic
- [X] Test flippers
- [X] Test slider with motor driver

### Launcher
* Launcher Solenoid
* Launcher button
* Launch strength pot

#### Todo:
- [X] Design and build
- [X] Test code logic
- [ ] Test mechanism


### Score Keeper / Game Warden
* Score keeper
* Scoreboard
* Reset Sensors

#### Todo:
- [X] Test scoreboard display code
- [X] Implement game flow code
    - [X] Power up: flash some lights, etc in setup()
    - [x] Wait for launcher to launch
    - [x] Loop code until reset sensor triggered
        - [x] End round
        - [x] Increment round count
    - [x] Check round cound < max round count
    - [x] Wait for launcher to launch again
    - [x] Once round count > max round count
        - [x] Reset score
        - [x] Reset round count
- [X] Discrete reset button on machine



## Scoring Mechanisms:

### Scoring Elmenet
* Parent object for all scoring mechanisms for commonality with scoring methods

### Drop Target
* Drop sensor
* Reset Servo
#### Todo:
- [X] Design and build
- [X] Test code logic
- [X] Test mechanism

### Pop Bumper
* Contact sensor
* Pop Solenoid
* Possibly reuse object for slingshot?

#### Todo:
- [x] Design and build
- [x] Test code logic
- [ ] Test with solenoid

### Channels
* Channel Sensors
#### Todo:
- [ ] Test code logic
- [ ] Test with sensors

### Horizontal Spinner
* DC motor
* Sensor?
#### Todo:
- [X] Design and build
- [ ] Test code logic
- [ ] Test mechanism

### Vertical Spinner
* Spin sensor (LS that triggers per spin?)
#### Todo:
- [ ] Design and build
- [ ] Test code logic
- [ ] Test mechanism







