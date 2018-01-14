#include "Stepper.h"

class RK4_stepper: public Stepper{
    public:
       void do_step(std::map<std::string, double>,std::map<std::string, double>&, double h);
       RK4_stepper(const Model* m, double h, double atol, double rtol);
};