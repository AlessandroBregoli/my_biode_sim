#include "Euler_stepper.h"
#include "imports.h"
#include <map>
void Euler_stepper::do_step(std::map<std::string, double> in ,std::map<std::string, double> &out){
    std::map<std::string, double> deriv;
    derivs(deriv, in);
    for(const auto &iter: deriv){
        out[iter.first] = in[iter.first] +  h * iter.second;
    }
}

Euler_stepper::Euler_stepper(const Model* m, double hh):Stepper(m){
    this->h = hh;
}