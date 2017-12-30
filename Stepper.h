#ifndef STEPPER
#define STEPPER
//#include "Bio_ode_system.h"
#include "imports.h"
class Stepper{
    protected:
        double h;
        int actual_step;
        std::vector<std::map<std::string, double> > steps;
        const Model* model;
    public:
        //Bio_ode_system ode_system;
        virtual void step(){return;};
        Stepper(const Model*);
        std::vector<std::map<std::string, double> > get_steps(){return steps;}
        double evaluate(const ASTNode *n);
        void derivs( std::map<std::string,double> &result);

};

#endif