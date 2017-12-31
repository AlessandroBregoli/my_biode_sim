#include "Euler_stepper.h"
#include "imports.h"
#include <map>
void Euler_stepper::do_step(){
    std::map<std::string, double> deriv;
    derivs(deriv);
    for(const auto &iter: deriv){
        steps[actual_step + 1][iter.first] = steps[actual_step][iter.first] +  h * iter.second;
    }
}

Euler_stepper::Euler_stepper(const Model* m, double hh):Stepper(m){
    this->h = hh;
}