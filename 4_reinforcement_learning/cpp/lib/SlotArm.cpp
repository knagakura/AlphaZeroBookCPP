#ifndef SLOT_ARM
#define SLOT_ARM

#include "utility.hpp"

class SlotArm {
  public:
    float p;
    SlotArm(float _p) : p(_p) {}
    float draw() {
        if(p > utility::rand()) {
            return 1.0;
        } else {
            return 0.0;
        }
    }
};

#endif