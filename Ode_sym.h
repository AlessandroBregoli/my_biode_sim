#ifndef ODESYM
#define ODESYM
#include "Stepper.h"
#include "imports.h"


class Ode_sym{
    private:
        double rtol;
        double atol;
        int max_step;
    public:
        Stepper *s;
        Ode_sym(Stepper*);
        void sym();
         std::vector<std::map<std::string, double> > get_steps(){return s->get_steps();}
};

#endif