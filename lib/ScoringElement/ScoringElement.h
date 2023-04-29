#pragma once

#include "Arduino.h"

namespace Pinball
{   
    class ScoringElement
    {
        private:
            int score;
        public:
            int getScore() {return score;}
            void addScore() {score++;}
            void setScore(int score) {this->score = score;}
    };

}