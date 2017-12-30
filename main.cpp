
#include <iostream>
#include "Ode_sym.h"
#include "Euler_stepper.h"
#include <cmath>

double derivata(double y){
    
    return 1-2*y;
}

double vera(double t){
    return 1.0/2.0 * (1 - std::exp(0-2*t));
}


int main(){
    std::cout<<"Inizio:"<<std::endl;
    Model* model;
    SBMLReader reader;
    SBMLDocument *doc = reader.readSBML("repressilator.xml");
    model = doc->getModel();
    free(doc);
    Euler_stepper stepper(model,0.1);
    for(int i = 0; i < 100; i++)
        stepper.step();
    for(const auto &iter:stepper.get_steps()[100])
        std::cout<<iter.first<<":"<<iter.second<<std::endl;

    
    return 0;
}