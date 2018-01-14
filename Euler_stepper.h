#include "Stepper.h"

class Euler_stepper: public Stepper{
    public:
       void do_step(std::map<std::string, double>,std::map<std::string, double>&);
        Euler_stepper(const Model* m, double hh);
};