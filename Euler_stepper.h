#include "Stepper.h"

class Euler_stepper: public Stepper{
    public:
        void step();
        Euler_stepper(const Model* m, double hh);
};