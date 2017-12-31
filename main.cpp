
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
    Euler_stepper stepper(model,0.1);
    for(int i = 0; i < 500; i++){
        stepper.step();
    }
    std::cout<<"Inizio il disegno"<<std::endl;
    //species_plot(stepper);
    species_csv(stepper, "dati.csv");
    return 0;
}