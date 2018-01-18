#include "RK4_stepper.h"
#include "imports.h"
#include <map>
void RK4_stepper::do_step(std::map<std::string, double> in ,std::map<std::string, double> &out, double h){
    double a = (std::sqrt(2)-1)/2;
    double b = (2- std::sqrt(2))/2;
    double c = (-std::sqrt(2))/2;
    double d = (2 + std::sqrt(2))/2;;

    std::map<std::string, double> deriv;
    derivs(deriv, in);
    std::map<std::string, double> k1, k2, k3, k4;
    for(const auto &iter: deriv){
        k1[iter.first] =  h * iter.second;
        out[iter.first] =  in[iter.first] + k1[iter.first]/2;
        
    }
    derivs(deriv, out);
    for(const auto &iter: deriv){
        k2[iter.first] =  h * iter.second;
        out[iter.first] = in[iter.first] + a*k1[iter.first] + b*k2[iter.first];
        //out[iter.first] = in[iter.first] + k2[iter.first]/2;
        
    }
    derivs(deriv,out);
    for(const auto &iter: deriv){
        k3[iter.first] =  h * iter.second;
        out[iter.first] = in[iter.first] + c*k2[iter.first] + d*k3[iter.first];
        //out[iter.first] = in[iter.first] + k3[iter.first];
        
    }
    derivs(deriv,out);
    for(const auto &iter: deriv){
        k4[iter.first] =  h * iter.second;
        out[iter.first] = in[iter.first] + 
                            1.0/6.0*k1[iter.first] + 
                            b/3.0*k2[iter.first] + 
                            d/3.0*k3[iter.first] +
                            1.0/6.0*k4[iter.first];
    }
}

RK4_stepper::RK4_stepper(const Model* m, double h, double atol, double rtol)
                            :Stepper(m,h,atol,rtol){
    this->k_error = 4;
}