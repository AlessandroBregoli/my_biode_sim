
#include <iostream>
#include "Ode_sym.h"
#include "Euler_stepper.h"
#include <cmath>
#include "gui.h"



int main(){
    std::cout<<"Inizio:"<<std::endl;
    Model* model;
    SBMLReader reader;
    SBMLDocument *doc = reader.readSBML("repressilator.xml");
    model = doc->getModel();
    free(doc);
    Euler_stepper stepper(model,0.1,0.01,0.001);
    do{
        stepper.step();
    }while(stepper.get_time_step()[stepper.get_actual_step()] < 100);
    std::cout<<"Inizio il disegno"<<std::endl;
    species_plot(stepper);
    species_csv(stepper, "dati.csv");
    return 0;
}