#include "Ode_sym.h"

#include "imports.h"
Ode_sym::Ode_sym(Stepper *s){
    this->s = s;
}

void Ode_sym::sym(){
    for(int i=0; i < this->max_step; i++){
        this->s->step();
    }
}